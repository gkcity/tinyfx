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
    ActionOnInvoke      onInvoke;
    void *              service;
};

typedef struct _Action Action;

IOT_API
TINY_LOR
Action* Action_New(void);

IOT_API
TINY_LOR
void Action_Delete(Action *thiz);

IOT_API
TINY_LOR
void Action_TryInvoke(Action *thiz, ActionOperation *o);

        
TINY_END_DECLS

#endif /* __ACTION_H__ */
