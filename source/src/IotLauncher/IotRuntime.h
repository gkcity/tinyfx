/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotRuntime.h
 *
 * @remark
 *
 */

#ifndef __IOT_RUNTIME_H__
#define __IOT_RUNTIME_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <device/Service.h>
#include <bootstrap/Bootstrap.h>
#include <device/Device.h>

TINY_BEGIN_DECLS


struct _IotRuntime;
typedef struct _IotRuntime IotRuntime;

typedef TinyRet (* Device_Initialize)(IotRuntime *thiz);
typedef TinyRet (* Device_Destroy)(IotRuntime *thiz);
typedef TinyRet (* Device_Run)(IotRuntime *thiz, Bootstrap *bootstrap, Device *device);
typedef TinyRet (* Device_Stop)(IotRuntime *thiz);

struct _IotRuntime
{
    const char            * Name;
    Device_Initialize       Initialize;
    Device_Run              Run;
    Device_Stop             Stop;
    Device_Destroy          Destroy;
    void                  * context;
};

IOT_API
TINY_LOR
IotRuntime * IotRuntime_New(void);

IOT_API
TINY_LOR
void IotRuntime_Delete(IotRuntime *thiz);

IOT_API
TINY_LOR
void IotRuntime_Copy(IotRuntime *dst, IotRuntime *src);


TINY_END_DECLS

#endif /* __IOT_RUNTIME_H__ */
