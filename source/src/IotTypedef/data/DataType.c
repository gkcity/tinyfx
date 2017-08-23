/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DataType.c
 *
 * @remark
 *
 */

#include "DataType.h"

#define FORMAT_NAME_BOOL        "bool"
#define FORMAT_NAME_UINT8       "uint8"
#define FORMAT_NAME_UINT16      "uint16"
#define FORMAT_NAME_UINT32      "uint32"
#define FORMAT_NAME_UINT64      "uint64"
#define FORMAT_NAME_INT         "int"
#define FORMAT_NAME_FLOAT       "float"
#define FORMAT_NAME_STRING      "string"
#define FORMAT_NAME_TLV8        "tlv8"

TINY_LOR
const char *DataType_GetName(DataType type)
{
    switch (type)
    {
        case DATATYPE_BOOL:
            return FORMAT_NAME_BOOL;

        case DATATYPE_UINT8:
            return FORMAT_NAME_UINT8;

        case DATATYPE_UINT16:
            return FORMAT_NAME_UINT16;

        case DATATYPE_UINT32:
            return FORMAT_NAME_UINT32;

        case DATATYPE_UINT64:
            return FORMAT_NAME_UINT64;

        case DATATYPE_INT:
            return FORMAT_NAME_INT;

        case DATATYPE_FLOAT:
            return FORMAT_NAME_FLOAT;

        case DATATYPE_STRING:
            return FORMAT_NAME_STRING;

            /* Base64-encoded set of one or more TLV8's */
        case DATATYPE_TLV8:
            return FORMAT_NAME_TLV8;

        default:
            break;
    }

    return NULL;
}