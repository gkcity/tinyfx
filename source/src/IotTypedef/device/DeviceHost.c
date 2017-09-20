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
#include "DeviceHost.h"
#include "Device.h"

#define TAG     "DeviceHost"

TINY_LOR
static TinyRet DeviceHost_Construct(DeviceHost *thiz);

TINY_LOR
static void DeviceHost_Dispose(DeviceHost *thiz);

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
DeviceHost* DeviceHost_New(void)
{
    DeviceHost *thiz = NULL;

    do
    {
        thiz = (DeviceHost *)tiny_malloc(sizeof(DeviceHost));
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
static TinyRet DeviceHost_Construct(DeviceHost *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(DeviceHost));

        ret = TinyList_Construct(&thiz->devices);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->devices.additionalData = thiz;
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
static void DeviceHost_Dispose(DeviceHost *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->changedObservers);
    TinyList_Dispose(&thiz->devices);
}

TINY_LOR
void DeviceHost_Delete(DeviceHost *thiz)
{
    RETURN_IF_FAIL(thiz);

    DeviceHost_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void DeviceHost_InitializeInstanceID(DeviceHost *thiz)
{
    uint16_t aid = 1;

    RETURN_IF_FAIL(thiz);

    for (uint32_t i = 0; i < thiz->devices.size; ++i)
    {
        Device *a = (Device *) TinyList_GetAt(&thiz->devices, i);
        Device_InitializeHomeKitInstanceID(a, aid++);
    }
}

TINY_LOR
DeviceHost* DeviceHost_Build(DeviceHostConfig *config)
{
    DeviceHost * device = DeviceHost_New();
    if (device != NULL)
    {
        DeviceHostConfig_Copy(&device->config, config);
    }

    return device;
}

TINY_LOR
Property * DeviceHost_GetProperty(DeviceHost *thiz, uint16_t diid, uint16_t siid, uint16_t piid)
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
static bool DeviceHost_NotifyPropertyChanged(DeviceHost *thiz, Property *property)
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
int DeviceHost_NotifyPropertiesChanged(DeviceHost *thiz)
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