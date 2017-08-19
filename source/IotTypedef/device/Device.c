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
#include <controlled/PropertyChangedObserver.h>
#include "Device.h"
#include "Accessory.h"

#define TAG     "Device"

TINY_LOR
static TinyRet Device_Construct(Device *thiz);

TINY_LOR
static void Device_Dispose(Device *thiz);

TINY_LOR
static void accessory_release_handler(void *data, void *ctx)
{
    Accessory *p = (Accessory *)data;
    Accessory_Delete(p);
}

TINY_LOR
static void OnChangedObserverDelete (void * data, void *ctx)
{
    PropertyChangedObserver * oo = (PropertyChangedObserver *) data;
    PropertyChangedObserver_Delete(oo);
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

        ret = TinyList_Construct(&thiz->accessories);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->accessories.additionalData = thiz;
        TinyList_SetDeleteListener(&thiz->accessories, accessory_release_handler, thiz);

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
static void Device_Dispose(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->changedObservers);
    TinyList_Dispose(&thiz->accessories);
}

TINY_LOR
void Device_Delete(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    Device_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void Device_InitializeInstanceID(Device *thiz)
{
    uint16_t aid = 1;

    RETURN_IF_FAIL(thiz);

    for (uint32_t i = 0; i < thiz->accessories.size; ++i)
    {
        Accessory *a = (Accessory *) TinyList_GetAt(&thiz->accessories, i);
        Accessory_InitializeInstanceID(a, aid++);
    }
}

TINY_LOR
Device* Device_Build(DeviceConfig *config)
{
    Device * device = Device_New();
    if (device != NULL)
    {
        DeviceConfig_Copy(&device->config, config);
    }

    return device;
}

TINY_LOR
Property * Device_GetProperty(Device *device, uint16_t aid, uint16_t iid)
{
    for (uint32_t i = 0; i < device->accessories.size; ++i)
    {
        Accessory * a = (Accessory *)TinyList_GetAt(&device->accessories, i);
        if (a->iid == aid)
        {
            for (uint32_t j = 0; j < a->services.size; ++j)
            {
                Service *s = (Service *) TinyList_GetAt(&a->services, j);

                for (uint32_t k = 0; k < s->properties.size; ++k)
                {
                    Property *p = (Property *) TinyList_GetAt(&s->properties, k);
                    if (p->iid == iid)
                    {
                        return p;
                    }
                }
            }
        }
    }

    return NULL;
}

TINY_LOR
static bool Device_NotifyPropertyChanged(Device *thiz, Property *property)
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
int Device_NotifyPropertiesChanged(Device *thiz)
{
    int count = 0;

    LOG_D(TAG, "Device_NotifyPropertiesChanged");

    for (uint32_t i = 0; i < thiz->accessories.size; ++i)
    {
        LOG_D(TAG, "Accessory: %d", i);
        Accessory * a = (Accessory *)TinyList_GetAt(&thiz->accessories, i);
        for (uint32_t j = 0; j < a->services.size; ++j)
        {
            LOG_D(TAG, "Service: %d", j);
            Service *s = (Service *) TinyList_GetAt(&a->services, j);
            for (uint32_t k = 0; k < s->properties.size; ++k)
            {
                LOG_D(TAG, "Property: %d", k);
                Property *p = (Property *) TinyList_GetAt(&s->properties, k);
                if (Device_NotifyPropertyChanged(thiz, p))
                {
                    count ++;
                }
            }
        }
    }

    LOG_D(TAG, "Notify count: %d", count);

    return count;
}