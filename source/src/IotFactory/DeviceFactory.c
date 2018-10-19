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
#include <JsonObject.h>
#include <JsonArray.h>
#include <value/JsonNumber.h>
#include <value/JsonString.h>
#include <device/Service.h>
#include <device/Property.h>
#include <device/Action.h>
#include <tiny_snprintf.h>
#include <device/Argument.h>
#include "DeviceFactory.h"

#define TAG     "DeviceFactory"

//TINY_LOR
//static uint16_t AccessType_New(JsonArray *array)
//{
//    uint16_t a = 0;
//
//    for (uint32_t i = 0; i < array->values.size; ++i)
//    {
//        JsonValue *value = (JsonValue *) TinyList_GetAt(&array->values, i);
//        Access type = Access_Retrieve(value->data.string->value);
//        if (type == ACCESS_UNDEFINED)
//        {
//            LOG_E(TAG, "Access INVALID: %s", value->data.string->value);
//            break;
//        }
//
//        a |= type;
//    }
//
//    return a;
//}

//TINY_LOR
//static TinyRet Property_ProcessValueRange(Property *property, JsonArray *range)
//{
//    TinyRet ret = TINY_RET_OK;
//
//    do
//    {
//        JsonValue *min = NULL;
//        JsonValue *max = NULL;
//        JsonValue *step = NULL;
//
//        if (range->values.size != 3)
//        {
//            LOG_E(TAG, "range values.size not 3");
//            ret = TINY_RET_E_ARG_INVALID;
//            break;
//        }
//
//        min = (JsonValue *)TinyList_GetAt(&range->values, 0);
//        max = (JsonValue *)TinyList_GetAt(&range->values, 1);
//        step = (JsonValue *)TinyList_GetAt(&range->values, 2);
//
//        switch (property->data.type)
//        {
//            case DATATYPE_UINT8:
//                if (min->data.number->type == JSON_NUMBER_INTEGER
//                    && max->data.number->type == JSON_NUMBER_INTEGER
//                    && step->data.number->type == JSON_NUMBER_INTEGER)
//                {
//
//                    Data_SetUint8ValueRange(&property->data,
//                                            (uint8_t)min->data.number->value.intValue,
//                                            (uint8_t)max->data.number->value.intValue,
//                                            (uint8_t)step->data.number->value.intValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            case DATATYPE_UINT16:
//                if (min->data.number->type == JSON_NUMBER_INTEGER
//                    && max->data.number->type == JSON_NUMBER_INTEGER
//                    && step->data.number->type == JSON_NUMBER_INTEGER)
//                {
//
//                    Data_SetUint16ValueRange(&property->data,
//                                             (uint16_t)min->data.number->value.intValue,
//                                             (uint16_t)max->data.number->value.intValue,
//                                             (uint16_t)step->data.number->value.intValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            case DATATYPE_UINT32:
//                if (min->data.number->type == JSON_NUMBER_INTEGER
//                    && max->data.number->type == JSON_NUMBER_INTEGER
//                    && step->data.number->type == JSON_NUMBER_INTEGER)
//                {
//
//                    Data_SetUint32ValueRange(&property->data,
//                                             (uint32_t)min->data.number->value.intValue,
//                                             (uint32_t)max->data.number->value.intValue,
//                                             (uint32_t)step->data.number->value.intValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            case DATATYPE_UINT64:
//                if (min->data.number->type == JSON_NUMBER_INTEGER
//                    && max->data.number->type == JSON_NUMBER_INTEGER
//                    && step->data.number->type == JSON_NUMBER_INTEGER)
//                {
//
//                    Data_SetUint64ValueRange(&property->data,
//                                             (uint64_t)min->data.number->value.intValue,
//                                             (uint64_t)max->data.number->value.intValue,
//                                             (uint64_t)step->data.number->value.intValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            case DATATYPE_INT:
//                if (min->data.number->type == JSON_NUMBER_INTEGER
//                    && max->data.number->type == JSON_NUMBER_INTEGER
//                    && step->data.number->type == JSON_NUMBER_INTEGER)
//                {
//
//                    Data_SetIntValueRange(&property->data,
//                                          min->data.number->value.intValue,
//                                          max->data.number->value.intValue,
//                                          step->data.number->value.intValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            case DATATYPE_FLOAT:
//                if (min->data.number->type == JSON_NUMBER_FLOAT
//                    && max->data.number->type == JSON_NUMBER_FLOAT
//                    && step->data.number->type == JSON_NUMBER_FLOAT)
//                {
//                    Data_SetFloatValueRange(&property->data,
//                                            min->data.number->value.floatValue,
//                                            max->data.number->value.floatValue,
//                                            step->data.number->value.floatValue);
//                }
//                else
//                {
//                    LOG_E(TAG, "range must be JsonNumber");
//                    ret = TINY_RET_E_ARG_INVALID;
//                }
//                break;
//
//            default:
//                ret = TINY_RET_E_ARG_INVALID;
//                break;
//        }
//    } while (false);
//
//    return ret;
//}
//
//TINY_LOR
//static TinyRet Property_ProcessValueList(Property *property, JsonArray *list)
//{
//    TinyRet ret = TINY_RET_OK;
//
//    // TODO: ...
//
//    return ret;
//}

