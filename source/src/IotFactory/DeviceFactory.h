/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceFactory.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_FACTORY_H__
#define __DEVICE_FACTORY_H__

#include <tiny_base.h>
#include <device/handler/PropertyHandler.h>
#include <api/iot_api.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
Device* Device_NewInstance(JsonObject *object);

IOT_API
TINY_LOR
Device *DeviceFactory_Create(uint16_t productId, uint16_t productVersion, uint32_t second);


TINY_END_DECLS

#endif /* __DEVICE_FACTORY_H__ */