/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ActionInvoker.c
 *
 * @remark
 *
 */

#include <device/Property.h>
#include <JsonObject.h>
#include <JsonNumber.h>
#include "ActionInvoker.h"
#include "PropertySetter.h"

TINY_LOR
bool ActionInvoker_Set(Action *action, JsonArray *in)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(action, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(in, TINY_RET_E_ARG_NULL);

    do
    {
        if (action->in.size != in->values.size)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (action->in.size == 0)
        {
            break;
        }

        if (in->type != JSON_OBJECT)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        for (uint32_t i = 0; i < in->values.size; ++i)
        {
            Property *property = (Property *) TinyList_GetAt(&action->in, i);
            JsonObject *p = (JsonObject *) TinyList_GetAt(&in->values, i);
            JsonNumber *iid = JsonObject_GetNumber(p, "iid");
            JsonValue *value = JsonObject_GetValue(p, "value");

            if (iid == NULL || value == NULL)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (property->iid != iid->value.intValue)
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (! PropertySetter_Set(property, value))
            {
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }
        }
    } while (false);

    return (ret == TINY_RET_OK);
}