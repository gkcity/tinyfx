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

#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include <TinyList.h>

TINY_BEGIN_DECLS


struct _Device
{
    uint16_t            iid;
    TinyList            services;
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
void Device_InitializeHomeKitInstanceID(Device *thiz, uint16_t aid);


TINY_END_DECLS

#endif /* __DEVICE_H__ */