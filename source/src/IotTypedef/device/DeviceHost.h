/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   DeviceHost.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_HOST_H__
#define __DEVICE_HOST_H__

#include <controlled/DeviceIdentifyListener.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "DeviceHostConfig.h"
#include "Property.h"
#include "Service.h"


TINY_BEGIN_DECLS


struct _DeviceHost
{
    DeviceHostConfig            config;
    TinyList                    accessories;
    TinyList                    changedObservers;
    DeviceIdentifyListener      identifyListener;
    void                      * ctx;
};

typedef struct _DeviceHost DeviceHost;

IOT_API
TINY_LOR
DeviceHost* DeviceHost_New(void);

IOT_API
TINY_LOR
void DeviceHost_Delete(DeviceHost *thiz);

IOT_API
TINY_LOR
void DeviceHost_InitializeInstanceID(DeviceHost *thiz);

IOT_API
TINY_LOR
DeviceHost* DeviceHost_Build(DeviceHostConfig *thiz);

IOT_API
TINY_LOR
Property * DeviceHost_GetProperty(DeviceHost *thiz, uint16_t aid, uint16_t iid);

IOT_API
TINY_LOR
int DeviceHost_NotifyPropertiesChanged(DeviceHost *thiz);


TINY_END_DECLS

#endif /* __DEVICE_HOST_H__ */