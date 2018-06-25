/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   IotExecute.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <value/JsonBoolean.h>
#include <value/JsonNumber.h>
#include <value/JsonString.h>
#include <JsonObject.h>
#include <JsonArray.h>
#include "IotExcute.h"

#define TAG     "IotExecute"

TINY_LOR
bool IotExecute_SetProperty(Property *property, JsonValue *value)
{
    TinyRet ret = TINY_RET_E_ARG_INVALID;

    RETURN_VAL_IF_FAIL(property, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    switch (property->data.type)
    {
        case DATATYPE_BOOL:
            switch (value->type)
            {
                case JSON_BOOLEAN:
                    ret = Data_SetBoolValue(&property->data, value->data.boolean->value);
                    break;

                case JSON_NUMBER:
                    if (value->data.number->type == JSON_NUMBER_INTEGER)
                    {
                        ret = Data_SetBoolValue(&property->data, value->data.number->value.intValue == 1);
                    }
                    break;

                default:
                    break;
            }
            break;

        case DATATYPE_UINT8:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_INTEGER)
            {
                ret = Data_SetUint8Value(&property->data, (uint8_t) value->data.number->value.intValue);
            }
            break;

        case DATATYPE_UINT16:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_INTEGER)
            {
                ret = Data_SetUint16Value(&property->data, (uint16_t) value->data.number->value.intValue);
            }
            break;

        case DATATYPE_UINT32:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_INTEGER)
            {
                ret = Data_SetUint32Value(&property->data, (uint32_t) value->data.number->value.intValue);
            }
            break;

        case DATATYPE_UINT64:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_INTEGER)
            {
                ret = Data_SetUint64Value(&property->data, (uint64_t) value->data.number->value.intValue);
            }
            break;

        case DATATYPE_INT:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_INTEGER)
            {
                ret = Data_SetIntValue(&property->data, (int32_t) value->data.number->value.intValue);
            }
            break;

        case DATATYPE_FLOAT:
            if (value->type == JSON_NUMBER && value->data.number->type == JSON_NUMBER_FLOAT)
            {
                ret = Data_SetFloatValue(&property->data, value->data.number->value.floatValue);
            }
            break;

        case DATATYPE_STRING:
            if (value->type == JSON_STRING)
            {
                ret = Data_SetStringValue(&property->data, value->data.string->value);
            }
            break;

        default:
            break;
    }

    return (ret == TINY_RET_OK);
}

TINY_LOR
bool IotExecute_InvokeAction(Action *action, JsonArray *in)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(action, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(in, TINY_RET_E_ARG_NULL);

    do
    {
        if (action->in.size != in->values.size)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (action->in.size == 0)
        {
            break;
        }


        if (! JsonArray_CheckValuesType(in, JSON_OBJECT))
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        for (uint32_t i = 0; i < in->values.size; ++i)
        {
            Property *property = (Property *) TinyList_GetAt(&action->in, i);
            JsonObject *p = (JsonObject *) TinyList_GetAt(&in->values, i);
            JsonNumber *iid = JsonObject_GetNumber(p, "iid");
            JsonValue *value = JsonObject_GetValue(p, "value");

            if (iid == NULL || value == NULL)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (property->iid != iid->value.intValue)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (! IotExecute_SetProperty(property, value))
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }
        }
    } while (false);

    return (ret == TINY_RET_OK);
}