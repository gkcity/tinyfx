/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Thing.h
 *
 * @remark
 *
 */

#ifndef __THING_H__
#define __THING_H__

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


struct _Thing
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

typedef struct _Thing Thing;

IOT_API
TINY_LOR
Thing* Thing_New(void);

IOT_API
TINY_LOR
void Thing_Delete(Thing *thiz);

IOT_API
TINY_LOR
bool Thing_CheckHandler(Thing *thiz);



TINY_END_DECLS

#endif /* __THING_H__ */