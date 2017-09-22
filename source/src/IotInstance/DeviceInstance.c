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
#include <JsonString.h>
#include <JsonObject.h>
#include <device/Service.h>
#include <device/Property.h>
#include <device/Action.h>
#include "DeviceInstance.h"

#define TAG     "DeviceInstance"

TINY_LOR
static uint16_t AccessType_New(JsonArray *array)
{
    uint16_t a = 0;

    for (uint32_t i = 0; i < array->values.size; ++i)
    {
        JsonValue *value = (JsonValue *) TinyList_GetAt(&array->values, i);
        AccessType type = AccessType_Retrieve(value->data.string->value);
        if (type == ACCESS_UNDEFINED)
        {
            LOG_E(TAG, "AccessType INVALID: %s", value->data.string->value);
            break;
        }

        a |= type;
    }

    return a;
}

TINY_LOR
static TinyRet Property_ProcessValueRange(Property *property, JsonArray *range)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        JsonValue *min = NULL;
        JsonValue *max = NULL;
        JsonValue *step = NULL;

        if (range->type != JSON_NUMBER)
        {
            LOG_E(TAG, "range.type not JsonNumber: %d", range->type);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (range->values.size != 3)
        {
            LOG_E(TAG, "range values.size not 3");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        min = (JsonValue *)TinyList_GetAt(&range->values, 0);
        max = (JsonValue *)TinyList_GetAt(&range->values, 1);
        step = (JsonValue *)TinyList_GetAt(&range->values, 2);

        switch (property->data.type)
        {
            case DATATYPE_UINT8:
                if (min->data.number->type == JSON_NUMBER_INTEGER
                    && max->data.number->type == JSON_NUMBER_INTEGER
                    && step->data.number->type == JSON_NUMBER_INTEGER)
                {

                    Data_SetUint8ValueRange(&property->data,
                                            (uint8_t)min->data.number->value.intValue,
                                            (uint8_t)max->data.number->value.intValue,
                                            (uint8_t)step->data.number->value.intValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            case DATATYPE_UINT16:
                if (min->data.number->type == JSON_NUMBER_INTEGER
                    && max->data.number->type == JSON_NUMBER_INTEGER
                    && step->data.number->type == JSON_NUMBER_INTEGER)
                {

                    Data_SetUint16ValueRange(&property->data,
                                             (uint16_t)min->data.number->value.intValue,
                                             (uint16_t)max->data.number->value.intValue,
                                             (uint16_t)step->data.number->value.intValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            case DATATYPE_UINT32:
                if (min->data.number->type == JSON_NUMBER_INTEGER
                    && max->data.number->type == JSON_NUMBER_INTEGER
                    && step->data.number->type == JSON_NUMBER_INTEGER)
                {

                    Data_SetUint32ValueRange(&property->data,
                                             (uint32_t)min->data.number->value.intValue,
                                             (uint32_t)max->data.number->value.intValue,
                                             (uint32_t)step->data.number->value.intValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            case DATATYPE_UINT64:
                if (min->data.number->type == JSON_NUMBER_INTEGER
                    && max->data.number->type == JSON_NUMBER_INTEGER
                    && step->data.number->type == JSON_NUMBER_INTEGER)
                {

                    Data_SetUint64ValueRange(&property->data,
                                             (uint64_t)min->data.number->value.intValue,
                                             (uint64_t)max->data.number->value.intValue,
                                             (uint64_t)step->data.number->value.intValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            case DATATYPE_INT:
                if (min->data.number->type == JSON_NUMBER_INTEGER
                    && max->data.number->type == JSON_NUMBER_INTEGER
                    && step->data.number->type == JSON_NUMBER_INTEGER)
                {

                    Data_SetIntValueRange(&property->data,
                                          min->data.number->value.intValue,
                                          max->data.number->value.intValue,
                                          step->data.number->value.intValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            case DATATYPE_FLOAT:
                if (min->data.number->type == JSON_NUMBER_FLOAT
                    && max->data.number->type == JSON_NUMBER_FLOAT
                    && step->data.number->type == JSON_NUMBER_FLOAT)
                {
                    Data_SetFloatValueRange(&property->data,
                                            min->data.number->value.floatValue,
                                            max->data.number->value.floatValue,
                                            step->data.number->value.floatValue);
                }
                else
                {
                    ret = TINY_RET_E_ARG_INVALID;
                }
                break;

            default:
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static TinyRet Property_ProcessValueList(Property *property, JsonArray *list)
{
    TinyRet ret = TINY_RET_OK;

    // TODO: ...

    return ret;
}

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
        JsonArray *valueRange = NULL;
        JsonArray *valueList = NULL;

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
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (property->type.type != PROPERTY)
        {
            LOG_E(TAG, "property.type invalid");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        property->data.type = DataType_Retrieve(format->value);
        if (property->data.type == DATATYPE_UNDEFINED)
        {
            LOG_E(TAG, "DataType_Retrieve failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (access->values.size == 0)
        {
            property->accessType = 0;
        }
        else
        {
            if (access->type != JSON_STRING)
            {
                LOG_E(TAG, "%d %s access.type is not JsonString: %d", iid->value.intValue, type->value, access->type);
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            property->accessType = AccessType_New(access);
        }

        valueRange = JsonObject_GetArray(object, "value-range");
        valueList = JsonObject_GetArray(object, "value-list");
        if (valueRange != NULL && valueList != NULL)
        {
            LOG_E(TAG, "value-range & value-list exist at the same time");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (valueRange != NULL)
        {
            ret = Property_ProcessValueRange(property, valueRange);
        }

        if (valueList != NULL)
        {
            ret = Property_ProcessValueList(property, valueList);
        }
    } while (false);

    if (RET_FAILED(ret) && property != NULL)
    {
        Property_Delete(property);
        property = NULL;
    }

    return property;
}

TINY_LOR
static Property * getProperty(TinyList *properties, uint16_t iid)
{
    for (uint32_t i = 0; i < properties->size; ++i)
    {
        Property * p = (Property *) TinyList_GetAt(properties, i);
        if (p->iid == iid)
        {
            return p;
        }
    }

    return NULL;
}

TINY_LOR
static TinyRet ParseArguments(TinyList *list, JsonArray *arguments, TinyList *properties)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(list, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(properties, TINY_RET_E_ARG_NULL);

    do
    {
        if (arguments == NULL)
        {
            break;
        }

        if (arguments->values.size == 0)
        {
            break;
        }

        if (arguments->type != JSON_NUMBER)
        {
            LOG_E(TAG, "in.type is not JSON_NUMBER");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        for (uint32_t i = 0; i < arguments->values.size; ++i)
        {
            JsonNumber *v = ((JsonValue *) TinyList_GetAt(&arguments->values, i))->data.number;
            Property * p = getProperty(properties, (uint16_t)v->value.intValue);
            if (p == NULL)
            {
                LOG_E(TAG, "action.in [%d] invalid", v->value.intValue);
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            TinyList_AddTail(list, p);
        }
    } while (false);

    return ret;
}

TINY_LOR
static Action* Action_NewInstance(uint16_t diid, uint16_t siid, JsonObject *object, TinyList *properties)
{
    TinyRet ret = TINY_RET_OK;
    Action *action = NULL;

    do
    {
        JsonNumber *iid = NULL;
        JsonString *type = NULL;
        JsonString *description = NULL;

        iid = JsonObject_GetNumber(object, "iid");
        if (iid == NULL)
        {
            LOG_E(TAG, "action.iid not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (iid->type != JSON_NUMBER_INTEGER)
        {
            LOG_E(TAG, "action.iid is not integer");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        type = JsonObject_GetString(object, "type");
        if (type == NULL)
        {
            LOG_E(TAG, "action.type not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        description = JsonObject_GetString(object, "description");
        if (description == NULL)
        {
            LOG_E(TAG, "action.description not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        action = Action_New();
        if (action == NULL)
        {
            LOG_E(TAG, "Property_New failed");
            break;
        }

        action->diid = diid;
        action->siid = siid;
        action->iid = (uint16_t) (iid->value.intValue);
        ret = Urn_SetString(&action->type, type->value);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "Urn_SetString failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        /**
         * in is optional
         */
        ret = ParseArguments(&action->in, JsonObject_GetArray(object, "in"), properties);
        if (RET_FAILED(ret))
        {
            break;
        }

        /**
         * out is optional
         */
        ret = ParseArguments(&action->out, JsonObject_GetArray(object, "out"), properties);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    if (RET_FAILED(ret) && action != NULL)
    {
        Action_Delete(action);
        action = NULL;
    }

    return action;
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
        JsonArray *actions = NULL;

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
            LOG_E(TAG, "properties.type is not JsonObject");
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
            LOG_E(TAG, "Urn_SetString failed");
            break;
        }

        if (service->type.type != SERVICE)
        {
            LOG_E(TAG, "property.type invalid");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        for (uint32_t i = 0; i < properties->values.size; ++i)
        {
            JsonValue *value = (JsonValue *) TinyList_GetAt(&properties->values, i);
            Property *property = Property_NewInstance(diid, service->iid, value->data.object);
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

        /**
         * Actions is optional
         */
        actions = JsonObject_GetArray(object, "actions");
        if (actions != NULL)
        {
            if (actions->type != JSON_OBJECT)
            {
                LOG_E(TAG, "actions.type is not JsonObject");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            for (uint32_t i = 0; i < actions->values.size; ++i)
            {
                JsonValue *value = (JsonValue *) TinyList_GetAt(&actions->values, i);
                Action *action = Action_NewInstance(diid, service->iid, value->data.object, &service->properties);
                if (action == NULL)
                {
                    LOG_E(TAG, "Action_NewInstance failed");
                    ret = TINY_RET_E_ARG_INVALID;
                    break;
                }

                ret = TinyList_AddTail(&service->actions, action);
                if (RET_FAILED(ret))
                {
                    break;
                }
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
            JsonValue *value = (JsonValue *) TinyList_GetAt(&array->values, i);
            Service *service = Service_NewInstance(device->iid, value->data.object);
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