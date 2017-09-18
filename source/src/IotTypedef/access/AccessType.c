/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   AccessType.c
 *
 * @remark
 *
 */

#include "AccessType.h"

TINY_LOR
AccessType AccessType_Retrieve(const char *value)
{
    if (STR_EQUAL("read", value))
    {
        return ACCESS_READ;
    }

    if (STR_EQUAL("write", value))
    {
        return ACCESS_WRITE;
    }

    if (STR_EQUAL("notify", value))
    {
        return ACCESS_NOTIFY;
    }

    return ACCESS_UNDEFINED;
}