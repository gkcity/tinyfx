/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertySetter.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <JsonBoolean.h>
#include <JsonNumber.h>
#include <JsonString.h>
#include "PropertySetter.h"

#define TAG     "PropertySetter"

bool PropertySetter_Set(Property *property, JsonValue *value)
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