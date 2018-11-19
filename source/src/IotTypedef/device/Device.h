/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <tiny_base.h>
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "constant/iot_constant.h"
#include <TinyList.h>
#include <device/config/DeviceConfig.h>
#include <device/handler/DeviceIdentifyListener.h>
#include <device/handler/ActionHandler.h>
#include <device/handler/PropertyHandler.h>
#include <operation/PropertyOperations.h>
#include <operation/ActionOperation.h>
#include <operation/EventOperation.h>

TINY_BEGIN_DECLS


struct _Device
{
    DeviceConfig                config;
    TinyList                    children;
    TinyList                    services;
    PropertyOnGet               onGet;
    PropertyOnSet               onSet;
    ActionOnInvoke              onInvoke;
    void                      * context;
    DeviceIdentifyListener      identifyListener;
};

typedef struct _Device Device;

IOT_API
TINY_LOR
Device* Device_New(void);

IOT_API
TINY_LOR
void Device_Delete(Device *thiz);

IOT_API
TINY_LOR
bool Device_CheckHandler(Device *thiz);



TINY_END_DECLS

#endif /* __DEVICE_H__ */