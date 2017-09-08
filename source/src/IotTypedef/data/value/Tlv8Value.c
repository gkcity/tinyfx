/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Tlv8Value.c
 *
 * @remark
 *
 */
#include <tiny_malloc.h>
#include <tiny_log.h>
#include "Tlv8Value.h"

#define TAG         "Tlv8Value"


TINY_LOR
static int toBytes(Tlv8Value *thiz);

TINY_LOR
static TinyRet AddSeparator(Tlv8Value *thiz);

//static TinyRet AddByteValue(Tlv8Value *thiz, uint8_t type, uint8_t value);

TINY_LOR
static TinyRet AddBytesValue(Tlv8Value *thiz, uint8_t type, size_t length, uint8_t *value);

TINY_LOR
static void _OnDelete(void * data, void * ctx)
{
    Tlv8 *tlv8 = (Tlv8 *)data;
    Tlv8_Delete(tlv8);
}

TINY_LOR
static bool _OnSearch(void * data, void * ctx)
{
    Tlv8 *tlv8 = (Tlv8 *)data;
    uint8_t type = *((uint8_t *)(ctx));
    return (type == tlv8->type);
}

#if 0
TinyRet Tlv8Value_Set(Tlv8Value *thiz, const char *tlv8)
{
    size_t len = strlen(tlv8);

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
    }

    thiz->value = tiny_strdup(tlv8);
    thiz->length = (uint32_t)len;

    return TINY_RET_OK;
}

TinyRet Tlv8Value_Clear(Tlv8Value *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
        thiz->value = NULL;
        thiz->length = 0;
    }

    return TINY_RET_OK;
}

TinyRet Tlv8Value_Copy(Tlv8Value *thiz, Tlv8Value *other)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(other, TINY_RET_E_ARG_NULL);

    if (thiz == other)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->length = other->length;

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
        thiz->value = NULL;
    }

    thiz->value = tiny_strdup(other->value);

    return TINY_RET_OK;
}
#endif

TINY_LOR
TinyRet Tlv8Value_Construct(Tlv8Value *thiz)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        memset(thiz, 0, sizeof(Tlv8Value));

        ret = TinyList_Construct(&thiz->values);
        if (RET_FAILED(ret))
        {
            break;
        }

        TinyList_SetDeleteListener(&thiz->values, _OnDelete, NULL);
    } while (0);

    return ret;
}

TINY_LOR
void Tlv8Value_Dispose(Tlv8Value *thiz)
{
    TinyList_Dispose(&thiz->values);

    if (thiz->_bytes != NULL)
    {
        tiny_free(thiz->_bytes);
        thiz->_bytes = NULL;
    }

    thiz->_size = 0;
}

TINY_LOR
const uint8_t * Tlv8Value_GetBytes(Tlv8Value *thiz)
{
    if (thiz->_bytes == NULL)
    {
        toBytes(thiz);
    }

    return thiz->_bytes;
}

TINY_LOR
uint32_t Tlv8Value_GetBytesSize(Tlv8Value *thiz)
{
    if (thiz->_bytes == NULL)
    {
        toBytes(thiz);
    }

    return thiz->_size;
}

TINY_LOR
TinyRet Tlv8Value_Parse(Tlv8Value *thiz, const uint8_t *buf, uint32_t len, bool mergeValue)
{
    TinyRet ret = TINY_RET_OK;
    uint32_t i = 0;

    LOG_D(TAG, "Tlv8Value_Parse: %d", len);

    if (len < 3)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    while (i < (len - 2))
    {
        uint8_t type = (uint8_t) (buf[i + 0]);
        uint8_t length = (uint8_t) (buf[i + 1]);
        const uint8_t * value = buf + i + 2;

        if ((uint32_t)(value + length - buf) > len)
        {
            LOG_D(TAG, "type.length > len");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (RET_FAILED(Tlv8Value_AddBytes(thiz, type, value, length, mergeValue)))
        {
            LOG_D(TAG, "Tlv8Value_AddBytes failed.");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        i += 1 + 1 + length;
    }

    return ret;
}

TINY_LOR
Tlv8 * Tlv8Value_Get(Tlv8Value *thiz, uint8_t type)
{
    int pos = 0;

    pos = TinyList_Foreach(&thiz->values, _OnSearch, &type);
    if (pos < 0)
    {
        return NULL;
    }

    return (Tlv8 *) TinyList_GetAt(&thiz->values, pos);
}

TINY_LOR
TinyRet Tlv8Value_AddByte(Tlv8Value *thiz, uint8_t type, uint8_t value, bool mergeValue)
{
    return Tlv8Value_AddBytes(thiz, type, &value, 1, mergeValue);
}

TINY_LOR
TinyRet Tlv8Value_AddBytes(Tlv8Value *thiz, uint8_t type, const uint8_t *value, uint32_t length, bool mergeValue)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        if (mergeValue)
        {
            Tlv8 *v = Tlv8Value_Get(thiz, type);
            if (v != NULL)
            {
                ret = Tlv8_AddData(v, length, value);
                break;
            }
        }

        Tlv8 *tlv8 = Tlv8_New();
        if (tlv8 == NULL)
        {
            LOG_D(TAG, "Tlv8_New failed");
            ret = TINY_RET_E_OUT_OF_MEMORY;
            break;
        }

        if (RET_FAILED(Tlv8_Initialize(tlv8, type, length, value)))
        {
            LOG_D(TAG, "Tlv8_Initialize failed");
            Tlv8_Delete(tlv8);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->values, tlv8))) 
        {
            LOG_D(TAG, "TinyList_AddTail failed");
            Tlv8_Delete(tlv8);
            ret = TINY_RET_E_INTERNAL;
            break;
        }
    } while (0);

    return ret;
}

