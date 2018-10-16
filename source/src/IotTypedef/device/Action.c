/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Action.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <status/IotStatus.h>
#include <value/JsonString.h>
#include "Action.h"
#include "Property.h"
#include "Argument.h"
#include "Service.h"

#define TAG     "Action"

TINY_LOR
static TinyRet Action_Construct(Action *thiz, uint16_t iid);

TINY_LOR
static void Action_Dispose(Action *thiz);

TINY_LOR
static void in_release_handler(void *data, void *ctx)
{
    Argument_Delete(data);
}

TINY_LOR
static void out_release_handler(void *data, void *ctx)
{
    Argument_Delete(data);
}

TINY_LOR
Action* Action_New(uint16_t iid)
{
    Action *thiz = NULL;

    do
    {
        thiz = (Action *)tiny_malloc(sizeof(Action));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Action_Construct(thiz, iid)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
Action* Action_NewInstance(uint16_t iid, const char *ns, const char *name, uint32_t uuid, const char *vendor)
{
    Action * thiz = NULL;

    do
    {
        thiz = Action_New(iid);
        if (thiz == NULL)
        {
            LOG_D(TAG, "Action_New FAILED");
            break;
        }

        if (RET_FAILED(Urn_Set(&thiz->type, ns, PROPERTY, name, uuid, vendor)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Action_Construct(Action *thiz, uint16_t iid)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Action));
        thiz->iid = iid;

        ret = Urn_Construct(&thiz->type);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Urn_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        ret = TinyList_Construct(&thiz->in, in_release_handler, thiz);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->in.context = thiz;

        ret = TinyList_Construct(&thiz->out, out_release_handler, thiz);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->out.context = thiz;
    } while (false);

    return ret;
}

TINY_LOR
static void Action_Dispose(Action *thiz)
{
    RETURN_IF_FAIL(thiz);

    Urn_Dispose(&thiz->type);
    TinyList_Dispose(&thiz->in);
    TinyList_Dispose(&thiz->out);
}

TINY_LOR
void Action_Delete(Action *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Action_Delete (iid: %d)", thiz->iid);

    Action_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet Action_InAdd(Action *thiz, uint16_t iid)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        Argument * argument = Argument_NewValue(iid);
        if (argument == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = TinyList_AddTail(&thiz->in, argument);
        if (RET_FAILED(ret))
        {
            Argument_Delete(argument);
            break;
        }
    } while(false);

    return ret;
}

TINY_LOR
TinyRet Action_OutAdd(Action *thiz, uint16_t iid)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        Argument * argument = Argument_NewValue(iid);
        if (argument == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = TinyList_AddTail(&thiz->out, argument);
        if (RET_FAILED(ret))
        {
            Argument_Delete(argument);
            break;
        }
    } while(false);

    return ret;
}

TINY_LOR
static Property* Action_GetProperty(Action *thiz, TinyList *arguments, int index)
{
    Argument * argument = NULL;

    RETURN_VAL_IF_FAIL(thiz, NULL);
    RETURN_VAL_IF_FAIL(arguments, NULL);

    argument = (Argument *) TinyList_GetAt(arguments, index);
    if (argument == NULL)
    {
        LOG_E(TAG, "argument not found: %d", index);
        return NULL;
    }

    return Service_GetProperty(thiz->service, argument->iid);
}

TINY_LOR
void Action_TryInvoke(Action *thiz, ActionOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    do
    {
        if (thiz->in.size != o->in.values.size)
        {
            LOG_E(TAG, "action in size invalid: %d, expected: %d", o->in.values.size, thiz->in.size);
            o->status = IOT_STATUS_ACTION_IN_ERROR;
            break;
        }

        for (uint32_t i = 0; i < thiz->in.size; ++i)
        {
            JsonValue * value = (JsonValue *)TinyList_GetAt(&o->in.values, i);
            Property *property = Action_GetProperty(thiz, &thiz->in, i);
            if (property == NULL)
            {
                LOG_E(TAG, "property not found");
                o->status = IOT_STATUS_INTERNAL_ERROR;
                break;
            }

            if (! Property_CheckValue(property, value))
            {
                LOG_E(TAG, "property value invalid, value type: %d", value->type);
                o->status = IOT_STATUS_VALUE_ERROR;
                break;
            }
        }
    } while (false);
}

TINY_LOR
void Action_CheckResult(Action *thiz, ActionOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    do
    {
        if (thiz->out.size != o->out.values.size)
        {
            o->status = IOT_STATUS_ACTION_OUT_ERROR;
            break;
        }

        if (thiz->out.size == 0)
        {
            break;
        }

        for (uint32_t i = 0; i < thiz->out.size; ++i)
        {
            JsonValue * value = (JsonValue *)TinyList_GetAt(&o->out.values, i);
            Property *property = Action_GetProperty(thiz, &thiz->out, i);
            if (property == NULL)
            {
                LOG_E(TAG, "property not found");
                o->status = IOT_STATUS_INTERNAL_ERROR;
                break;
            }

            if (! Property_CheckValue(property, value))
            {
                LOG_E(TAG, "property value invalid");
                o->status = IOT_STATUS_VALUE_ERROR;
                break;
            }
        }
    } while (false);
}