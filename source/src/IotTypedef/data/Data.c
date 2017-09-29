/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Data.c
*
* @remark
*
*/

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "Data.h"

#define TAG                     "Data"

TINY_LOR
TinyRet Data_Construct(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(Data));
    thiz->type = DATATYPE_UNDEFINED;

    return TINY_RET_OK;
}

TINY_LOR
void Data_Dispose(Data *thiz)
{
    RETURN_IF_FAIL(thiz);

    switch (thiz->type) {
        case DATATYPE_STRING:
            StringValue_Clear(&thiz->value.stringValue);
            break;

        case DATATYPE_TLV8:
            Tlv8Value_Dispose(&thiz->value.tlv8Value);
            break;

        case DATATYPE_DATA:
            DataBlobValue_Clear(&thiz->value.dataBlobValue);
            break;

        default:
            break;
    }

    memset(thiz, 0, sizeof(Data));
}

TINY_LOR
TinyRet Data_Set(Data *thiz, Data *data)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(dst, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(src, TINY_RET_E_ARG_NULL);

    switch (data->type)
    {
        case DATATYPE_BOOL:
            Data_SetBoolValue(thiz, data->value.boolValue.value);
            break;

        case DATATYPE_UINT8:
            Data_SetUint8Value(thiz, data->value.uint8Value.value);
            break;

        case DATATYPE_UINT16:
            Data_SetUint16Value(thiz, data->value.uint16Value.value);
            break;

        case DATATYPE_UINT32:
            Data_SetUint32Value(thiz, data->value.uint32Value.value);
            break;

        case DATATYPE_UINT64:
            Data_SetUint64Value(thiz, data->value.uint64Value.value);
            break;

        case DATATYPE_INT:
            Data_SetIntValue(thiz, data->value.intValue.value);
            break;

        case DATATYPE_FLOAT:
            Data_SetFloatValue(thiz, data->value.floatValue.value);
            break;

        case DATATYPE_STRING:
            Data_SetStringValue(thiz, data->value.stringValue.value);
            break;

        case DATATYPE_TLV8:
            Data_SetTlv8Value(thiz, data->value.tlv8Value._bytes, data->value.tlv8Value._size);
            break;

        case DATATYPE_DATA:
            Data_SetDataValue(thiz, data->value.dataBlobValue.value);
            break;

        case DATATYPE_UNDEFINED:
            ret = TINY_RET_E_ARG_INVALID;
            break;
    }

    return ret;
}

TINY_LOR
TinyRet Data_Copy(Data *dst, Data *src)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(dst, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(src, TINY_RET_E_ARG_NULL);

    if (dst != src)
    {
        Data_Dispose(dst);

        switch (src->type) {
            case DATATYPE_STRING:
                ret = StringValue_Copy(&src->value.stringValue, &src->value.stringValue);
                break;

            case DATATYPE_DATA:
                ret = DataBlobValue_Copy(&src->value.dataBlobValue, &src->value.dataBlobValue);
                break;

            default:
                memcpy(dst, src, sizeof(Data));
                break;
        }
    }

    return ret;
}

TINY_LOR
TinyRet Data_SetMaxLength(Data *thiz, uint32_t length)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_STRING)
    {
        LOG_E(TAG, "DataType not string");
        return TINY_RET_E_INTERNAL;
    }

    return StringValue_SetMaxLength(&thiz->value.stringValue, length);
}

TINY_LOR
TinyRet Data_SetUint8ValueRange(Data *thiz, uint8_t min, uint8_t max, uint8_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT8)
    {
        LOG_E(TAG, "DataType not uint8");
        return TINY_RET_E_INTERNAL;
    }

    return Uint8Value_SetRange(&thiz->value.uint8Value, min, max, step);
}

TINY_LOR
TinyRet Data_SetUint16ValueRange(Data *thiz, uint16_t min, uint16_t max, uint16_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT16)
    {
        LOG_E(TAG, "DataType not uint16");
        return TINY_RET_E_INTERNAL;
    }

    return Uint16Value_SetRange(&thiz->value.uint16Value, min, max, step);
}

TINY_LOR
TinyRet Data_SetUint32ValueRange(Data *thiz, uint32_t min, uint32_t max, uint32_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT32)
    {
        LOG_E(TAG, "DataType not uint32");
        return TINY_RET_E_INTERNAL;
    }

    return Uint32Value_SetRange(&thiz->value.uint32Value, min, max, step);
}

TINY_LOR
TinyRet Data_SetUint64ValueRange(Data *thiz, uint64_t min, uint64_t max, uint64_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT64)
    {
        LOG_E(TAG, "DataType not uint64");
        return TINY_RET_E_INTERNAL;
    }

    return Uint64Value_SetRange(&thiz->value.uint64Value, min, max, step);
}

