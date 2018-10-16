/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <operation/PropertyOperation.h>
#include <status/IotStatus.h>
#include "Property.h"
#include "Device.h"
#include "Service.h"
#include "Action.h"

#define TAG     "Device"

TINY_LOR
static TinyRet Device_Construct(Device *thiz);

TINY_LOR
static void Device_Dispose(Device *thiz);

TINY_LOR
static void service_release_handler(void *data, void *ctx)
{
    Service_Delete((Service *)data);
}

TINY_LOR
Device* Device_New(void)
{
    Device *thiz = NULL;

    do
    {
        thiz = (Device *)tiny_malloc(sizeof(Device));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Device_Construct(thiz)))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Device_Construct(Device *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Device));

        ret = TinyList_Construct(&thiz->services, service_release_handler, thiz);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }
        thiz->services.context = thiz;
    } while (false);

    return ret;
}

TINY_LOR
static void Device_Dispose(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->services);
}

TINY_LOR
void Device_Delete(Device *thiz)
{
    RETURN_IF_FAIL(thiz);

    Device_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void Device_SetLtsk(Device *thiz, const char *ltsk)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(ltsk);

    strncpy(thiz->ltsk, ltsk, DEVICE_LTSK_LENGTH);
}

TINY_LOR
void Device_InitializeIID(Device *thiz, InstanceIDStyle style)
{
    if (style == IID_STYLE_HOMEKIT)
    {
        uint16_t iid = 1;

        for (uint32_t j = 0; j < thiz->services.size; ++j)
        {
            Service *s = (Service *) TinyList_GetAt(&thiz->services, j);
            s->iid = iid++;

            for (uint32_t k = 0; k < s->properties.size; ++k)
            {
                Property *p = (Property * )TinyList_GetAt(&s->properties, k);
                p->iid = iid++;
            }
        }
    }
    else
    {
        uint16_t siid = 1;

        for (uint32_t j = 0; j < thiz->services.size; ++j)
        {
            uint16_t piid = 1;
            Service *s = (Service *) TinyList_GetAt(&thiz->services, j);
            s->iid = siid++;

            for (uint32_t k = 0; k < s->properties.size; ++k)
            {
                Property *p = (Property * )TinyList_GetAt(&s->properties, k);
                p->iid = piid++;
            }
        }
    }
}

TINY_LOR
void Device_SetHandler(Device *thiz, PropertyOnGet onGet, PropertyOnSet onSet, ActionOnInvoke onInvoke)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Device_SetHandler");

    thiz->onSet = onSet;
    thiz->onGet = onGet;
    thiz->onInvoke = onInvoke;

//    for (uint32_t i = 0; i < thiz->services.size; ++i)
//    {
//        Service *s = (Service *) TinyList_GetAt(&thiz->services, i);
//
//        for (uint32_t j = 0; j < s->properties.size; ++j)
//        {
//            Property *p = (Property * )TinyList_GetAt(&s->properties, j);
//            p->onSet = onSet;
//            p->onGet = onGet;
//        }
//
//        for (uint32_t j = 0; j < s->actions.size; ++j)
//        {
//            Action *a = (Action * )TinyList_GetAt(&s->actions, j);
//            a->onInvoke = onInvoke;
//        }
//    }
}

TINY_LOR
bool Device_CheckHandler(Device *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "Device_CheckHandler");

    if (thiz->onSet == NULL)
    {
        LOG_E(TAG, "Property on set not handle");
        return false;
    }

    if (thiz->onGet == NULL)
    {
        LOG_E(TAG, "Property on get not handle");
        return false;
    }

    if (thiz->onInvoke == NULL)
    {
        LOG_E(TAG, "Action on invoke not handle");
        return false;
    }

//    for (uint32_t i = 0; i < thiz->services.size; ++i)
//    {
//        Service *s = (Service *) TinyList_GetAt(&thiz->services, i);
//
//        for (uint32_t j = 0; j < s->properties.size; ++j)
//        {
//            Property *p = (Property * )TinyList_GetAt(&s->properties, j);
//            if (Access_IsReadable(p->access) && (p->onGet == NULL))
//            {
//                LOG_E(TAG, "Property.onGet not handle: %s", p->type.name);
//                return false;
//            }
//
//            if (Access_IsWritable(p->access) && p->onSet == NULL)
//            {
//                LOG_E(TAG, "Property.onSet not handle: %s", p->type.name);
//                return false;
//            }
//        }
//
//        for (uint32_t j = 0; j < s->actions.size; ++j)
//        {
//            Action *a = (Action * )TinyList_GetAt(&s->actions, j);
//            if (a->onInvoke == NULL)
//            {
//                LOG_E(TAG, "Action.onInvoke not handle: %s", a->type.name);
//                return false;
//            }
//        }
//    }

    return true;
}

