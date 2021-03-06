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
#include <value/JsonString.h>
#include <tiny_str_equal.h>
#include <JsonObject.h>
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
        ret = TinyList_Construct(&thiz->list, _OnValueDelete, thiz);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "TinyList_Construct FAILED");
            break;
        }

        if (array != NULL)
        {
            for (uint32_t i = 0; i < array->values.size; ++i)
            {
                JsonValue * value = NULL;
                JsonValue * object = NULL;
                JsonValue * newValue = NULL;
                object = (JsonValue *) TinyList_GetAt(&array->values, i);
                if (object->type != JSON_OBJECT)
                {
                    LOG_E(TAG, "JsonValue not a JsonObject");
                    ret = TINY_RET_E_ARG_INVALID;
                    break;
                }

                value = JsonObject_GetValue(object->data.object, "value");
                if (value == NULL)
                {
                    LOG_E(TAG, "item not contains 'value' field");
                    ret = TINY_RET_E_ARG_INVALID;
                    break;
                }

                newValue = JsonValue_NewFrom(value);
                if (newValue == NULL)
                {
                    LOG_E(TAG, "JsonValue_Copy FAILED");
                    ret = TINY_RET_E_OUT_OF_MEMORY;
                    break;
                }

                ret = TinyList_AddTail(&thiz->list, newValue);
                if (RET_FAILED(ret))
                {
                    LOG_E(TAG, "TinyList_AddTail FAILED");
                    JsonValue_Delete(newValue);
                    break;
                }
            }
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
ValueList* ValueList_New(void)
{
    ValueList *thiz = NULL;

    do
    {
        thiz = (ValueList *)tiny_malloc(sizeof(ValueList));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ValueList_Construct(thiz, NULL)))
        {
            LOG_E(TAG, "ValueList_Construct FAILED");
            ValueList_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
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
            LOG_E(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ValueList_Construct(thiz, array)))
        {
            LOG_E(TAG, "ValueList_Construct FAILED");
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
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    do
    {
        JsonValue *newValue = JsonValue_NewFrom(value);
        if (newValue == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret= TinyList_AddTail(&thiz->list, newValue);
        if (RET_FAILED(ret))
        {
            JsonValue_Delete(newValue);
            break;
        }
    } while (false);

    return  ret;
}

TINY_LOR
static bool ValueList_CheckIntegerValue(ValueList *thiz, JsonNumber *number)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(number, false);

    if (number->type != JSON_NUMBER_INTEGER)
    {
        LOG_E(TAG, "ValueList_CheckIntegerValue FAILED, number not integer");
        return false;
    }

    LOG_D(TAG, "ValueList_CheckIntegerValue: %ld", number->value.intValue);

    for (uint32_t i = 0; i < thiz->list.size; ++i)
    {
        JsonValue * v = (JsonValue *) TinyList_GetAt(&thiz->list, i);

        if (v->data.number->value.intValue == number->value.intValue)
        {
            return true;
        }
    }

    LOG_E(TAG, "ValueList_CheckIntegerValue FAILED, invalid value: %ld", number->value.intValue);

    return false;
}

TINY_LOR
static bool ValueList_CheckStringValue(ValueList *thiz, JsonString *string)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(string, false);

    LOG_D(TAG, "ValueList_CheckStringValue: %s", string->value);

    for (uint32_t i = 0; i < thiz->list.size; ++i)
    {
        JsonValue * v = (JsonValue *) TinyList_GetAt(&thiz->list, i);

        if (str_equal(v->data.string->value, string->value, true))
        {
            return true;
        }
    }

    LOG_E(TAG, "ValueList_CheckStringValue FAILED, invalid value: %s", string->value);

    return false;
}

TINY_LOR
bool ValueList_CheckValue(ValueList *thiz, JsonValue *value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    LOG_D(TAG, "ValueList_CheckValue");

    switch (value->type)
    {
        case JSON_NUMBER:
            return ValueList_CheckIntegerValue(thiz, value->data.number);

        case JSON_STRING:
            return ValueList_CheckStringValue(thiz, value->data.string);

        default:
            LOG_E(TAG, "ValueList_CheckValue FAILED, value type error: %d", value->type);
            return false;
    }
}
