/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Property.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <status/IotStatus.h>
#include <value/JsonNumber.h>
#include "Property.h"

#define TAG     "Property"

TINY_LOR
static TinyRet Property_Construct(Property *thiz);

TINY_LOR
static void Property_Dispose(Property *thiz);

TINY_LOR
Property* Property_New(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = (Property *)tiny_malloc(sizeof(Property));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Property_Construct(thiz)))
        {
            Property_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Property_Construct(Property *thiz)
{
    TinyRet ret;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Property));

        ret = Urn_Construct(&thiz->type);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Urn_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static void Property_Dispose(Property *thiz)
{
    RETURN_IF_FAIL(thiz);

    Urn_Dispose(&thiz->type);

    if (thiz->valueList != NULL)
    {
        ValueList_Delete(thiz->valueList);
        thiz->valueList = NULL;
    }

    if (thiz->valueRange != NULL)
    {
        ValueRange_Delete(thiz->valueRange);
        thiz->valueRange = NULL;
    }
}

TINY_LOR
void Property_Delete(Property *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Property_Delete (iid: %d)", thiz->iid);

    Property_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
static bool Property_CheckValueType(Property *thiz, JsonValue* value)
{
    RETURN_VAL_IF_FAIL(thiz, false);
    RETURN_VAL_IF_FAIL(value, false);

    switch (thiz->format)
    {
        case FORMAT_BOOL:
            return (value->type == JSON_BOOLEAN);

        case FORMAT_STRING:
            return (value->type == JSON_STRING);

        case FORMAT_FLOAT:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_FLOAT)
                {
                    return true;
                }
            }
            return false;

        case FORMAT_UINT8:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_UINT8, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_UINT16:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_UINT16, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_UINT32:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_UINT32, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_INT8:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_INT8, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_INT16:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_INT16, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_INT32:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_INT32, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_INT64:
            if (value->type == JSON_NUMBER)
            {
                if (value->data.number->type == JSON_NUMBER_INTEGER)
                {
                    return Format_CheckInteger(FORMAT_INT64, value->data.number->value.intValue);
                }
            }
            return false;

        case FORMAT_HEX:
            return (value->type == JSON_STRING);

        default:
            return false;
    }
}

TINY_LOR
bool Property_CheckValue(Property *thiz, JsonValue* value)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "Property_CheckValue: %d", thiz->iid);

    if (value == NULL)
    {
        return false;
    }

    if (! Property_CheckValueType(thiz, value))
    {
        return false;
    }

    if (thiz->valueRange != NULL)
    {
        return ValueRange_CheckValue(thiz->valueRange, value);
    }

    if (thiz->valueList != NULL)
    {
        return ValueList_CheckValue(thiz->valueList, value);
    }

    return true;
}

TINY_LOR
void Property_TryRead(Property *thiz, PropertyOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    LOG_D(TAG, "Property_TryRead: %d", thiz->iid);

    if (! Access_IsReadable(thiz->access))
    {
        o->status = IOT_STATUS_CANNOT_READ;
    }
}

TINY_LOR
void Property_TryWrite(Property *thiz, PropertyOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    LOG_D(TAG, "Property_TryWrite: %d", thiz->iid);

    do
    {
        if (! Access_IsWritable(thiz->access))
        {
            o->status = IOT_STATUS_CANNOT_WRITE;
            break;
        }

        if (! Property_CheckValue(thiz, o->value))
        {
            o->status = IOT_STATUS_VALUE_ERROR;
            break;
        }
    } while (false);
}

TINY_LOR
void Property_TryChange(Property *thiz, PropertyOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    LOG_D(TAG, "Property_TryChange: %d", thiz->iid);

    do
    {
        if (! Access_IsNotifiable(thiz->access))
        {
            o->status = IOT_STATUS_CANNOT_NOTIFY;
            break;
        }

        if (! Property_CheckValue(thiz, o->value))
        {
            o->status = IOT_STATUS_VALUE_ERROR;
            break;
        }
    } while (false);
}