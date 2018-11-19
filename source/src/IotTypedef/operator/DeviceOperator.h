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
#include <device/Device.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
void Device_TryReadProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryWriteProperties(Device *thiz, PropertyOperations *operations);

#if 0
IOT_API
TINY_LOR
void Device_TrySubscribeProperties(Device *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryUnsubscribeProperties(Device *thiz, PropertyOperations *operations);
#endif

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

#endif /* __DEVICE_OPERATOR_H__ */