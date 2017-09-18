/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   UrnType.c
 *
 * @remark
 *
 */

#include "UrnType.h"

TINY_LOR
UrnType UrnType_Retrieve(const char *string)
{
    if (STR_EQUAL("device", string))
    {
        return DEVICE;
    }

    if (STR_EQUAL("service", string))
    {
        return SERVICE;
    }

    if (STR_EQUAL("property", string))
    {
        return PROPERTY;
    }

    return UNDEFINED;
}