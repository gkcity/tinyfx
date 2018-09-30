/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Event.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <status/IotStatus.h>
#include <value/JsonString.h>
#include "Event.h"
#include "Property.h"
#include "Argument.h"
#include "Service.h"

#define TAG     "Event"

TINY_LOR
static TinyRet Event_Construct(Event *thiz, uint16_t iid);

TINY_LOR
static void Event_Dispose(Event *thiz);

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
Event* Event_New(uint16_t iid)
{
    Event *thiz = NULL;

    do
    {
        thiz = (Event *)tiny_malloc(sizeof(Event));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Event_Construct(thiz, iid)))
        {
            Event_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
Event* Event_NewInstance(uint16_t iid, const char *ns, const char *name, uint32_t uuid, const char *vendor)
{
    Event * thiz = NULL;

    do
    {
        thiz = Event_New(iid);
        if (thiz == NULL)
        {
            LOG_D(TAG, "Event_New FAILED");
            break;
        }

        if (RET_FAILED(Urn_Set(&thiz->type, ns, EVENT, name, uuid, vendor)))
        {
            Event_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Event_Construct(Event *thiz, uint16_t iid)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Event));
        thiz->iid = iid;

        ret = Urn_Construct(&thiz->type);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Urn_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        ret = TinyList_Construct(&thiz->arguments);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->arguments.context = thiz;
        TinyList_SetDeleteListener(&thiz->arguments, in_release_handler, thiz);
    } while (false);

    return ret;
}

TINY_LOR
static void Event_Dispose(Event *thiz)
{
    RETURN_IF_FAIL(thiz);

    Urn_Dispose(&thiz->type);
    TinyList_Dispose(&thiz->arguments);
}

TINY_LOR
void Event_Delete(Event *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Event_Delete (iid: %d)", thiz->iid);

    Event_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet Event_ArgumentAdd(Event *thiz, uint16_t iid)
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

        ret = TinyList_AddTail(&thiz->arguments, argument);
        if (RET_FAILED(ret))
        {
            Argument_Delete(argument);
            break;
        }
    } while(false);

    return ret;
}

TINY_LOR
static Property* Event_GetProperty(Event *thiz, TinyList *arguments, int index)
{
    Argument * argument = NULL;

    RETURN_VAL_IF_FAIL(thiz, NULL);
    RETURN_VAL_IF_FAIL(arguments, NULL);

    argument = (Argument *) TinyList_GetAt(arguments, index);
    if (argument == NULL)
    {
        return NULL;
    }

    return Service_GetProperty(thiz->service, argument->iid);
}

TINY_LOR
void Event_TryProduce(Event *thiz, EventOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    do
    {
        if (thiz->arguments.size != o->arguments->values.size)
        {
            o->status = IOT_STATUS_ACTION_IN_ERROR;
            break;
        }

        for (uint32_t i = 0; i < thiz->arguments.size; ++i)
        {
            JsonValue * value = (JsonValue *)TinyList_GetAt(&o->arguments->values, i);
            Property *property = Event_GetProperty(thiz, &thiz->arguments, i);
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