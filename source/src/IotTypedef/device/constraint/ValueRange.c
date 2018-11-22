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
#include <value/JsonString.h>
#include "ValueRange.h"

#define TAG     "ValueRange"

TINY_LOR
static TinyRet ValueRange_Construct(ValueRange *thiz, JsonValue *min, JsonValue *max, JsonValue *step)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(min, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(max, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(step, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(ValueRange));

        if (min->type != max->type || min->type != step->type)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        thiz->min = JsonValue_NewFrom(min);
        if (thiz->min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->max = JsonValue_NewFrom(max);
        if (thiz->max == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->step = JsonValue_NewFrom(step);
        if (thiz->step == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static TinyRet ValueRange_Construct2(ValueRange *thiz, JsonArray *range)
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
            LOG_E(TAG, "range.length invalid: %d", range->values.size);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        min = (JsonValue *)TinyList_GetAt(&range->values, 0);
        max = (JsonValue *)TinyList_GetAt(&range->values, 1);
        step = (JsonValue *)TinyList_GetAt(&range->values, 2);

        if (min->type != max->type || min->type != step->type)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        thiz->min = JsonValue_NewFrom(min);
        if (thiz->min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->max = JsonValue_NewFrom(max);
        if (thiz->max == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->step = JsonValue_NewFrom(step);
        if (thiz->step == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
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
ValueRange* ValueRange_New(JsonValue *min, JsonValue *max, JsonValue *step)
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

        if (RET_FAILED(ValueRange_Construct(thiz, min, max, step)))
        {
            ValueRange_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
ValueRange *ValueRange_NewFrom(JsonArray *range)
{
    ValueRange *thiz = NULL;

    RETURN_VAL_IF_FAIL(range, NULL);

    do
    {
        thiz = (ValueRange *) tiny_malloc(sizeof(ValueRange));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ValueRange_Construct2(thiz, range)))
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
static bool ValueRange_CheckIntegerValue(ValueRange *thiz, long value)
{
    long min = 0;
    long max = 0;
    long step = 0;

    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "ValueRange_CheckIntegerValue: %ld", value);

    min = thiz->min->data.number->value.intValue;
    max = thiz->max->data.number->value.intValue;
    step = thiz->step->data.number->value.intValue;

    // fix step value
    if (step == 0)
    {
        step = 1;
    }

    for (long v = min; v <= max; v += step)
    {
        if (v == value)
        {
            return true;
        }
    }

    LOG_E(TAG, "ValueRange_CheckIntegerValue FAILED, invalid value: %ld", value);

    return false;
}

TINY_LOR
static bool ValueRange_CheckFloatValue(ValueRange *thiz, float value)
{
    float v = 0.0;
    float max = 0.0;
    float step = 0.0;

    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "ValueRange_CheckFloatValue: %f", value);

    v = thiz->min->data.number->value.floatValue;
    max = thiz->max->data.number->value.floatValue;
    step = thiz->step->data.number->value.floatValue;

    // fix step value
    if (step < 0.0001f)
    {
        step = 0.0001f;
    }

    while (v < max)
    {
        float difference = (v - value);
        if (difference < 0.0001f || difference > -0.0001f)
        {
            return true;
        }

        v += step;
    }

    LOG_E(TAG, "ValueRange_CheckFloatValue FAILED, invalid value: %f", value);

    return false;
}

TINY_LOR
static bool ValueRange_CheckHexValue(ValueRange *thiz, JsonString *hex)
{
    char *stop = NULL;
    uint32_t min = 0;
    uint32_t max = 0;
    uint32_t step = 0;
    uint32_t value = 0;

    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(hex, false);

    LOG_D(TAG, "ValueRange_CheckHexValue: %s", hex->value);

    if (thiz->min == NULL || thiz->max == NULL || thiz->step == NULL)
    {
        LOG_E(TAG, "check hex value error: min/max/step is null");
        return false;
    }

    if (thiz->min->type != JSON_STRING)
    {
        LOG_E(TAG, "check hex value error: ValueRange not hex");
        return false;
    }

    if (thiz->min->data.string->value == NULL || thiz->max->data.string->value == NULL || thiz->step->data.string->value == NULL)
    {
        LOG_E(TAG, "check hex value error: min/max/step.string is null");
        return false;
    }

    min = (uint32_t) strtol(thiz->min->data.string->value, &stop, 16);
    max = (uint32_t) strtol(thiz->max->data.string->value, &stop, 16);
    step = (uint32_t) strtol(thiz->step->data.string->value, &stop, 16);
    value = (uint32_t) strtol(hex->value, &stop, 16);

    LOG_D(TAG, "check hex value: (%d, %d, %d), value = %d", min, max, step, value);

    for (uint32_t v = min; v <= max; v += step)
    {
        if (value == v)
        {
            return true;
        }
    }

    LOG_E(TAG, "ValueRange_CheckHexValue FAILED, invalid value: %s", hex->value);

    return false;
}

TINY_LOR
static bool ValueRange_CheckNumberValue(ValueRange *thiz, JsonNumber *number)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(number, false);

    if (thiz->min == NULL || thiz->max == NULL || thiz->step == NULL)
    {
        LOG_E(TAG, "check number value error, min/max/step is null");
        return false;
    }

    if (thiz->min->type != JSON_NUMBER)
    {
        LOG_E(TAG, "check number value error, min/max/step.type is not JsonNumber");
        return false;
    }

    if (number->type != thiz->min->data.number->type)
    {
        LOG_E(TAG, "check number value error, value type invalid: %d", number->type);
        return false;
    }

    if (number->type == JSON_NUMBER_INTEGER)
    {
        return ValueRange_CheckIntegerValue(thiz, number->value.intValue);
    }

    return ValueRange_CheckFloatValue(thiz, number->value.floatValue);
}

TINY_LOR
bool ValueRange_CheckValue(ValueRange *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    LOG_D(TAG, "ValueRange_CheckValue");

    switch (value->type)
    {
        case JSON_STRING:
            return ValueRange_CheckHexValue(thiz, value->data.string);

        case JSON_NUMBER:
            return ValueRange_CheckNumberValue(thiz, value->data.number);

        default:
            LOG_E(TAG, "ValueRange_CheckValue FAILED, value type error: %d", value->type);
            return false;
    }
}