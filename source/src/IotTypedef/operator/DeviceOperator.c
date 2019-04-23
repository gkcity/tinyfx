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
static Thing * Device_GetChild(Thing *thiz, const char * did)
{
    for (uint32_t i = 0; i < thiz->children.size; ++i)
    {
        Thing * child = (Thing *)TinyList_GetAt(&thiz->children, i);
        if (STR_EQUAL(child->config.did, did))
        {
            return child;
        }
    }

    return NULL;
}

TINY_LOR
static Service * Device_GetService(Thing *thiz, uint16_t siid)
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
static void Device_TryRead(Thing *thiz, PropertyOperation *o)
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
static void Device_TryReadChild(Thing *thiz, PropertyOperation *o)
{
    Thing *child = NULL;

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
static void Device_TryWrite(Thing *thiz, PropertyOperation *o)
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
static void Device_TrySubscribe(Thing *thiz, PropertyOperation *o)
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
static void Device_TryUnsubscribe(Thing *thiz, PropertyOperation *o)
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
static void Device_TryWriteChild(Thing *thiz, PropertyOperation *o)
{
    Thing *child = NULL;

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
static void Device_TrySubscribeChild(Thing *thiz, PropertyOperation *o)
{
    Thing *child = NULL;

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
static void Device_TryUnsubscribeChild(Thing *thiz, PropertyOperation *o)
{
    Thing *child = NULL;

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
static void Device_TryInvoke(Thing *thiz, ActionOperation *o)
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
static void Device_TryInvokeChild(Thing *thiz, ActionOperation *o)
{
    Thing *child = NULL;

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
void Device_TryReadProperties(Thing *thiz, PropertyOperations *operations)
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
void Device_TryWriteProperties(Thing *thiz, PropertyOperations *operations)
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
void Device_TrySubscribeProperties(Thing *thiz, PropertyOperations *operations)
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
void Device_TryUnsubscribeProperties(Thing *thiz, PropertyOperations *operations)
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
void Device_TryInvokeAction(Thing *thiz, ActionOperation *o)
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
TinyRet Device_TryChangePropertyValue(Thing *thiz, PropertyOperation *o)
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
TinyRet Device_TryProduceEvent(Thing *thiz, EventOperation *o)
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