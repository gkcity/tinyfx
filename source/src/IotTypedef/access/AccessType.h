/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   AccessType.h
 *
 * @remark
 *
 */

#ifndef __ACCESS_TYPE_H__
#define __ACCESS_TYPE_H__

#include <api/iot_api.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _AccessType
{
    ACCESS_UNDEFINED    = 0,
    ACCESS_READ         = 0x01,
    ACCESS_WRITE        = 0x02,
    ACCESS_NOTIFY       = 0x04,
} AccessType;

IOT_API
TINY_LOR
AccessType AccessType_Retrieve(const char *value);


TINY_END_DECLS

#endif /* __ACCESS_TYPE_H__ */