TINY_LOR
TinyRet Data_SetIntValueRange(Data *thiz, int32_t min, int32_t max, int32_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_INT)
    {
        LOG_E(TAG, "DataType not int");
        return TINY_RET_E_INTERNAL;
    }

    return IntValue_SetRange(&thiz->value.intValue, min, max, step);
}

TINY_LOR
TinyRet Data_SetFloatValueRange(Data *thiz, float min, float max, float step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_FLOAT)
    {
        LOG_E(TAG, "DataType not float");
        return TINY_RET_E_INTERNAL;
    }

    return FloatValue_SetRange(&thiz->value.floatValue, min, max, step);
}

#if 0
TinyRet Data_GetValue(Data *thiz, char *value, uint32_t len)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    switch (thiz->type)
    {
        case DATATYPE_UNDEFINED:
            break;

        case DATATYPE_BOOL:
            tiny_snprintf(value, len, "%s", BoolValue_ToString(&thiz->value.boolValue));
            break;

        case DATATYPE_UINT8:
            tiny_snprintf(value, len, "%ud", thiz->value.uint8Value.value);
            break;

        case DATATYPE_UINT16:
            tiny_snprintf(value, len, "%ud", thiz->value.uint16Value.value);
            break;

        case DATATYPE_UINT32:
            tiny_snprintf(value, len, "%ud", thiz->value.uint32Value.value);
            break;

        case DATATYPE_UINT64:
#if (defined _WIN32) || (defined __MAC_OSX__)
			tiny_snprintf(value, len, "%llu", thiz->value.uint64Value.value);
			//tiny_snprintf(value, len, "%I64u", thiz->value.uint64Value.value);
            //tiny_snprintf(value, len, "%ulld", thiz->value.uint64Value.value);
#else
            tiny_snprintf(value, len, "%ld", thiz->value.uint64Value.value);
#endif
            break;

        case DATATYPE_INT:
            tiny_snprintf(value, len, "%d", thiz->value.intValue.value);
            break;

        case DATATYPE_FLOAT:
            tiny_snprintf(value, len, "%f", thiz->value.floatValue.value);
            break;

        case DATATYPE_STRING:
            strncpy(value, thiz->value.stringValue.value, len);
            break;

        case DATATYPE_TLV8:
            strncpy(value, thiz->value.tlv8Value.value, len);
            break;

        case DATATYPE_DATA:
            strncpy(value, thiz->value.dataBlobValue.value, len);
            break;
    }

    return ret;
}

TinyRet Data_SetValue(Data *thiz, const char *value)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    switch (thiz->type)
    {
        case DATATYPE_UNDEFINED:
            ret = TINY_RET_E_ARG_INVALID;
            break;

        case DATATYPE_BOOL:
            BoolValue_Retrieve(&thiz->value.boolValue, value);
            break;

        case DATATYPE_UINT8:
            Uint8Value_Set(&thiz->value.uint8Value, (uint8_t)(atoi(value)));
            break;

        case DATATYPE_UINT16:
            Uint16Value_Set(&thiz->value.uint16Value, (uint16_t)(atoi(value)));
            break;

        case DATATYPE_UINT32:
            Uint32Value_Set(&thiz->value.uint32Value, (uint32_t)(atoi(value)));
            break;

        case DATATYPE_UINT64:
            Uint64Value_Set(&thiz->value.uint64Value, (uint64_t)(atol(value)));
            break;

        case DATATYPE_INT:
            IntValue_Set(&thiz->value.intValue, (int32_t)(atoi(value)));
            break;

        case DATATYPE_FLOAT:
            FloatValue_Set(&thiz->value.floatValue, (float)(atof(value)));
            break;

        case DATATYPE_STRING:
            StringValue_Set(&thiz->value.stringValue, value);
            break;

        case DATATYPE_TLV8:
            Tlv8Value_Set(&thiz->value.tlv8Value, value);
            break;

        case DATATYPE_DATA:
            DataBlobValue_Set(&thiz->value.dataBlobValue, value);
            break;

        default:
            ret = TINY_RET_E_ARG_INVALID;
            break;
    }

    return ret;
}
#endif

TINY_LOR
TinyRet Data_SetBoolValue(Data *thiz, bool value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_BOOL)
    {
        LOG_E(TAG, "DataType not bool");
        return TINY_RET_E_INTERNAL;
    }

    return BoolValue_Set(&thiz->value.boolValue, value);
}

TINY_LOR
TinyRet Data_SetUint8Value(Data *thiz, uint8_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT8)
    {
        LOG_E(TAG, "DataType not uint8");
        return TINY_RET_E_INTERNAL;
    }

    return Uint8Value_Set(&thiz->value.uint8Value, value);
}

