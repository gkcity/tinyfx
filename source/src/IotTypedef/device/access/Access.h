/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Access.h
 *
 * @remark
 *
 */

#ifndef __ACCESS_H__
#define __ACCESS_H__

#include <api/iot_api.h>
#include <JsonArray.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


#define ACCESS_READ         0x01
#define ACCESS_WRITE        0x02
#define ACCESS_NOTIFY       0x04

typedef uint8_t Access;

IOT_API
TINY_LOR
Access Access_FromJsonArray(JsonArray *array);

IOT_API
TINY_LOR
bool Access_IsReadable(Access access);

IOT_API
TINY_LOR
bool Access_IsWritable(Access access);

IOT_API
TINY_LOR
bool Access_IsNotifiable(Access access);


TINY_END_DECLS

#endif /* __ACCESS_H__ */
