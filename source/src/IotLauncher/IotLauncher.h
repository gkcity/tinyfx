/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotLauncher.h
 *
 * @remark
 *
 */

#ifndef __IOT_LAUNCHER_H__
#define __IOT_LAUNCHER_H__

#include "tiny_base.h"
#include <TinyList.h>
#include <bootstrap/Bootstrap.h>
#include "IotRuntime.h"

TINY_BEGIN_DECLS


struct _IotLauncher
{
    Device                * device;
    bool                    started;
    TinyList                runtimes;
    Bootstrap               bootstrap;
};

typedef struct _IotLauncher IotLauncher;

IOT_API
TINY_LOR
IotLauncher * IotLauncher_New(Device *device);

IOT_API
TINY_LOR
IotLauncher * IotLauncher_NewRuntime(Device *device, IotRuntime *runtime, Channel *executor);

IOT_API
TINY_LOR
IotLauncher * IotLauncher_NewRuntime2(Device *device, IotRuntime *r1, IotRuntime *r2, Channel *executor);

IOT_API
TINY_LOR
IotLauncher * IotLauncher_NewRuntime3(Device *device, IotRuntime *r1, IotRuntime *r2, IotRuntime *r3, Channel *executor);

IOT_API
TINY_LOR
void IotLauncher_Delete(IotLauncher *thiz);

IOT_API
TINY_LOR
TinyRet IotLauncher_Construct(IotLauncher *thiz, Device *device);

IOT_API
TINY_LOR
void IotLauncher_Dispose(IotLauncher *thiz);

IOT_API
TINY_LOR
TinyRet IotLauncher_AddRuntime(IotLauncher *thiz, IotRuntime *runtime);

IOT_API
TINY_LOR
TinyRet IotLauncher_Run(IotLauncher *thiz);

IOT_API
TINY_LOR
TinyRet IotLauncher_Stop(IotLauncher *thiz);



TINY_END_DECLS

#endif /* __IOT_LAUNCHER_H__ */
