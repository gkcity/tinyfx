/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   DeviceControllable.h
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
#include "DeviceConfig.h"
#include "device/Property.h"
#include "device/Service.h"
#include "device/Device.h"
#include "device/Action.h"


TINY_BEGIN_DECLS


struct _DeviceControllable
{
    Device                      device;
    DeviceConfig                config;
    TinyList                    children;
    TinyList                    changedObservers;
    DeviceIdentifyListener      identifyListener;
    void                      * context;
};

typedef struct _DeviceControllable DeviceControllable;

IOT_API
TINY_LOR
DeviceControllable* DeviceControllable_New(void);

IOT_API
TINY_LOR
void DeviceControllable_Delete(DeviceControllable *thiz);

IOT_API
TINY_LOR
void DeviceControllable_InitializeInstanceID(DeviceControllable *thiz);

IOT_API
TINY_LOR
DeviceControllable* DeviceControllable_Build(DeviceConfig *thiz);

IOT_API
TINY_LOR
Device * DeviceControllable_GetDevice(DeviceControllable *thiz, uint16_t diid);

IOT_API
TINY_LOR
Service * DeviceControllable_GetService(DeviceControllable *thiz, uint16_t diid, uint16_t siid);

IOT_API
TINY_LOR
Action * DeviceControllable_GetAction(DeviceControllable *thiz, uint16_t diid, uint16_t siid, uint16_t aiid);

IOT_API
TINY_LOR
Property * DeviceControllable_GetProperty(DeviceControllable *thiz, uint16_t diid, uint16_t siid, uint16_t piid);

IOT_API
TINY_LOR
int DeviceControllable_NotifyPropertiesChanged(DeviceControllable *thiz);

IOT_API
TINY_LOR
void DeviceControllable_OnPropertiesSet(DeviceControllable *thiz, PropertyOperations *properties);

IOT_API
TINY_LOR
void DeviceControllable_OnPropertiesGet(DeviceControllable *thiz, PropertyOperations *properties);

IOT_API
TINY_LOR
void DeviceControllable_OnActionInvoke(DeviceControllable *thiz, ActionOperation *action);



TINY_END_DECLS

#endif /* __DEVICE_HOST_H__ */