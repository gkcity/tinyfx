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

#define STRING_UNDEFINED    "undefined"
#define STRING_DEVICE       "device"
#define STRING_SERVICE      "service"
#define STRING_ACTION       "action"
#define STRING_EVENT        "event"
#define STRING_PROPERTY     "property"

TINY_LOR
UrnType UrnType_Retrieve(const char *string)
{
    if (STR_EQUAL(STRING_DEVICE, string))
    {
        return DEVICE;
    }

    if (STR_EQUAL(STRING_SERVICE, string))
    {
        return SERVICE;
    }

    if (STR_EQUAL(STRING_ACTION, string))
    {
        return ACTION;
    }

    if (STR_EQUAL(STRING_EVENT, string))
    {
        return EVENT;
    }

    if (STR_EQUAL(STRING_PROPERTY, string))
    {
        return PROPERTY;
    }

    return UNDEFINED;
}

TINY_LOR
const char * UrnType_ToString(UrnType type)
{
    const char *p = NULL;

    switch (type)
    {
        case DEVICE:
            p = STRING_DEVICE;
            break;

        case SERVICE:
            p = STRING_SERVICE;
            break;

        case PROPERTY:
            p = STRING_PROPERTY;
            break;

        case ACTION:
            p = STRING_ACTION;
            break;

        case EVENT:
            p = STRING_EVENT;
            break;

        case UNDEFINED:
            p = STRING_UNDEFINED;
            break;
    }

    return p;
}