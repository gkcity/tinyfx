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

#include <value/JsonString.h>
#include "Access.h"

TINY_LOR
Access Access_FromJsonArray(JsonArray *array)
{
    Access access = 0;

    RETURN_VAL_IF_FAIL(array, ACCESS_UNDEFINED);

    for (int i = 0; i < array->values.size; ++i)
    {
        JsonValue *v = TinyList_GetAt(&array->values, i);
        if (v->type != JSON_STRING)
        {
            break;
        }

        if (STR_EQUAL("read", v->data.string->value))
        {
            access |= ACCESS_READ;
        }

        else if (STR_EQUAL("write", v->data.string->value))
        {
            access |= ACCESS_WRITE;
        }

        else if (STR_EQUAL("notify", v->data.string->value))
        {
            access |= ACCESS_NOTIFY;
        }
    }

    return access;
}

TINY_LOR
bool Property_IsReadable(Access access)
{
    return ((access & ACCESS_READ) != 0);
}

TINY_LOR
bool Property_IsWritable(Access access)
{
    return ((access & ACCESS_WRITE) != 0);
}

TINY_LOR
bool Property_IsNotifiable(Access access)
{
    return ((access & ACCESS_NOTIFY) != 0);
}