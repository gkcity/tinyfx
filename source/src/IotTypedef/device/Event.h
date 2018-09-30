/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Event.h
 *
 * @remark
 *
 */

#ifndef __EVENT_H__
#define __EVENT_H__

#include <TinyList.h>
#include <operation/EventOperation.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"

TINY_BEGIN_DECLS


struct _Event
{
    uint16_t            iid;
    Urn                 type;
    TinyList            arguments;
    void *              service;
};

typedef struct _Event Event;

IOT_API
TINY_LOR
Event* Event_New(uint16_t iid);

IOT_API
TINY_LOR
Event* Event_NewInstance(uint16_t iid, const char *ns, const char *name, uint32_t uuid, const char *vendor);

IOT_API
TINY_LOR
void Event_Delete(Event *thiz);

IOT_API
TINY_LOR
TinyRet Event_ArgumentAdd(Event *thiz, uint16_t iid);

IOT_API
TINY_LOR
void Event_TryProduce(Event *thiz, EventOperation *o);


TINY_END_DECLS

#endif /* __EVENT_H__ */
