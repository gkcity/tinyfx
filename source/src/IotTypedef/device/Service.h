/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Service.h
 *
 * @remark
 *
 */

#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <TinyList.h>
#include <operation/PropertyOperation.h>
#include <operation/ActionOperation.h>
#include <operation/EventOperation.h>
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "Property.h"
#include "Action.h"
#include "Event.h"

TINY_BEGIN_DECLS


struct _Service
{
    uint16_t            iid;
    Urn                 type;
    TinyList            properties;
    TinyList            actions;
    TinyList            events;
};

typedef struct _Service Service;

IOT_API
TINY_LOR
Service* Service_New(uint16_t iid);

IOT_API
TINY_LOR
Service* Service_NewInstance(uint16_t iid, const char *ns, const char *name, uint32_t uuid, const char *vendor);

IOT_API
TINY_LOR
void Service_Delete(Service *thiz);

IOT_API
TINY_LOR
Property *Service_GetProperty(Service *thiz, uint16_t iid);

IOT_API
TINY_LOR
Action *Service_GetAction(Service *thiz, uint16_t iid);

IOT_API
TINY_LOR
Event *Service_GetEvent(Service *thiz, uint16_t iid);

IOT_API
TINY_LOR
bool Service_CheckValue(Service *thiz, PropertyOperation * o);

IOT_API
TINY_LOR
bool Service_CheckResult(Service *thiz, ActionOperation * o);

IOT_API
TINY_LOR
void Service_TryRead(Service *thiz, PropertyOperation * o);

IOT_API
TINY_LOR
void Service_TryWrite(Service *thiz, PropertyOperation * o);

IOT_API
TINY_LOR
void Service_TryInvoke(Service *thiz, ActionOperation * o);

IOT_API
TINY_LOR
void Service_TryChange(Service *thiz, PropertyOperation *o);

IOT_API
TINY_LOR
void Service_TryProduce(Service *thiz, EventOperation *o);


TINY_END_DECLS

#endif /* __SERVICE_H__ */