TINY_LOR
TinyRet Tlv8Value_AddSeparator(Tlv8Value *thiz)
{
    uint8_t value = 0;
    return Tlv8Value_AddBytes(thiz, 0xFF, &value, 0, false);
}

TINY_LOR
static int toBytes(Tlv8Value *thiz)
{
    uint32_t length = 0;

    for (uint32_t i = 0; i < thiz->values.size; ++i)
    {
        Tlv8 *v = (Tlv8 *) TinyList_GetAt(&thiz->values, i);
        size_t count = (v->length / 255);
        uint8_t len = (uint8_t)(v->length % 255);
        size_t tlvLength = (count > 0) ? ((1 + 1 + 255) * count + (1 + 1 + len)) : (1 + 1 + len);
        length += tlvLength;
    }

    if (thiz->_bytes != NULL)
    {
        tiny_free(thiz->_bytes);
        thiz->_bytes = NULL;
        thiz->_size = 0;
    }

    LOG_D(TAG, "toBytes: %d", length);

    thiz->_bytes = tiny_malloc(length);
    if (thiz->_bytes == NULL)
    {
        return -1;
    }

    thiz->_size = length;

    for (uint32_t i = 0; i < thiz->values.size; ++i)
    {
        Tlv8 *v = (Tlv8 *) TinyList_GetAt(&thiz->values, i);
        if (v->type == 0xFF)
        {
            AddSeparator(thiz);
        }
        else
        {
            AddBytesValue(thiz, v->type, v->length, v->data);
        }
    }

    return length;
}

TINY_LOR
static TinyRet AddSeparator(Tlv8Value *thiz)
{
    TinyRet ret = TINY_RET_OK;
    size_t tlv_length = 1;
    size_t unused = thiz->_size - thiz->_available;

    if (unused < tlv_length)
    {
        return TINY_RET_E_FULL;
    }

    thiz->_bytes[thiz->_available ++] = 0xFF;

    return ret;
}

#if 0
static TinyRet AddByteValue(Tlv8Value *thiz, uint8_t type, uint8_t value)
{
    TinyRet ret = TINY_RET_OK;
    size_t tlv_length = 1 + 1 + 1;
    size_t unused = thiz->_size - thiz->_available;

    LOG_D(TAG, "Tlv8_AddByteValue: type(%d) length(1) value(%d)", type, value);

    if (unused < tlv_length)
    {
        return TINY_RET_E_FULL;
    }

    thiz->_bytes[thiz->_available ++] = type;
    thiz->_bytes[thiz->_available ++] = 1;
    thiz->_bytes[thiz->_available ++] = value;

    return ret;
}
#endif

TINY_LOR
static TinyRet AddBytesValue(Tlv8Value *thiz, uint8_t type, size_t length, uint8_t *value)
{
    TinyRet ret = TINY_RET_OK;
    size_t count = (length / 255);
    uint8_t len = (uint8_t)(length % 255);
    size_t unused = thiz->_size - thiz->_available;
    size_t tlv_length = (count > 0) ? (1 + 1 + 255) * count + (1 + 1 + len) : 1 + 1 + len;

    if (unused < tlv_length)
    {
        return TINY_RET_E_FULL;
    }

    for (size_t i = 0; i < count; ++i)
    {
        thiz->_bytes[thiz->_available ++] = type;
        thiz->_bytes[thiz->_available ++] = 255;
        memcpy(thiz->_bytes + thiz->_available, value + i * 255, 255);
        thiz->_available += 255;
    }

    if (len > 0)
    {
        thiz->_bytes[thiz->_available ++] = type;
        thiz->_bytes[thiz->_available ++] = len;
        memcpy(thiz->_bytes + thiz->_available, value + count * 255, len);
        thiz->_available += len;
    }

    return ret;
}