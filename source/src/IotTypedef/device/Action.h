/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Action.h
 *
 * @remark
 *
 */

#ifndef __ACTION_H__
#define __ACTION_H__

#include <TinyList.h>
#include <device/handler/ActionOnInvoke.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"

TINY_BEGIN_DECLS


struct _Action
{
    uint16_t            iid;
    Urn                 type;
    TinyList            in;
    TinyList            out;
    void *              service;
};

typedef struct _Action Action;

IOT_API
TINY_LOR
Action* Action_New(uint16_t iid);

IOT_API
TINY_LOR
Action* Action_NewInstance(uint16_t iid, const char *ns, const char *name, uint32_t uuid, const char *vendor);

IOT_API
TINY_LOR
void Action_Delete(Action *thiz);

IOT_API
TINY_LOR
TinyRet Action_InAdd(Action *thiz, uint16_t iid);

IOT_API
TINY_LOR
TinyRet Action_OutAdd(Action *thiz, uint16_t iid);

IOT_API
TINY_LOR
void Action_TryInvoke(Action *thiz, ActionOperation *o);

IOT_API
TINY_LOR
void Action_CheckResult(Action *thiz, ActionOperation *o);


TINY_END_DECLS

#endif /* __ACTION_H__ */