TINY_LOR
TinyRet Data_SetUint16Value(Data *thiz, uint16_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT16)
    {
        LOG_E(TAG, "DataType not uint16");
        return TINY_RET_E_INTERNAL;
    }

    return Uint16Value_Set(&thiz->value.uint16Value, value);
}

TINY_LOR
TinyRet Data_SetUint32Value(Data *thiz, uint32_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT32)
    {
        LOG_E(TAG, "DataType not uint32");
        return TINY_RET_E_INTERNAL;
    }

    return Uint32Value_Set(&thiz->value.uint32Value, value);
}

TINY_LOR
TinyRet Data_SetUint64Value(Data *thiz, uint64_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_UINT64)
    {
        LOG_E(TAG, "DataType not uint64");
        return TINY_RET_E_INTERNAL;
    }

    return Uint64Value_Set(&thiz->value.uint64Value, value);
}

TINY_LOR
TinyRet Data_SetIntValue(Data *thiz, int32_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_INT)
    {
        LOG_E(TAG, "DataType not int");
        return TINY_RET_E_INTERNAL;
    }

    return IntValue_Set(&thiz->value.intValue, value);
}

TINY_LOR
TinyRet Data_SetFloatValue(Data *thiz, float value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_FLOAT)
    {
        LOG_E(TAG, "DataType not float");
        return TINY_RET_E_INTERNAL;
    }

    return FloatValue_Set(&thiz->value.floatValue, value);
}

TINY_LOR
TinyRet Data_SetStringValue(Data *thiz, const char * value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_STRING)
    {
        LOG_E(TAG, "DataType not string");
        return TINY_RET_E_INTERNAL;
    }

    return StringValue_Set(&thiz->value.stringValue, value);
}

TINY_LOR
TinyRet Data_SetTlv8Value(Data *thiz, const uint8_t * value, uint32_t len)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_TLV8)
    {
        LOG_E(TAG, "DataType not TLV8");
        return TINY_RET_E_INTERNAL;
    }

    return Tlv8Value_Parse(&thiz->value.tlv8Value, (const uint8_t *)value, len, false);
}

TINY_LOR
TinyRet Data_SetDataValue(Data *thiz, const char * value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    if (thiz->type != DATATYPE_DATA)
    {
        LOG_E(TAG, "DataType not DATA");
        return TINY_RET_E_INTERNAL;
    }

    return DataBlobValue_Set(&thiz->value.dataBlobValue, value);
}

TINY_LOR
bool Data_GetBoolValue(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    if (thiz->type != DATATYPE_BOOL)
    {
        LOG_E(TAG, "DataType not bool");
        return false;
    }

    return thiz->value.boolValue.value;
}

TINY_LOR
uint8_t Data_GetUint8Value(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    if (thiz->type != DATATYPE_UINT8)
    {
        LOG_E(TAG, "DataType not uint8");
        return 0;
    }

    return thiz->value.uint8Value.value;
}

TINY_LOR
uint16_t Data_GetUint16Value(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    if (thiz->type != DATATYPE_UINT16)
    {
        LOG_E(TAG, "DataType not uint16");
        return 0;
    }

    return thiz->value.uint16Value.value;
}

TINY_LOR
uint32_t Data_GetUint32Value(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    if (thiz->type != DATATYPE_UINT32)
    {
        LOG_E(TAG, "DataType not uint32");
        return 0;
    }

    return thiz->value.uint32Value.value;
}

TINY_LOR
uint64_t Data_GetUint64Value(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    if (thiz->type != DATATYPE_UINT64)
    {
        LOG_E(TAG, "DataType not uint64");
        return 0;
    }

    return thiz->value.uint64Value.value;
}

TINY_LOR
int32_t Data_GetIntValue(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    if (thiz->type != DATATYPE_INT)
    {
        LOG_E(TAG, "DataType not int");
        return 0;
    }

    return thiz->value.intValue.value;
}

TINY_LOR
float Data_GetFloatValue(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0.0f);

    if (thiz->type != DATATYPE_FLOAT)
    {
        LOG_E(TAG, "DataType not float");
        return 0.0f;
    }

    return thiz->value.floatValue.value;
}

TINY_LOR
const char * Data_GetStringValue(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, NULL);

    if (thiz->type != DATATYPE_STRING)
    {
        LOG_E(TAG, "DataType not string");
        return NULL;
    }

    return thiz->value.stringValue.value;
}

#if 0
const char * Data_GetTlv8Value(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, NULL);

    if (thiz->type != DATATYPE_TLV8)
    {
        LOG_E(TAG, "DataType not TLV8");
        return NULL;
    }

    return thiz->value.tlv8Value.value;
}

const char * Data_GetDataValue(Data *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, NULL);

    if (thiz->type != DATATYPE_DATA)
    {
        LOG_E(TAG, "DataType not data");
        return NULL;
    }

    return thiz->value.dataBlobValue.value;
}
#endif