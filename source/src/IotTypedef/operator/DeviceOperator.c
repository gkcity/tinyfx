/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   DeviceOperator.c
 *
 * @remark
 *
 */

#include <device/Service.h>
#include <status/IotStatus.h>
#include "DeviceOperator.h"

TINY_LOR
static Product * Device_GetChild(Product *thiz, const char * did)
{
    for (uint32_t i = 0; i < thiz->children.size; ++i)
    {
        Product * child = (Product *)TinyList_GetAt(&thiz->children, i);
        if (STR_EQUAL(child->config.did, did))
        {
            return child;
        }
    }

    return NULL;
}

TINY_LOR
static Service * Device_GetService(Product *thiz, uint16_t siid)
{
    for (uint32_t i = 0; i < thiz->services.size; ++i)
    {
        Service *s = (Service *) TinyList_GetAt(&thiz->services, i);
        if (s->iid == siid)
        {
            return s;
        }
    }

    return NULL;
}

TINY_LOR
static void Device_TryRead(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryRead(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onGet != NULL)
            {
                thiz->onGet(o);
                Service_CheckValue(service, o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryReadChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TryRead(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryWrite(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryWrite(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onSet != NULL)
            {
                thiz->onSet(o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

#if 0
TINY_LOR
static void Device_TrySubscribe(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TrySubscribe(service, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryUnsubscribe(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryUnsubscribe(service, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}
#endif

TINY_LOR
static void Device_TryWriteChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TryWrite(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

#if 0
TINY_LOR
static void Device_TrySubscribeChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TrySubscribe(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryUnsubscribeChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TryUnsubscribe(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}
#endif

TINY_LOR
static void Device_TryInvoke(Product *thiz, ActionOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->aid.siid);
    if (service != NULL)
    {
        Service_TryInvoke(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onInvoke != NULL)
            {
                thiz->onInvoke(o);
                Service_CheckResult(service, o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryInvokeChild(Product *thiz, ActionOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->aid.did);
    if (child != NULL)
    {
        Device_TryInvoke(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
void Device_TryReadProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Device_TryRead(thiz, o);
        }
        else
        {
            Device_TryReadChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TryWriteProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Device_TryWrite(thiz, o);
        }
        else
        {
            Device_TryWriteChild(thiz, o);
        }
    }
}

#if 0
TINY_LOR
void Device_TrySubscribeProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Device_TrySubscribe(thiz, o);
        }
        else
        {
            Device_TrySubscribeChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TryUnsubscribeProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Device_TryUnsubscribe(thiz, o);
        }
        else
        {
            Device_TryUnsubscribeChild(thiz, o);
        }
    }
}
#endif

TINY_LOR
void Device_TryInvokeAction(Product *thiz, ActionOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    if (STR_EQUAL(thiz->config.did, o->aid.did))
    {
        Device_TryInvoke(thiz, o);
    }
    else
    {
        Device_TryInvokeChild(thiz, o);
    }
}

TINY_LOR
TinyRet Device_TryChangePropertyValue(Product *thiz, PropertyOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Device_GetService(thiz, o->pid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryChange(service, o);
    } while (false);

    return ret;
}

TINY_LOR
TinyRet Device_TryProduceEvent(Product *thiz, EventOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Device_GetService(thiz, o->eid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryProduce(service, o);
    } while (false);

    return ret;
}