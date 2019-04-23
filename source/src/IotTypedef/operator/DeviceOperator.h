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
#include <product/Product.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
void Device_TryReadProperties(Product *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryWriteProperties(Product *thiz, PropertyOperations *operations);

#if 0
IOT_API
TINY_LOR
void Device_TrySubscribeProperties(Product *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Device_TryUnsubscribeProperties(Product *thiz, PropertyOperations *operations);
#endif

IOT_API
TINY_LOR
void Device_TryInvokeAction(Product *thiz, ActionOperation *operation);

IOT_API
TINY_LOR
TinyRet Device_TryChangePropertyValue(Product *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
TinyRet Device_TryProduceEvent(Product *thiz, EventOperation *o);


TINY_END_DECLS

#endif /* __DEVICE_OPERATOR_H__ */