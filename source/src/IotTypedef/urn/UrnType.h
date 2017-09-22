/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   UrnType.h
 *
 * @remark
 *
 */

#ifndef __URN_TYPE_H__
#define __URN_TYPE_H__

#include "tiny_base.h"
#include "api/iot_api.h"

TINY_BEGIN_DECLS


typedef enum _UrnType
{
    UNDEFINED   = 0,
    DEVICE      = 1,
    SERVICE     = 2,
    PROPERTY    = 3,
    ACTION      = 4,
    EVENT       = 5,
} UrnType;

IOT_API
TINY_LOR
UrnType UrnType_Retrieve(const char *string);

IOT_API
TINY_LOR
const char * UrnType_ToString(UrnType type);


TINY_END_DECLS

#endif /* __URN_TYPE_H__ */
