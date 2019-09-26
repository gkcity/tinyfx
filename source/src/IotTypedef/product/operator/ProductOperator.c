/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ProductOperator.c
 *
 * @remark
 *
 */

#include <device/Service.h>
#include <status/IotStatus.h>
#include <tiny_log.h>
#include "ProductOperator.h"

#define TAG "ProductOperator"

TINY_LOR
static Product * Product_GetChild(Product *thiz, const char * did)
{
    for (uint32_t i = 0; i < thiz->children.size; ++i)
    {
        Product * child = (Product *)TinyList_GetAt(&thiz->children, i);
        if (STR_EQUAL(child->config.did, did))
        {
            return child;
        }
    }

    return NULL;
}

TINY_LOR
static Service * Product_GetService(Product *thiz, uint16_t siid)
{
    for (uint32_t i = 0; i < thiz->device.services.size; ++i)
    {
        Service *s = (Service *) TinyList_GetAt(&thiz->device.services, i);
        if (s->iid == siid)
        {
            return s;
        }
    }

    return NULL;
}

TINY_LOR
static void Product_TryRead(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Product_GetService(thiz, o->pid.siid);
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
static void Product_TryReadChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Product_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Product_TryRead(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Product_TryWrite(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Product_GetService(thiz, o->pid.siid);
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

#if 0
TINY_LOR
static void Product_TrySubscribe(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Product_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TrySubscribe(service, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Product_TryUnsubscribe(Product *thiz, PropertyOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Product_GetService(thiz, o->pid.siid);
    if (service != NULL)
    {
        Service_TryUnsubscribe(service, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}
#endif

TINY_LOR
static void Product_TryWriteChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Product_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Product_TryWrite(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

#if 0
TINY_LOR
static void Product_TrySubscribeChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Product_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Product_TrySubscribe(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
static void Product_TryUnsubscribeChild(Product *thiz, PropertyOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Product_GetChild(thiz, o->pid.did);
    if (child != NULL)
    {
        Product_TryUnsubscribe(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}
#endif

TINY_LOR
static void Product_TryInvoke(Product *thiz, ActionOperation *o)
{
    Service * service = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    service = Product_GetService(thiz, o->aid.siid);
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
static void Product_TryInvokeChild(Product *thiz, ActionOperation *o)
{
    Product *child = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    child = Product_GetChild(thiz, o->aid.did);
    if (child != NULL)
    {
        Product_TryInvoke(child, o);
    }
    else
    {
        o->status = IOT_STATUS_NOT_EXIST;
    }
}

TINY_LOR
void Product_TryReadProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Product_TryRead(thiz, o);
        }
        else
        {
            Product_TryReadChild(thiz, o);
        }
    }
}

TINY_LOR
void Product_TryWriteProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Product_TryWrite(thiz, o);
        }
        else
        {
            Product_TryWriteChild(thiz, o);
        }
    }
}

#if 0
TINY_LOR
void Product_TrySubscribeProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Product_TrySubscribe(thiz, o);
        }
        else
        {
            Product_TrySubscribeChild(thiz, o);
        }
    }
}

TINY_LOR
void Product_TryUnsubscribeProperties(Product *thiz, PropertyOperations *operations)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(operations);

    for (uint32_t i = 0; i < operations->properties.size; ++i)
    {
        PropertyOperation *o = (PropertyOperation *)TinyList_GetAt(&operations->properties, i);
        if (STR_EQUAL(thiz->config.did, o->pid.did))
        {
            Product_TryUnsubscribe(thiz, o);
        }
        else
        {
            Product_TryUnsubscribeChild(thiz, o);
        }
    }
}
#endif

TINY_LOR
void Product_TryInvokeAction(Product *thiz, ActionOperation *o)
{
    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(o);

    if (STR_EQUAL(thiz->config.did, o->aid.did))
    {
        Product_TryInvoke(thiz, o);
    }
    else
    {
        Product_TryInvokeChild(thiz, o);
    }
}

TINY_LOR
TinyRet Product_TryChangePropertyValue(Product *thiz, PropertyOperation *o, bool save)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Product_GetService(thiz, o->pid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryChange(service, o, save);
    } while (false);

    return ret;
}

TINY_LOR
TinyRet Product_TryProduceEvent(Product *thiz, EventOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    do
    {
        Service * service = Product_GetService(thiz, o->eid.siid);
        if (service == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        Service_TryProduce(service, o);
    } while (false);

    return ret;
}

TINY_LOR
TinyRet Product_DoChangePropertyValue(Product *thiz, PropertyOperation *o)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(o, TINY_RET_E_ARG_NULL);

    Product_Lock(thiz);

    ret = Product_TryChangePropertyValue(thiz, o, true);

    Product_Unlock(thiz);

    return ret;
}

IOT_API
TINY_LOR
PropertyOperations * Product_GetChangedProperties(Product *thiz)
{
    PropertyOperations *changed = NULL;

    RETURN_VAL_IF_FAIL(thiz, NULL);

    changed = PropertyOperations_New();
    if (changed != NULL)
    {
        Product_Lock(thiz);

        for (uint32_t i = 0; i < thiz->device.services.size; ++i)
        {
            Service *s = (Service *) TinyList_GetAt(&thiz->device.services, i);
            for (uint32_t j = 0; j < s->properties.size; ++j)
            {
                Property *p = (Property *) TinyList_GetAt(&s->properties, j);
                if (p->value != NULL)
                {
                    PropertyOperation *o = PropertyOperation_New();
                    if (o == NULL)
                    {
                        LOG_E(TAG, "PropertyOperation_New failed!");
                        break;
                    }

                    strncpy(o->pid.did, thiz->config.did, IOT_DEVICE_ID_LENGTH);
                    o->pid.siid = s->iid;
                    o->pid.iid = p->iid;

                    o->value = JsonValue_NewFrom(p->value);
                    if (o->value == NULL)
                    {
                        LOG_E(TAG, "JsonValue_NewFrom failed!");
                        PropertyOperation_Delete(o);
                        break;
                    }

                    if (RET_FAILED(TinyList_AddTail(&changed->properties, o)))
                    {
                        LOG_E(TAG, "TinyList_AddTail failed!");
                        PropertyOperation_Delete(o);
                        break;
                    }
                }
            }
        }

        Product_Unlock(thiz);
    }

    return changed;
}