/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   DeviceHost.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <controlled/PropertyChangedObserver.h>
#include <error/IotStatus.h>
#include <operation/PropertyOperation.h>
#include <operation/AID.h>
#include "DeviceControllalbe.h"

#define TAG     "DeviceHost"

TINY_LOR
static TinyRet DeviceHost_Construct(DeviceControllable *thiz);

TINY_LOR
static void DeviceHost_Dispose(DeviceControllable *thiz);

TINY_LOR
static void accessory_release_handler(void *data, void *ctx)
{
    Device *p = (Device *)data;
    Device_Delete(p);
}

TINY_LOR
static void OnChangedObserverDelete (void * data, void *ctx)
{
    PropertyChangedObserver * oo = (PropertyChangedObserver *) data;
    PropertyChangedObserver_Delete(oo);
}

TINY_LOR
DeviceControllable* DeviceHost_New(void)
{
    DeviceControllable *thiz = NULL;

    do
    {
        thiz = (DeviceControllable *)tiny_malloc(sizeof(DeviceControllable));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(DeviceHost_Construct(thiz)))
        {
            DeviceHost_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet DeviceHost_Construct(DeviceControllable *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(DeviceControllable));

        ret = TinyList_Construct(&thiz->devices);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->devices.context = thiz;
        TinyList_SetDeleteListener(&thiz->devices, accessory_release_handler, thiz);

        ret = TinyList_Construct(&thiz->changedObservers);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        TinyList_SetDeleteListener(&thiz->changedObservers, OnChangedObserverDelete, thiz);
    } while (false);

    return ret;
}

TINY_LOR
static void DeviceHost_Dispose(DeviceControllable *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->changedObservers);
    TinyList_Dispose(&thiz->devices);
}

TINY_LOR
void DeviceHost_Delete(DeviceControllable *thiz)
{
    RETURN_IF_FAIL(thiz);

    DeviceHost_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void DeviceHost_InitializeInstanceID(DeviceControllable *thiz)
{
    uint16_t iid = 1;

    RETURN_IF_FAIL(thiz);

    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device *device = (Device *) TinyList_GetAt(&thiz->devices, i);
        Device_InitializeInstanceID(device, iid++);
    }
}

TINY_LOR
DeviceControllable* DeviceHost_Build(DeviceHostConfig *config)
{
    DeviceControllable * device = DeviceHost_New();
    if (device != NULL)
    {
        DeviceHostConfig_Copy(&device->config, config);
    }

    return device;
}

IOT_API
TINY_LOR
Device * DeviceHost_GetDevice(DeviceControllable *thiz, uint16_t diid)
{
    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device * d = (Device *)TinyList_GetAt(&thiz->devices, i);
        if (d->iid == diid)
        {
            return d;
        }
    }

    return NULL;
}

IOT_API
TINY_LOR
Service * DeviceHost_GetService(DeviceControllable *thiz, uint16_t diid, uint16_t siid)
{
    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device * d = (Device *)TinyList_GetAt(&thiz->devices, i);
        if (d->iid == diid)
        {
            for (uint32_t j = 0; j < d->services.size; ++j)
            {
                Service *s = (Service *) TinyList_GetAt(&d->services, j);
                if (s->iid == siid)
                {
                    return s;
                }
            }
        }
    }

    return NULL;
}

IOT_API
TINY_LOR
Action * DeviceHost_GetAction(DeviceControllable *thiz, uint16_t diid, uint16_t siid, uint16_t aiid)
{
    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device * d = (Device *)TinyList_GetAt(&thiz->devices, i);
        if (d->iid == diid)
        {
            for (uint32_t j = 0; j < d->services.size; ++j)
            {
                Service *s = (Service *) TinyList_GetAt(&d->services, j);
                if (s->iid == siid)
                {
                    for (uint32_t k = 0; k < s->actions.size; ++k)
                    {
                        Action *a = (Action *) TinyList_GetAt(&s->actions, k);
                        if (a->iid == aiid)
                        {
                            return a;
                        }
                    }
                }
            }
        }
    }

    return NULL;
}

TINY_LOR
Property * DeviceHost_GetProperty(DeviceControllable *thiz, uint16_t diid, uint16_t siid, uint16_t piid)
{
    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device * d = (Device *)TinyList_GetAt(&thiz->devices, i);
        if (d->iid == diid)
        {
            for (uint32_t j = 0; j < d->services.size; ++j)
            {
                Service *s = (Service *) TinyList_GetAt(&d->services, j);
                if (s->iid == siid)
                {
                    for (uint32_t k = 0; k < s->properties.size; ++k)
                    {
                        Property *p = (Property *) TinyList_GetAt(&s->properties, k);
                        if (p->iid == piid)
                        {
                            return p;
                        }
                    }
                }
            }
        }
    }

    return NULL;
}

TINY_LOR
static bool DeviceHost_NotifyPropertyChanged(DeviceControllable *thiz, Property *property)
{
    bool notified = false;

    if (property->changed)
    {
        for (uint32_t i = 0; i < thiz->changedObservers.size; ++i)
        {
            PropertyChangedObserver * observer = (PropertyChangedObserver *) TinyList_GetAt(&thiz->changedObservers, i);
            printf("PropertyChangedObserver: %d\n", i);
            observer->listener(property, observer->data, observer->ctx);
            notified = true;
        }

        property->changed = false;
    }

    return notified;
}

