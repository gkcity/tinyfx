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

#include <tiny_log.h>
#include "Format.h"

#define TAG     "Format"

#define FORMAT_STRING_UNDEFINED   "undefined"
#define FORMAT_STRING_BOOL        "bool"
#define FORMAT_STRING_STRING      "string"
#define FORMAT_STRING_FLOAT       "float"
#define FORMAT_STRING_UINT8       "uint8"
#define FORMAT_STRING_UINT16      "uint16"
#define FORMAT_STRING_UINT32      "uint32"
#define FORMAT_STRING_INT8        "int8"
#define FORMAT_STRING_INT16       "int16"
#define FORMAT_STRING_INT32       "int32"
#define FORMAT_STRING_INT64       "int64"

TINY_LOR
const char * Format_ToString(Format type)
{
    switch (type)
    {
        case FORMAT_BOOL:
            return FORMAT_STRING_BOOL;

        case FORMAT_FLOAT:
            return FORMAT_STRING_FLOAT;

        case FORMAT_STRING:
            return FORMAT_STRING_STRING;

        case FORMAT_UINT8:
            return FORMAT_STRING_UINT8;

        case FORMAT_UINT16:
            return FORMAT_STRING_UINT16;

        case FORMAT_UINT32:
            return FORMAT_STRING_UINT32;

        case FORMAT_INT8:
            return FORMAT_STRING_INT8;

        case FORMAT_INT16:
            return FORMAT_STRING_INT16;

        case FORMAT_INT32:
            return FORMAT_STRING_INT32;

        case FORMAT_INT64:
            return FORMAT_STRING_INT64;

        default:
            break;
    }

    return FORMAT_STRING_UNDEFINED;
}

TINY_LOR
Format Format_FromString(const char *value)
{
    LOG_D(TAG, "Format_FromString: %s", value);

    if (STR_EQUAL(FORMAT_STRING_BOOL, value))
    {
        return FORMAT_BOOL;
    }

    if (STR_EQUAL(FORMAT_STRING_UINT8, value))
    {
        return FORMAT_UINT8;
    }

    if (STR_EQUAL(FORMAT_STRING_UINT16, value))
    {
        return FORMAT_UINT16;
    }

    if (STR_EQUAL(FORMAT_STRING_UINT32, value))
    {
        return FORMAT_UINT32;
    }

    if (STR_EQUAL(FORMAT_STRING_INT8, value))
    {
        return FORMAT_INT8;
    }

    if (STR_EQUAL(FORMAT_STRING_INT16, value))
    {
        return FORMAT_INT16;
    }

    if (STR_EQUAL(FORMAT_STRING_INT32, value))
    {
        return FORMAT_INT32;
    }

    if (STR_EQUAL(FORMAT_STRING_FLOAT, value))
    {
        return FORMAT_FLOAT;
    }

    if (STR_EQUAL(FORMAT_STRING_INT64, value))
    {
        return FORMAT_INT64;
    }

    if (STR_EQUAL(FORMAT_STRING_STRING, value))
    {
        return FORMAT_STRING;
    }

    return FORMAT_UNDEFINED;
}

TINY_LOR
bool Format_CheckInteger(Format format, long value)
{
    long min = 0;
    long max = 0;

    switch (format)
    {
        case FORMAT_UINT8:
            min = 0;
            max = 0xFF;
            break;

        case FORMAT_UINT16:
            min = 0;
            max = 0xFFFF;
            break;

        case FORMAT_UINT32:
            min = 0;
            max = 0xFFFFFFFF;
            break;

        case FORMAT_INT8:
            min = 0 - 0x7F;
            max = 0x7F;
            break;

        case FORMAT_INT16:
            min = 0 - 0x7FFF;
            max = 0x7FFF;
            break;

        case FORMAT_INT32:
            min = 0 - 0x7FFFFFFF;
            max = 0x7FFFFFFF;
            break;

        case FORMAT_INT64:
            return true;

        default:
            return false;
    }

    return (value >= min && value <= max);
}