TINY_LOR
static Device * Device_GetChild(Device *thiz, const char * did)
{
    for (uint32_t i = 0; i < thiz->children.size; ++i)
    {
        Device * child = (Device *)TinyList_GetAt(&thiz->children, i);
        if (STR_EQUAL(child->did, did))
        {
            return child;
        }
    }

    return NULL;
}

TINY_LOR
static Service * Device_GetService(Device *thiz, uint16_t siid)
{
    for (uint32_t i = 0; i < thiz->services.size; ++i)
    {
        Service *s = (Service *) TinyList_GetAt(&thiz->services, i);
        if (s->iid == siid)
        {
            return s;
        }
    }

    return NULL;
}

TINY_LOR
static void Device_TryRead(Device *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryRead(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onGet != NULL)
            {
                thiz->onGet(o);
                Service_CheckValue(service, o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryReadChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TryRead(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryWrite(Device *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryWrite(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onSet != NULL)
            {
                thiz->onSet(o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryWriteChild(Device *thiz, PropertyOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Device_TryWrite(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryInvoke(Device *thiz, ActionOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Device_GetService(thiz, o->aid.siid);
    if (service != NULL)
    {
        Service_TryInvoke(service, o);
        if (o->status == IOT_STATUS_OK)
        {
            if (thiz->onInvoke != NULL)
            {
                thiz->onInvoke(o);
                Service_CheckResult(service, o);
            }
            else
            {
                o->status = IOT_STATUS_INTERNAL_ERROR;
            }
        }
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Device_TryInvokeChild(Device *thiz, ActionOperation *o)
{
    Device *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Device_GetChild(thiz, o->aid.did);
    if (child != NULL)
    {
        Device_TryInvoke(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
void Device_TryReadProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->did, o->pid.did))
        {
            Device_TryRead(thiz, o);
        }
        else
        {
            Device_TryReadChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TryWriteProperties(Device *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->did, o->pid.did))
        {
            Device_TryWrite(thiz, o);
        }
        else
        {
            Device_TryWriteChild(thiz, o);
        }
    }
}

TINY_LOR
void Device_TryInvokeAction(Device *thiz, ActionOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    if (STR_EQUAL(thiz->did, o->aid.did))
    {
        Device_TryInvoke(thiz, o);
    }
    else
    {
        Device_TryInvokeChild(thiz, o);
    }
}

TINY_LOR
TinyRet Device_TryChangePropertyValue(Device *thiz, PropertyOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Device_GetService(thiz, o->pid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryChange(service, o);

        if (o->status != IOT_STATUS_OK)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (thiz->onChanged == NULL)
        {
            ret = TINY_RET_E_NOT_IMPLEMENTED;
            break;
        }

        thiz->onChanged(o);
    } while (false);

    return ret;
}

TINY_LOR
TinyRet Device_TryProduceEvent(Device *thiz, EventOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Device_GetService(thiz, o->eid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryProduce(service, o);

        if (o->status != IOT_STATUS_OK)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (thiz->onEventOccurred == NULL)
        {
            ret = TINY_RET_E_NOT_IMPLEMENTED;
            break;
        }

        thiz->onEventOccurred(o);
    } while (false);

    return ret;
}

//TINY_LOR
//TinyRet Device_GetAccessKey(Device *thiz, OnGetAccessKeySucceed onSucceed, OnGetAccessKeyFailed onFailed)
//{
//    return TINY_RET_E_NOT_IMPLEMENTED;
//}
//
//TINY_LOR
//TinyRet Device_ResetAccessKey(Device *thiz, OnResetAccessKeySucceed onSucceed, OnResetAccessKeyFailed onFailed)
//{
//    return TINY_RET_E_NOT_IMPLEMENTED;
//}