TINY_LOR
static Property* Property_NewFrom(JsonObject *object)
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

        LOG_D(TAG, "decode property: %s", type->value);

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

        property = Property_New((uint16_t) (iid->value.intValue));
        if (property == NULL)
        {
            LOG_E(TAG, "Property_New failed");
            break;
        }

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

        property->format = Format_FromString(format->value);
        if (property->format == FORMAT_UNDEFINED)
        {
            LOG_E(TAG, "Format_FromString failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        property->access = Access_FromJsonArray(access);

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
            property->valueRange = ValueRange_NewFrom(valueRange);
            if (property->valueRange == NULL)
            {
                LOG_E(TAG, "value-range invalid");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }
        }

        if (valueList != NULL)
        {
            property->valueList = ValueList_NewFrom(valueList);
            if (property->valueList == NULL)
            {
                LOG_E(TAG, "value-list invalid");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }
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
static TinyRet ParseArguments(TinyList *list, JsonArray *arguments)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(list, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(arguments, TINY_RET_E_ARG_NULL);

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

        for (uint32_t i = 0; i < arguments->values.size; ++i)
        {
            JsonValue *v = (JsonValue *) TinyList_GetAt(&arguments->values, i);
            Argument * argument = NULL;

            if (v->type != JSON_NUMBER) {
                break;
            }

            argument = Argument_New();
            if (argument == NULL)
            {
                LOG_E(TAG, "argument [%ld] invalid", v->data.number->value.intValue);
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            argument->iid= (uint16_t)v->data.number->value.intValue;
            TinyList_AddTail(list, argument);
        }
    } while (false);

    return ret;
}

TINY_LOR
static Action* Action_NewFrom(JsonObject *object, Service *service)
{
    TinyRet ret = TINY_RET_OK;
    Action *action = NULL;

    do
    {
        JsonNumber *iid = NULL;
        JsonString *type = NULL;
        JsonString *description = NULL;
        JsonArray *in = NULL;
        JsonArray *out = NULL;

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

        action = Action_New((uint16_t) (iid->value.intValue));
        if (action == NULL)
        {
            LOG_E(TAG, "Property_New failed");
            break;
        }

        action->iid = (uint16_t) (iid->value.intValue);
        action->service = service;

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
        in = JsonObject_GetArray(object, "in");
        if (in != NULL)
        {
            ret = ParseArguments(&action->in, in);
            if (RET_FAILED(ret))
            {
                break;
            }
        }

        /**
         * out is optional
         */
        out = JsonObject_GetArray(object, "out");
        if (out != NULL)
        {
            ret = ParseArguments(&action->out, out);
            if (RET_FAILED(ret))
            {
                break;
            }
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
static Service* Service_NewFrom(JsonObject *object)
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

        if (! JsonArray_CheckValuesType(properties, JSON_OBJECT)) {
            LOG_E(TAG, "check properties failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        service = Service_New((uint16_t) (iid->value.intValue));
        if (service == NULL)
        {
            LOG_E(TAG, "Service_New failed");
            break;
        }

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
            Property *property = Property_NewFrom(value->data.object);
            if (property == NULL)
            {
                LOG_E(TAG, "Property_New failed");
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
        if (actions == NULL)
        {
            break;
        }

        if (! JsonArray_CheckValuesType(actions, JSON_OBJECT)) {
            LOG_E(TAG, "check actions failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        for (uint32_t i = 0; i < actions->values.size; ++i)
        {
            JsonValue *value = (JsonValue *) TinyList_GetAt(&actions->values, i);
            Action *action = Action_NewFrom(value->data.object, service);
            if (action == NULL)
            {
                LOG_E(TAG, "Action_New failed");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            ret = TinyList_AddTail(&service->actions, action);
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
Device* Device_NewInstance(JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;
    Device* device = NULL;

    do
    {
        JsonArray * services = JsonObject_GetArray(object, "services");
        if (services == NULL)
        {
            LOG_E(TAG, "services not found!");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (! JsonArray_CheckValuesType(services, JSON_OBJECT))
        {
            LOG_E(TAG, "check services failed");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        device = Device_New();
        if (device == NULL)
        {
            LOG_E(TAG, "Device_New failed!");
            break;
        }

        for (uint32_t i = 0; i < services->values.size; ++i)
        {
            JsonValue *value = (JsonValue *) TinyList_GetAt(&services->values, i);
            Service *service = Service_NewFrom(value->data.object);
            if (service == NULL)
            {
                LOG_E(TAG, "Service_New failed");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            ret = TinyList_AddTail(&device->services, service);
            if (RET_FAILED(ret))
            {
                Service_Delete(service);
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

#define HOST "39.106.171.204"
#define PORT 80

TINY_LOR
Device* DeviceFactory_NewDevice(const char *uri, uint32_t second)
{
    Device *device = NULL;
    HttpClient *client = NULL;
    HttpExchange *exchange = NULL;
    JsonObject *object = NULL;

    LOG_I(TAG, "DeviceFactory_NewDevice -> http://%s:%d/%s", HOST, PORT, uri);

    do
    {
        client = HttpClient_New();
        if (client == NULL)
        {
            LOG_E(TAG, "HttpClient_New failed!");
            break;
        }

        exchange = HttpExchange_New(HOST, PORT, "GET", uri, second, NULL, 0);
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

        device = Device_NewInstance(object);
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

    LOG_I(TAG, "DeviceFactory_Create finished!");

    return device;
}

TINY_LOR
Device *DeviceFactory_Create(uint16_t productId, uint16_t productVersion, uint32_t second)
{
    char uri[1024];

    memset(uri, 0, 1024);
    tiny_snprintf(uri, 1014, "/dd/instance/product/%d/version/%d", productId, productVersion);

    return DeviceFactory_NewDevice(uri, second);
}
