/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Tlv8.c
 *
 * @remark
 *
 */

#include "Tlv8.h"
#include <tiny_malloc.h>
#include <tiny_log.h>

#define TAG     "Tlv8"

TINY_LOR
static TinyRet Tlv8_Construct(Tlv8 *thiz);

TINY_LOR
static void Tlv8_Dispose(Tlv8 *thiz);

TINY_LOR
Tlv8* Tlv8_New()
{
    Tlv8 *thiz = NULL;

    do
    {
        thiz = (Tlv8 *)tiny_malloc(sizeof(Tlv8));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Tlv8_Construct(thiz)))
        {
            Tlv8_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Tlv8_Construct(Tlv8 *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    memset(thiz, 0, sizeof(Tlv8));

    return ret;
}

TINY_LOR
static void Tlv8_Dispose(Tlv8 *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->data != NULL)
    {
        tiny_free(thiz->data);
    }

    memset(thiz, 0, sizeof(Tlv8));
}

TINY_LOR
void Tlv8_Delete(Tlv8 *thiz)
{
    RETURN_IF_FAIL(thiz);

    Tlv8_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet Tlv8_Initialize(Tlv8 *thiz, uint8_t type, uint32_t length, const uint8_t *buf)
{
    thiz->type = type;
    thiz->length = length;

    if (thiz->data != NULL)
    {
        tiny_free(thiz->data);
        thiz->data = NULL;
    }

    if (length > 0)
    {
        thiz->data = tiny_malloc(length);
        if (thiz->data == NULL)
        {
            return TINY_RET_E_OUT_OF_MEMORY;
        }

        memcpy(thiz->data, buf, length);
    }

    return TINY_RET_OK;
}

TINY_LOR
TinyRet Tlv8_AddData(Tlv8 *thiz, uint32_t dataLength, const uint8_t *data)
{
    TinyRet ret = TINY_RET_OK;
    uint8_t * newData = NULL;

    do
    {
        if (thiz->data == NULL)
        {
            thiz->data = tiny_malloc(dataLength);
            if (thiz->data == NULL)
            {
                ret = TINY_RET_E_OUT_OF_MEMORY;
                break;
            }

            memcpy(thiz->data, data, dataLength);
            break;
        }

        newData = tiny_malloc(thiz->length + dataLength);
        if (newData == NULL)
        {
            ret = TINY_RET_E_OUT_OF_MEMORY;
            break;
        }

        memcpy(newData, thiz->data, thiz->length);
        memcpy(newData + thiz->length, data, dataLength);

        tiny_free(thiz->data);

        thiz->data = newData;
        thiz->length = thiz->length + dataLength;
    } while (0);

    return ret;
}