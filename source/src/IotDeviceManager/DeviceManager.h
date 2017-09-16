/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceManager.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include "tiny_base.h"
#include "DeviceRuntime.h"
#include <device/DeviceHost.h>

TINY_BEGIN_DECLS


struct _DeviceManager
{
    bool                    started;
    DeviceRuntime           runtime;
};

typedef struct _DeviceManager DeviceManager;

//IOT_API
//TINY_LOR
//DeviceManager * DeviceManager_New(void);
//
//IOT_API
//TINY_LOR
//void DeviceManager_Delete(DeviceManager *thiz);

IOT_API
TINY_LOR
TinyRet DeviceManager_Construct(DeviceManager *thiz);

IOT_API
TINY_LOR
void DeviceManager_Dispose(DeviceManager *thiz);

IOT_API
TINY_LOR
TinyRet DeviceManager_SetRuntimeImpl(DeviceManager *thiz, DeviceRuntime *impl);

IOT_API
TINY_LOR
TinyRet DeviceManager_Run(DeviceManager *thiz, DeviceHost *host);

IOT_API
TINY_LOR
TinyRet DeviceManager_Stop(DeviceManager *thiz);



TINY_END_DECLS

#endif /* __DEVICE_MANAGER_H__ */
