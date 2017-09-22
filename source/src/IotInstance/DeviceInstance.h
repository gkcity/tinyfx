/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceInstance.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_INSTANCE_H__
#define __DEVICE_INSTANCE_H__

#include <tiny_base.h>
#include <controlled/PropertyOnControl.h>
#include <api/iot_api.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
Device* DeviceInstance_New(const char *ip, uint16_t port, const char *uri, uint32_t second);


TINY_END_DECLS

#endif /* __DEVICE_INSTANCE_H__ */