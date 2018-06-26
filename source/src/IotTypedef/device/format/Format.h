/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Format.h
 *
 * @remark
 *
 */

#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <tiny_lor.h>
#include <tiny_base.h>
#include "api/iot_api.h"

TINY_BEGIN_DECLS


typedef enum _Format
{
    FORMAT_UNDEFINED  = 0,
    FORMAT_BOOL       = 1,
    FORMAT_STRING     = 2,
    FORMAT_FLOAT      = 3,
    FORMAT_UINT8      = 4,
    FORMAT_UINT16     = 5,
    FORMAT_UINT32     = 6,
    FORMAT_INT8       = 7,
    FORMAT_INT16      = 8,
    FORMAT_INT32      = 9,
    FORMAT_INT64      = 10,
} Format;

IOT_API
TINY_LOR
const char * Format_ToString(Format type);

IOT_API
TINY_LOR
Format Format_FromString(const char *value);

IOT_API
TINY_LOR
bool Format_CheckInteger(Format format, long value);


TINY_END_DECLS

#endif /* __FORMAT_H__ */