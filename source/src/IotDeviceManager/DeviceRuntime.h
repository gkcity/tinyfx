/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceRuntime.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_RUNTIME_H__
#define __DEVICE_RUNTIME_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <device/DeviceHost.h>
#include <device/Service.h>
#include <bootstrap/Bootstrap.h>

TINY_BEGIN_DECLS


struct _DeviceRuntime;
typedef struct _DeviceRuntime DeviceRuntime;

typedef TinyRet (* Device_Initialize)(DeviceRuntime *thiz);
typedef TinyRet (* Device_Destroy)(DeviceRuntime *thiz);
typedef TinyRet (* Device_Run)(DeviceRuntime *thiz, Bootstrap *bootstrap, DeviceHost *host);
typedef TinyRet (* Device_Stop)(DeviceRuntime *thiz);

struct _DeviceRuntime
{
    const char            * Name;
    Device_Initialize       Initialize;
    Device_Run              Run;
    Device_Stop             Stop;
    Device_Destroy          Destroy;
    void                  * context;
};

TINY_LOR
void DeviceRuntime_Copy(DeviceRuntime *dst, DeviceRuntime *src);


TINY_END_DECLS

#endif /* __DEVICE_RUNTIME_H__ */
