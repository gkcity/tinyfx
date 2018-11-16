/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <operation/PropertyOperation.h>
#include <status/IotStatus.h>
#include "Property.h"
#include "Device.h"
#include "Service.h"
#include "Action.h"

#define TAG     "Device"

TINY_LOR
static TinyRet Device_Construct(Device *thiz);

TINY_LOR
static void Device_Dispose(Device *thiz);

TINY_LOR
static void service_release_handler(void *data, void *ctx)
{
    Service_Delete((Service *)data);
}

TINY_LOR
Device* Device_New(void)
{
    Device *thiz = NULL;

    do
    {
        thiz = (Device *)tiny_malloc(sizeof(Device));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Device_Construct(thiz)))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Device_Construct(Device *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Device));

        ret = TinyList_Construct(&thiz->services, service_release_handler, thiz);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->services.context = thiz;
    } while (false);

    return ret;
}

TINY_LOR
static void Device_Dispose(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->services);
}

TINY_LOR
void Device_Delete(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    Device_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
bool Device_CheckHandler(Device *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "Device_CheckHandler");

    if (thiz->onSet == NULL)
    {
        LOG_E(TAG, "Property Setter is null");
        return false;
    }

    if (thiz->onGet == NULL)
    {
        LOG_E(TAG, "Property Getter is null");
        return false;
    }

    if (thiz->onInvoke == NULL)
    {
        LOG_E(TAG, "Action Invocation is null");
    }

    return true;
}

TINY_LOR
static bool did_equals(Device *device, const char *did, uint16_t aid)
{
    if (device->config.accessoryConfig.aid > 0)
    {
        return (device->config.accessoryConfig.aid == aid);
    }

    return STR_EQUAL(device->config.did, did);
}

TINY_LOR
static Device * Device_GetChild(Device *thiz, const char * did, uint16_t aid)
{
    for (uint32_t i = 0; i < thiz->children.size; ++i)
    {
        Device * child = (Device *)TinyList_GetAt(&thiz->children, i);
        if (did_equals(child, did, aid))
        {
            return child;
        }
    }

    return NULL;
}

TINY_LOR
static Service * Device_GetService(Device *thiz, uint16_t siid)
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
static Property * Device_GetProperty(Device *thiz, uint16_t piid)
{
    for (uint32_t i = 0; i < thiz->services.size; ++i)
    {
        Service *s = (Service *) TinyList_GetAt(&thiz->services, i);
        Property *property = Service_GetProperty(s, piid);
        if (property != NULL)
        {
            return property;
        }
    }

    return NULL;
}

TINY_LOR
static void Device_TryRead(Device *thiz, PropertyOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    /**
     * only for homekit, siid always is 0
     */
    if (o->pid.siid == 0)
    {
        Property *property = Device_GetProperty(thiz, o->pid.iid);
        if (property != NULL)
        {
            Property_TryRead(property, o);
            if (o->status == IOT_STATUS_OK)
            {
                if (thiz->onGet != NULL)
                {
                    thiz->onGet(o);
                    Property_CheckValue(property, o->value);
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
    else
    {
        Service * service = Device_GetService(thiz, o->pid.siid);
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
}

TINY_LOR
static void Device_TryReadChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did, o->pid.aid);
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
static void Device_TryWrite(Device *thiz, PropertyOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    /**
     * only for homekit, siid always is 0
     */
    if (o->pid.siid == 0)
    {
        Property *property = Device_GetProperty(thiz, o->pid.iid);
        if (property != NULL)
        {
            Property_TryWrite(property, o);
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
    else
    {
        Service * service = Device_GetService(thiz, o->pid.siid);
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
}

/**
 * only for homekit, siid always is 0
 */
TINY_LOR
static void Device_TrySubscribe(Device *thiz, PropertyOperation *o)
{
    Property *property = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    property = Device_GetProperty(thiz, o->pid.iid);
    if (property != NULL)
    {
        Property_TrySubscribe(property, o);
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

/**
 * only for homekit, siid always is 0
 */
TINY_LOR
static void Device_TryUnsubscribe(Device *thiz, PropertyOperation *o)
{
    Property *property = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    property = Device_GetProperty(thiz, o->pid.iid);
    if (property != NULL)
    {
        Property_TryUnsubscribe(property, o);
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

TINY_LOR
static void Device_TryWriteChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did, o->pid.aid);
    if (child != NULL)
    {
        Device_TryWrite(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TrySubscribeChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did, o->pid.aid);
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
static void Device_TryUnsubscribeChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did, o->pid.aid);
    if (child != NULL)
    {
        Device_TryUnsubscribe(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryInvoke(Device *thiz, ActionOperation *o)
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
static void Device_TryInvokeChild(Device *thiz, ActionOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->aid.did, 0);
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
void Device_TryReadProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (did_equals(thiz, o->pid.did, o->pid.aid))
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
void Device_TryWriteProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (did_equals(thiz, o->pid.did, o->pid.aid))
        {
            Device_TryWrite(thiz, o);
        }
        else
        {
            Device_TryWriteChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TrySubscribeProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (did_equals(thiz, o->pid.did, o->pid.aid))
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
void Device_TryUnsubscribeProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (did_equals(thiz, o->pid.did, o->pid.aid))
        {
            Device_TryUnsubscribe(thiz, o);
        }
        else
        {
            Device_TryUnsubscribeChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TryInvokeAction(Device *thiz, ActionOperation *o)
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
TinyRet Device_TryChangePropertyValue(Device *thiz, PropertyOperation *o)
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
TinyRet Device_TryProduceEvent(Device *thiz, EventOperation *o)
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