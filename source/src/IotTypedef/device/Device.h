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

#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "constant/iot_constant.h"
#include <TinyList.h>
#include <device/handler/DeviceIdentifyListener.h>
#include <device/handler/ActionOnInvoke.h>
#include <device/handler/EventOnOccurred.h>
#include <device/handler/PropertyOnControl.h>
#include <operation/PropertyOperations.h>
#include <operation/ActionOperation.h>

TINY_BEGIN_DECLS


typedef enum _InstanceIDStyle
{
    IID_STYLE_HOMEKIT = 0,
    IID_STYLE_XIOT = 1,
} InstanceIDStyle;

struct _Device
{
    char                        did[DEVICE_ID_LENGTH + 1];
    char                        ltsk[DEVICE_LTSK_LENGTH + 1];
    char                        type[DEVICE_TYPE_LENGTH];
    TinyList                    services;
    TinyList                    children;
    PropertyOnGet               onGet;
    PropertyOnSet               onSet;
    ActionOnInvoke              onInvoke;
    PropertyOnChanged           onChanged;
    EventOnOccurred             onEventOccurred;
    void                      * context;

//    DeviceIdentifyListener      identifyListener;
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
void Device_SetLtsk(Device *thiz, const char *ltsk);

IOT_API
TINY_LOR
void Device_InitializeIID(Device *thiz, InstanceIDStyle style);

IOT_API
TINY_LOR
void Device_SetHandler(Device *thiz, PropertyOnGet onGet, PropertyOnSet onSet, ActionOnInvoke onInvoke);

IOT_API
TINY_LOR
bool Device_CheckHandler(Device *thiz);

IOT_API
TINY_LOR
void Device_TryReadProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryWriteProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryInvokeAction(Device *thiz, ActionOperation *operation);

IOT_API
TINY_LOR
TinyRet Device_TryChangePropertyValue(Device *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
TinyRet Device_TryProduceEvent(Device *thiz, EventOperation *o);


TINY_END_DECLS

#endif /* __DEVICE_H__ */