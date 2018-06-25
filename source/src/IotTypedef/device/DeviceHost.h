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
#include <operation/ActionOperation.h>
#include <tiny_base.h>
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "DeviceHostConfig.h"
#include "Property.h"
#include "Service.h"
#include "Device.h"
#include "Action.h"


TINY_BEGIN_DECLS


struct _DeviceHost
{
    DeviceHostConfig            config;
    TinyList                    devices;
    TinyList                    changedObservers;
    DeviceIdentifyListener      identifyListener;
    void                      * context;
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
Device * DeviceHost_GetDevice(DeviceHost *thiz, uint16_t diid);

IOT_API
TINY_LOR
Service * DeviceHost_GetService(DeviceHost *thiz, uint16_t diid, uint16_t siid);

IOT_API
TINY_LOR
Action * DeviceHost_GetAction(DeviceHost *thiz, uint16_t diid, uint16_t siid, uint16_t aiid);

IOT_API
TINY_LOR
Property * DeviceHost_GetProperty(DeviceHost *thiz, uint16_t diid, uint16_t siid, uint16_t piid);

IOT_API
TINY_LOR
int DeviceHost_NotifyPropertiesChanged(DeviceHost *thiz);

IOT_API
TINY_LOR
void DeviceHost_OnPropertiesSet(DeviceHost *thiz, PropertyOperations *beans);

IOT_API
TINY_LOR
void DeviceHost_OnPropertiesGet(DeviceHost *thiz, PropertyOperations *beans);

IOT_API
TINY_LOR
void DeviceHost_OnActionInvoke(DeviceHost *thiz, ActionOperation *actionBean);



TINY_END_DECLS

#endif /* __DEVICE_HOST_H__ */