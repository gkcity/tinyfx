/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertyOperation.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <tiny_malloc.h>
#include <StringArray.h>
#include "PropertyOperation.h"

#define TAG     "PropertyOperation"

TINY_LOR
TinyRet PropertyOperation_Construct(PropertyOperation *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(PropertyOperation));
    thiz->status = 0;

    return TINY_RET_OK;
}

TINY_LOR
void PropertyOperation_Dispose(PropertyOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->value != NULL)
    {
        JsonValue_Delete(thiz->value);
        thiz->value = NULL;
    }
}

TINY_LOR
PropertyOperation * PropertyOperation_New(void)
{
    PropertyOperation *thiz = NULL;

    do
    {
        thiz = (PropertyOperation *)tiny_malloc(sizeof(PropertyOperation));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(PropertyOperation_Construct(thiz)))
        {
            PropertyOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
PropertyOperation * PropertyOperation_NewFrom(const char *did, uint16_t siid, uint16_t piid)
{
    PropertyOperation *thiz = PropertyOperation_New();
    if (thiz != NULL)
    {
        strncpy(thiz->pid.did, did, DEVICE_ID_LENGTH);
        thiz->status = 0;
        thiz->pid.siid = siid;
        thiz->pid.iid = piid;
    }

    return thiz;
}

TINY_LOR
PropertyOperation * PropertyOperation_NewValue(const char *did, uint16_t siid, uint16_t piid, JsonValue *value)
{
    PropertyOperation *thiz = NULL;

    do
    {
        thiz = PropertyOperation_New();
        if (thiz == NULL)
        {
            break;
        }

        strncpy(thiz->pid.did, did, DEVICE_ID_LENGTH);
        thiz->status = 0;
        thiz->pid.siid = siid;
        thiz->pid.iid = piid;

        thiz->value = JsonValue_NewFrom(value);
        if (thiz->value == NULL)
        {
            PropertyOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
PropertyOperation * PropertyOperation_NewFromHomeKit(const char *value)
{
    PropertyOperation *thiz = NULL;
    StringArray * pid = NULL;

    do
    {
        char *stop = NULL;

        pid = StringArray_NewString(value, ".");
        if (pid == NULL)
        {
            LOG_E(TAG, "pid invalid: %s", value);
            break;
        }

        if (pid->values.size != 2)
        {
            LOG_E(TAG, "pid invalid: %s", value);
            break;
        }

        thiz = PropertyOperation_New();
        if (thiz == NULL)
        {
            LOG_E(TAG, "PropertyBean_New FAILED!");
            break;
        }

        thiz->pid.aid = (uint16_t) strtol((const char *) TinyList_GetAt(&pid->values, 0), &stop, 10);
        thiz->pid.iid = (uint16_t) strtol((const char *) TinyList_GetAt(&pid->values, 1), &stop, 10);
    } while (false);

    if (pid != NULL)
    {
        StringArray_Delete(pid);
    }

    return thiz;
}

TINY_LOR
PropertyOperation * PropertyOperation_CopyFrom(PropertyOperation *other)
{
    PropertyOperation * thiz = NULL;

    RETURN_VAL_IF_FAIL(other, NULL);

    do
    {
        thiz = PropertyOperation_New();
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        strncpy(thiz->pid.did, other->pid.did, DEVICE_ID_LENGTH);
        thiz->pid.siid = other->pid.siid;
        thiz->pid.iid = other->pid.iid;
        thiz->status = other->status;

        if (other->value == NULL)
        {
            break;
        }

        thiz->value = JsonValue_NewFrom(other->value);
        if (thiz->value == NULL)
        {
            PropertyOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void PropertyOperation_Delete(PropertyOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    PropertyOperation_Dispose(thiz);
    tiny_free(thiz);
}