TINY_LOR
int DeviceHost_NotifyPropertiesChanged(DeviceControllable *thiz)
{
    int count = 0;

    LOG_D(TAG, "DeviceHost_NotifyPropertiesChanged");

    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        LOG_D(TAG, "Device: %d", i);
        Device * a = (Device *)TinyList_GetAt(&thiz->devices, i);
        for (uint32_t j = 0; j < a->services.size; ++j)
        {
            LOG_D(TAG, "Service: %d", j);
            Service *s = (Service *) TinyList_GetAt(&a->services, j);
            for (uint32_t k = 0; k < s->properties.size; ++k)
            {
                LOG_D(TAG, "Property: %d", k);
                Property *p = (Property *) TinyList_GetAt(&s->properties, k);
                if (DeviceHost_NotifyPropertyChanged(thiz, p))
                {
                    count ++;
                }
            }
        }
    }

    LOG_D(TAG, "Notify count: %d", count);

    return count;
}

TINY_LOR
void DeviceHost_OnPropertiesSet(DeviceControllable *thiz, PropertyOperations *beans)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(propertyBeans);

    for (uint32_t i = 0; i < beans->properties.size; ++i)
    {
        PropertyOperation *bean = (PropertyOperation *)TinyList_GetAt(&beans->properties, i);
        Property *property = DeviceHost_GetProperty(thiz, bean->pid.diid, bean->pid.siid, bean->pid.iid);
        if (property == NULL)
        {
            bean->status = IOT_STATUS_NOT_EXIST;
            continue;
        }

        if (! Property_IsReadable(property))
        {
            bean->status = IOT_STATUS_CANNOT_WRITE;
            continue;
        }

        if (property->onSet == NULL)
        {
            bean->status = IOT_STATUS_INTERNAL_ERROR;
            continue;
        }

        if (RET_FAILED(Data_Set(&bean->value, &property->data)))
        {
            bean->status = IOT_STATUS_VALUE_ERROR;
            continue;
        }

        property->onSet(property);
        bean->status = IOT_STATUS_OK;
    }
}

TINY_LOR
void DeviceHost_OnPropertiesGet(DeviceControllable *thiz, PropertyOperations *beans)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(propertyBeans);

    for (uint32_t i = 0; i < beans->properties.size; ++i)
    {
        PropertyOperation *bean = (PropertyOperation *)TinyList_GetAt(&beans->properties, i);
        Property *property = DeviceHost_GetProperty(thiz, bean->pid.diid, bean->pid.siid, bean->pid.iid);
        if (property == NULL)
        {
            bean->status = IOT_STATUS_NOT_EXIST;
            continue;
        }

        if (! Property_IsReadable(property))
        {
            bean->status = IOT_STATUS_CANNOT_READ;
            continue;
        }

        if (property->onGet == NULL)
        {
            bean->status = IOT_STATUS_INTERNAL_ERROR;
            continue;
        }

        property->onGet(property);

        if (RET_FAILED(Data_Copy(&bean->value, &property->data)))
        {
            bean->status = IOT_STATUS_INTERNAL_ERROR;
            continue;
        }

        bean->status = IOT_STATUS_OK;
    }
}

TINY_LOR
void DeviceHost_OnActionInvoke(DeviceControllable *thiz, ActionOperation *actionBean)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(actionBean);

    actionBean->status = IOT_STATUS_OK;

    do
    {
        Action *action = DeviceHost_GetAction(thiz, actionBean->aid.diid, actionBean->aid.siid, actionBean->aid.diid);
        if (action == NULL)
        {
            actionBean->status = IOT_STATUS_NOT_EXIST;
            break;
        }

        if (action->in.size != actionBean->in.properties.size)
        {
            actionBean->status = IOT_STATUS_ACTION_IN_ERROR;
            break;
        }

        if (action->onInvoke == NULL)
        {
            actionBean->status = IOT_STATUS_INTERNAL_ERROR;
            break;
        }

        for (uint32_t i = 0; i < action->in.size; ++i)
        {
            Property *property = (Property *)TinyList_GetAt(&action->in, i);
            PropertyOperation *bean = (PropertyOperation *)TinyList_GetAt(&actionBean->in.properties, i);

            if (RET_FAILED(Data_Set(&property->data, &bean->value)))
            {
                actionBean->status = IOT_STATUS_VALUE_ERROR;
                break;
            }
        }

        if (actionBean->status == IOT_STATUS_OK)
        {
            break;
        }

        action->onInvoke(action);

        for (uint32_t i = 0; i < action->out.size; ++i)
        {
            Property *property = (Property *)TinyList_GetAt(&action->out, i);
            PropertyOperation *bean = PropertyOperation_New();
            if (bean == NULL)
            {
                actionBean->status = IOT_STATUS_INTERNAL_ERROR;
                break;
            }

            bean->pid.diid = property->diid;
            bean->pid.siid = property->siid;
            bean->pid.iid = property->iid;
            Data_Copy(&bean->value, &property->data);

            TinyList_AddTail(&actionBean->out.properties, bean);
        }
    } while (false);
}