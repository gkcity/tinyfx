/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ValueList.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <value/JsonNumber.h>
#include <JsonArray.h>
#include "ValueList.h"

#define TAG     "ValueRange"

TINY_LOR
static void _OnValueDelete(void *data, void *ctx)
{
    JsonValue_Delete((JsonValue *)data);
}

TINY_LOR
static TinyRet ValueList_Construct(ValueList *thiz, JsonArray *array)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        ret = TinyList_Construct(&thiz->list);
        if (RET_FAILED(ret))
        {
            break;
        }

        TinyList_SetDeleteListener(&thiz->list, _OnValueDelete, thiz);

        for (int i = 0; i < array->values.size; ++i)
        {
            JsonValue * newValue = NULL;
            JsonValue * v = (JsonValue *) TinyList_GetAt(&array->values, i);
            if (v->type != JSON_NUMBER)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (v->data.number->type != JSON_NUMBER_INTEGER)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            newValue = JsonValue_Copy(v);
            if (newValue == NULL)
            {
                ret = TINY_RET_E_OUT_OF_MEMORY;
                break;
            }

            TinyList_AddTail(&thiz->list, newValue);
        }

    } while (false);

    return ret;
}

TINY_LOR
static void ValueList_Dispose(ValueList *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->list);
}

TINY_LOR
ValueList* ValueList_NewFrom(JsonArray *array)
{
    ValueList *thiz = NULL;

    do
    {
        thiz = (ValueList *)tiny_malloc(sizeof(ValueList));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ValueList_Construct(thiz, array)))
        {
            ValueList_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void ValueList_Delete(ValueList *thiz)
{
    RETURN_IF_FAIL(thiz);

    ValueList_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet ValueList_Put(ValueList *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    if (value->type != JSON_NUMBER)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    if (value->data.number->type != JSON_NUMBER_INTEGER)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    return TinyList_AddTail(&thiz->list, value);
}

TINY_LOR
bool ValueList_CheckValue(ValueList *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    if (value->type != JSON_NUMBER)
    {
        return false;
    }

    if (value->data.number->type != JSON_NUMBER_INTEGER)
    {
        return false;
    }

    for (int i = 0; i < thiz->list.size; ++i)
    {
        JsonValue * v = (JsonValue *) TinyList_GetAt(&thiz->list, i);

        if (v->data.number->value.intValue == value->data.number->value.intValue)
        {
            return true;
        }
    }

    return false;
}
