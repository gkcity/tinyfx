/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   DeviceOperator.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_OPERATOR_H__
#define __DEVICE_OPERATOR_H__

#include <tiny_base.h>
#include <thing/Thing.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
void Device_TryReadProperties(Thing *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryWriteProperties(Thing *thiz, PropertyOperations *operations);

#if 0
IOT_API
TINY_LOR
void Device_TrySubscribeProperties(Thing *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryUnsubscribeProperties(Thing *thiz, PropertyOperations *operations);
#endif

IOT_API
TINY_LOR
void Device_TryInvokeAction(Thing *thiz, ActionOperation *operation);

IOT_API
TINY_LOR
TinyRet Device_TryChangePropertyValue(Thing *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
TinyRet Device_TryProduceEvent(Thing *thiz, EventOperation *o);


TINY_END_DECLS

#endif /* __DEVICE_OPERATOR_H__ */