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
#include "IotRuntime.h"
#include <bootstrap/Bootstrap.h>

TINY_BEGIN_DECLS


struct _IotLauncher
{
    bool                    started;
    IotRuntime           runtime;
    Bootstrap               bootstrap;
};

typedef struct _IotLauncher IotLauncher;

IOT_API
TINY_LOR
IotLauncher * IotLauncher_New(void);

IOT_API
TINY_LOR
void IotLauncher_Delete(IotLauncher *thiz);

IOT_API
TINY_LOR
TinyRet IotLauncher_Construct(IotLauncher *thiz);

IOT_API
TINY_LOR
void IotLauncher_Dispose(IotLauncher *thiz);

IOT_API
TINY_LOR
TinyRet IotLauncher_AddRuntime(IotLauncher *thiz, IotRuntime *runtime);

IOT_API
TINY_LOR
TinyRet IotLauncher_Run(IotLauncher *thiz, Device *device);

IOT_API
TINY_LOR
TinyRet IotLauncher_Stop(IotLauncher *thiz);



TINY_END_DECLS

#endif /* __IOT_LAUNCHER_H__ */