/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ProductFactory.h
 *
 * @remark
 *
 */

#ifndef __PRODUCT_FACTORY_H__
#define __PRODUCT_FACTORY_H__

#include <tiny_base.h>
#include <api/iot_api.h>
#include <product/handler/PropertyHandler.h>
#include <product/Product.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
Product* Product_NewInstance(JsonObject *object, PropertyLock lock, PropertyUnlock unlock);

IOT_API
TINY_LOR
Product *ProductFactory_Create(uint16_t productId, uint16_t productVersion, uint32_t second);


TINY_END_DECLS

#endif /* __PRODUCT_FACTORY_H__ */