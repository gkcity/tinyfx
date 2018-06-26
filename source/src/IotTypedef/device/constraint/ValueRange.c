/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ValueRange.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <value/JsonNumber.h>
#include <JsonArray.h>
#include "ValueRange.h"

#define TAG     "ValueRange"

TINY_LOR
static TinyRet ValueRange_Construct(ValueRange *thiz, JsonArray *range)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(range, TINY_RET_E_ARG_NULL);

    do
    {
        JsonValue *min = NULL;
        JsonValue *max = NULL;
        JsonValue *step = NULL;

        memset(thiz, 0, sizeof(ValueRange));

        if (range->values.size != 3)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        min = (JsonValue *)TinyList_GetAt(&range->values, 0);
        max = (JsonValue *)TinyList_GetAt(&range->values, 1);
        step = (JsonValue *)TinyList_GetAt(&range->values, 2);

        if (min->type != JSON_NUMBER || max->type != JSON_NUMBER || step->type != JSON_NUMBER)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (min->data.number->type != max->data.number->type)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (min->data.number->type != step->data.number->type)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        thiz->min = min;
        thiz->max = max;
        thiz->step = step;
    } while (false);

    return ret;
}

TINY_LOR
static void ValueRange_Dispose(ValueRange *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->min != NULL)
    {
        JsonValue_Delete(thiz->min);
        thiz->min = NULL;
    }

    if (thiz->max != NULL)
    {
        JsonValue_Delete(thiz->max);
        thiz->max = NULL;
    }

    if (thiz->step != NULL)
    {
        JsonValue_Delete(thiz->step);
        thiz->step = NULL;
    }
}

TINY_LOR
ValueRange *ValueRange_NewFrom(JsonArray *range)
{
    ValueRange *thiz = NULL;

    RETURN_VAL_IF_FAIL(min, NULL);
    RETURN_VAL_IF_FAIL(max, NULL);
    RETURN_VAL_IF_FAIL(step, NULL);

    do
    {
        thiz = (ValueRange *) tiny_malloc(sizeof(ValueRange));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ValueRange_Construct(thiz, range)))
        {
            ValueRange_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void ValueRange_Delete(ValueRange *thiz)
{
    RETURN_IF_FAIL(thiz);

    ValueRange_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static bool ValueRange_CheckIntegerValue(ValueRange *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    for (long v = thiz->min->data.number->value.intValue; v <= thiz->max->data.number->value.intValue; v += thiz->min->data.number->value.intValue)
    {
        if (value->data.number->value.intValue == v)
        {
            return true;
        }
    }

    return false;
}

TINY_LOR
static bool ValueRange_CheckFloatValue(ValueRange *thiz, JsonValue *value)
{
    float v = 0;

    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    v = thiz->min->data.number->value.floatValue;
    while (v < thiz->max->data.number->value.floatValue)
    {
        float difference = (value->data.number->value.floatValue - v);
        if (difference < 0.00001f || difference > -0.00001f)
        {
            return true;
        }

        v += thiz->min->data.number->value.floatValue;
    }

    return false;
}

TINY_LOR
bool ValueRange_CheckValue(ValueRange *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    if (value->type != JSON_NUMBER)
    {
        return false;
    }

    if (value->data.number->type != thiz->min->data.number->type)
    {
        return false;
    }

    return (value->data.number->type == JSON_NUMBER_INTEGER) ?
           ValueRange_CheckIntegerValue(thiz, value) : ValueRange_CheckFloatValue(thiz, value);
}