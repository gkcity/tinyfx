/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ProductOperator.h
 *
 * @remark
 *
 */

#ifndef __PRODUCT_OPERATOR_H__
#define __PRODUCT_OPERATOR_H__

#include <tiny_base.h>
#include <product/Product.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
void Product_TryReadProperties(Product *thiz, PropertyOperations *operations);

IOT_API
TINY_LOR
void Product_TryWriteProperties(Product *thiz, PropertyOperations *operations);

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
void Product_TryInvokeAction(Product *thiz, ActionOperation *operation);

IOT_API
TINY_LOR
TinyRet Product_TryChangePropertyValue(Product *thiz, PropertyOperation *o, bool save);

IOT_API
TINY_LOR
TinyRet Product_TryProduceEvent(Product *thiz, EventOperation *o);

IOT_API
TINY_LOR
TinyRet Product_DoChangePropertyValue(Product *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
PropertyOperations * Product_GetChangedProperties(Product *thiz);


TINY_END_DECLS

#endif /* __PRODUCT_OPERATOR_H__ */