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
#include <product/Product.h>

TINY_BEGIN_DECLS


struct _IotRuntime;
typedef struct _IotRuntime IotRuntime;

typedef TinyRet (* IotRuntime_Initialize)(IotRuntime *thiz);
typedef TinyRet (* IotRuntime_Destroy)(IotRuntime *thiz);
typedef TinyRet (* IotRuntime_Run)(IotRuntime *thiz, Bootstrap *bootstrap, Product *device);
typedef TinyRet (* IotRuntime_Stop)(IotRuntime *thiz);

struct _IotRuntime
{
    const char              * Name;
    IotRuntime_Initialize     Initialize;
    IotRuntime_Run            Run;
    IotRuntime_Stop           Stop;
    IotRuntime_Destroy        Destroy;
    Channel                 * channel;
    void                    * context;
};

IOT_API
TINY_LOR
IotRuntime * IotRuntime_New(void);

IOT_API
TINY_LOR
void IotRuntime_Delete(IotRuntime *thiz);


TINY_END_DECLS

#endif /* __IOT_RUNTIME_H__ */
