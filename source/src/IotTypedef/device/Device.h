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

#include <api/iot_api.h>
#include <tiny_base.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


struct _Device
{
    TinyList                    services;
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
TinyRet Device_Construct(Device *thiz);

IOT_API
TINY_LOR
void Device_Dispose(Device *thiz);


TINY_END_DECLS

#endif /* __DEVICE_H__ */