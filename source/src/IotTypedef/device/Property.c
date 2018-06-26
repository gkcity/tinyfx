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

        ret = Data_Construct(&thiz->data);
        if (RET_FAILED(ret)) {
            LOG_D(TAG, "Data_Construct FAILED: %s", tiny_ret_to_str(ret));
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
    Data_Dispose(&thiz->data);
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
bool Property_IsReadable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_READ) != 0);
}

TINY_LOR
bool Property_IsWritable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_WRITE) != 0);
}

TINY_LOR
bool Property_IsNotifiable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_NOTIFY) != 0);
}

TINY_LOR
void Property_TryRead(Property *thiz, PropertyOperation *o)
{
//    do
//    {
//
//
//
//        Property *property = Device_GetProperty(thiz, o->pid.did, o->pid.siid, o->pid.iid);
//        if (property == NULL)
//        {
//            o->status = IOT_STATUS_NOT_EXIST;
//            break;
//        }
//
//        if (! Property_IsReadable(property))
//        {
//            bean->status = IOT_STATUS_CANNOT_READ;
//            continue;
//        }
//
//        if (property->onGet == NULL)
//        {
//            bean->status = IOT_STATUS_INTERNAL_ERROR;
//            continue;
//        }
//
//        property->onGet(property);
//
//        if (RET_FAILED(Data_Copy(&bean->value, &property->data)))
//        {
//            bean->status = IOT_STATUS_INTERNAL_ERROR;
//            continue;
//        }
//
//        bean->status = IOT_STATUS_OK;
//    }
//    while (false);
}

TINY_LOR
void Property_TryWrite(Property *thiz, PropertyOperation *o)
{

//    for (uint32_t i = 0; i < operations->properties.size; ++i)
//    {
//        PropertyOperation *o = (PropertyOperation *) TinyList_GetAt(&operations->properties, i);
//
//        Property *property = DeviceControllable_GetProperty(thiz, o->pid.diid, o->pid.siid, o->pid.iid);
//        if (property == NULL)
//        {
//            bean->status = IOT_STATUS_NOT_EXIST;
//            continue;
//        }
//
//        if (!Property_IsReadable(property))
//        {
//            bean->status = IOT_STATUS_CANNOT_WRITE;
//            continue;
//        }
//
//        if (property->onSet == NULL)
//        {
//            bean->status = IOT_STATUS_INTERNAL_ERROR;
//            continue;
//        }
//
//        if (RET_FAILED(Data_Set(&bean->value, &property->data)))
//        {
//            bean->status = IOT_STATUS_VALUE_ERROR;
//            continue;
//        }
//
//        property->onSet(property);
//        bean->status = IOT_STATUS_OK;
//    }
}

TINY_LOR
bool Property_TrySet(Property *thiz, JsonValue* value)
{

}