/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Service.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <status/IotStatus.h>
#include "Service.h"
#include "Property.h"
#include "Action.h"

#define TAG     "Service"

TINY_LOR
static TinyRet Service_Construct(Service *thiz);

TINY_LOR
static void Service_Dispose(Service *thiz);

TINY_LOR
static void property_release_handler(void *data, void *ctx)
{
    Property_Delete((Property *) data);
}

TINY_LOR
static void action_release_handler(void *data, void *ctx)
{
    Action_Delete((Action *) data);
}

TINY_LOR
Service *Service_New(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = (Service *) tiny_malloc(sizeof(Service));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Service_Construct(thiz)))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Service_Construct(Service *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Service));

        ret = Urn_Construct(&thiz->type);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Urn_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }

        /**
         * Properties
         */
        ret = TinyList_Construct(&thiz->properties);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
        thiz->properties.context = thiz;
        TinyList_SetDeleteListener(&thiz->properties, property_release_handler, thiz);

        /**
         * Actions
         */
        ret = TinyList_Construct(&thiz->actions);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
        thiz->actions.context = thiz;
        TinyList_SetDeleteListener(&thiz->actions, action_release_handler, thiz);
    } while (false);

    return ret;
}

TINY_LOR
static void Service_Dispose(Service *thiz)
{
    RETURN_IF_FAIL(thiz);

    Urn_Dispose(&thiz->type);
    TinyList_Dispose(&thiz->properties);
    TinyList_Dispose(&thiz->actions);
}

TINY_LOR
void Service_Delete(Service *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Service_Delete (iid: %d)", thiz->iid);

    Service_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
Property *Service_GetProperty(Service *thiz, uint16_t iid)
{
    RETURN_IF_FAIL(thiz);

    for (uint32_t i = 0; i < thiz->properties.size; ++i)
    {
        Property *p = (Property *) TinyList_GetAt(&thiz->properties, i);
        if (p->iid == iid)
        {
            return p;
        }
    }

    return NULL;
}

TINY_LOR
Action *Service_GetAction(Service *thiz, uint16_t iid)
{
    RETURN_IF_FAIL(thiz);

    for (uint32_t i = 0; i < thiz->actions.size; ++i)
    {
        Action *a = (Action *) TinyList_GetAt(&thiz->actions, i);
        if (a->iid == iid)
        {
            return a;
        }
    }

    return NULL;
}

TINY_LOR
void Service_TryRead(Service *thiz, PropertyOperation *o)
{
    Property *property = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    property = Service_GetProperty(thiz, o->pid.iid);
    if (property != NULL)
    {
        Property_TryRead(property, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
void Service_TryWrite(Service *thiz, PropertyOperation *o)
{
    Property *property = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    property = Service_GetProperty(thiz, o->pid.iid);
    if (property != NULL)
    {
        Property_TryWrite(property, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
void Service_TryInvoke(Service *thiz, ActionOperation *o)
{
    Action *action = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    action = Service_GetAction(thiz, o->aid.iid);
    if (action != NULL)
    {
        Action_TryInvoke(action, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}
