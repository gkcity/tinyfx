/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Product.h
 *
 * @remark
 *
 */

#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <tiny_base.h>
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "constant/iot_constant.h"
#include <TinyList.h>
#include <product/config/ProductConfig.h>
#include <product/handler/DeviceIdentifyListener.h>
#include <product/handler/ActionHandler.h>
#include <product/handler/PropertyHandler.h>
#include <operation/PropertyOperations.h>
#include <operation/ActionOperation.h>
#include <operation/EventOperation.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


struct _Product
{
    ProductConfig               config;
    Device                      device;
    TinyList                    children;
    PropertyOnGet               onGet;
    PropertyOnSet               onSet;
    ActionOnInvoke              onInvoke;
    void                      * context;
    DeviceIdentifyListener      identifyListener;
};

typedef struct _Product Product;

IOT_API
TINY_LOR
Product* Product_New(void);

IOT_API
TINY_LOR
void Product_Delete(Product *thiz);

IOT_API
TINY_LOR
bool Product_CheckHandler(Product *thiz);



TINY_END_DECLS

#endif /* __PRODUCT_H__ */