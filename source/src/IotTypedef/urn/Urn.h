/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Urn.h
 *
 * @remark
 *
 */

#ifndef __URN_H__
#define __URN_H__

#include <tiny_lor.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "UrnType.h"

TINY_BEGIN_DECLS

/**
 * <URN> ::= "urn:"<namespace>":"<type>":"<name>":"<value>[":"<modified>]
 *
 * urn:homekit-spec:device:light:00000001
 * urn:homekit-spec:service:switch:00000014
 * urn:homekit-spec:property:on:00000030
 *
 */

typedef struct _Urn
{
    char        * namespace;
    UrnType       type;
    char        * name;
    uint32_t      value;
    char        * vendor;
} Urn;

IOT_API
TINY_LOR
TinyRet Urn_Construct(Urn *thiz);

IOT_API
TINY_LOR
void Urn_Dispose(Urn *thiz);

IOT_API
TINY_LOR
TinyRet Urn_Set(Urn *thiz, const char *ns, UrnType type, const char *name, uint32_t value, const char *vendor);

IOT_API
TINY_LOR
TinyRet Urn_SetString(Urn *thiz, const char *string);


TINY_END_DECLS

#endif /* __URN_H__ */