/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceInstance.h
 *
 * @remark
 *
 */

#include <HttpClient.h>
#include <tiny_log.h>
#include <JsonArray.h>
#include <JsonNumber.h>
#include <device/Service.h>
#include <device/Property.h>
#include <JsonString.h>
#include "DeviceInstance.h"

#define TAG     "DeviceInstance"


TINY_LOR
static Property* Property_NewInstance(uint16_t diid, uint16_t siid, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;
    Property *property = NULL;

    do
    {
        JsonNumber *iid = NULL;
        JsonString *type = NULL;
        JsonString *description = NULL;
        JsonString *format = NULL;
        JsonArray *access = NULL;

        iid = JsonObject_GetNumber(object, "iid");
        if (iid == NULL)
        {
            LOG_E(TAG, "property.iid not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (iid->type != JSON_NUMBER_INTEGER)
        {
            LOG_E(TAG, "property.iid is not integer");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        type = JsonObject_GetString(object, "type");
        if (type == NULL)
        {
            LOG_E(TAG, "property.type not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        description = JsonObject_GetString(object, "description");
        if (description == NULL)
        {
            LOG_E(TAG, "property.description not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        format = JsonObject_GetString(object, "format");
        if (format == NULL)
        {
            LOG_E(TAG, "property.format not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        access = JsonObject_GetArray(object, "access");
        if (access == NULL)
        {
            LOG_E(TAG, "property.access not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (access->type != JSON_STRING)
        {
            LOG_E(TAG, "property.access is not JsonString");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        // TODO: how to process value-range & value-list ?

        property = Property_New();
        if (property == NULL)
        {
            LOG_E(TAG, "Property_New failed");
            break;
        }

        property->diid = diid;
        property->siid = siid;
        property->iid = (uint16_t) (iid->value.intValue);

        ret = Urn_SetString(&property->type, type->value);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Urn_SetString failed");
            break;
        }

//        property->data.type = DataType_?
//        property->accessType = ?;
    } while (false);

    if (RET_FAILED(ret) && property != NULL)
    {
        Property_Delete(property);
        property = NULL;
    }

    return property;
}

TINY_LOR
static Service* Service_NewInstance(uint16_t diid, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;
    Service *service = NULL;

    do
    {
        JsonNumber *iid = NULL;
        JsonString *type = NULL;
        JsonString *description = NULL;
        JsonArray *properties = NULL;

        iid = JsonObject_GetNumber(object, "iid");
        if (iid == NULL)
        {
            LOG_E(TAG, "service.iid not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (iid->type != JSON_NUMBER_INTEGER)
        {
            LOG_E(TAG, "service.iid is not integer");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        type = JsonObject_GetString(object, "type");
        if (type == NULL)
        {
            LOG_E(TAG, "service.type not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        description = JsonObject_GetString(object, "description");
        if (description == NULL)
        {
            LOG_E(TAG, "service.description not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        properties = JsonObject_GetArray(object, "properties");
        if (properties == NULL)
        {
            LOG_E(TAG, "service.properties not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (properties->type != JSON_OBJECT)
        {
            LOG_E(TAG, "service.property is not JsonObject");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        service = Service_New();
        if (service == NULL)
        {
            LOG_E(TAG, "Service_New failed");
            break;
        }

        service->diid = diid;
        service->iid = (uint16_t) (iid->value.intValue);

        ret = Urn_SetString(&service->type, type->value);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Urn_Parse failed");
            break;
        }

        for (uint32_t i = 0; i < properties->values.size; ++i)
        {
            Property *property = Property_NewInstance(diid, service->iid, (JsonObject *) TinyList_GetAt(&properties->values, i));
            if (property == NULL)
            {
                LOG_E(TAG, "Property_NewInstance failed");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            ret = TinyList_AddTail(&service->properties, property);
            if (RET_FAILED(ret))
            {
                break;
            }
        }
    } while (false);

    if (RET_FAILED(ret) && service != NULL)
    {
        Service_Delete(service);
        service = NULL;
    }

    return service;
}

TINY_LOR
static Device* Device_NewInstance(uint16_t instanceID, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;
    Device* device = NULL;

    do
    {
        JsonArray * array = JsonObject_GetArray(object, "services");
        if (array == NULL)
        {
            LOG_E(TAG, "services not found!");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (array->type != JSON_OBJECT)
        {
            LOG_E(TAG, "service is not JsonObject");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        device = Device_New();
        if (device == NULL)
        {
            LOG_E(TAG, "Device_New failed!");
            break;
        }

        device->iid = instanceID;

        for (uint32_t i = 0; i < array->values.size; ++i)
        {
            Service *service = Service_NewInstance(device->iid, (JsonObject *) TinyList_GetAt(&array->values, i));
            if (service == NULL)
            {
                LOG_E(TAG, "Service_NewInstance failed");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            ret = TinyList_AddTail(&device->services, service);
            if (RET_FAILED(ret))
            {
                break;
            }
        }
    } while (false);

    if (RET_FAILED(ret) && device != NULL)
    {
        Device_Delete(device);
        device = NULL;
    }

    return device;
}

TINY_LOR
Device* DeviceInstance_New(const char *ip, uint16_t port, const char *uri, uint32_t second)
{
    Device *device = NULL;
    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;
    JsonObject *object = NULL;

    do
    {
        client = HttpClient_New();
        if (client == NULL)
        {
            LOG_E(TAG, "HttpClient_New failed!");
            break;
        }

        exchange = HttpExchange_New(ip, port, "GET", uri, second);
        if (exchange == NULL)
        {
            LOG_E(TAG, "HttpExchange_New failed!");
            break;
        }

        if (RET_FAILED(HttpClient_Send(client, exchange)))
        {
            LOG_E(TAG, "HttpClient_Send failed!");
            break;
        }

        if (exchange->status != HTTP_STATUS_OK)
        {
            LOG_E(TAG, "exchange->status: %d", exchange->status);
            break;
        }

        object = JsonObject_NewString(exchange->content);
        if (object == NULL)
        {
            LOG_E(TAG, "JsonObject_NewString failed!");
            break;
        }

        device = Device_NewInstance(1, object);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    if (exchange != NULL)
    {
        HttpExchange_Delete(exchange);
    }

    if (client != NULL)
    {
        HttpClient_Delete(client);
    }

    return device;
}