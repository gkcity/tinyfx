/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOperation.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "EventOperation.h"

#define TAG     "EventOperation"

TINY_LOR
EventOperation * EventOperation_New(void)
{
    EventOperation *thiz = NULL;

    do
    {
        thiz = (EventOperation *)tiny_malloc(sizeof(EventOperation));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(EventOperation_Construct(thiz)))
        {
            EventOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void EventOperation_Delete(EventOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    EventOperation_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet EventOperation_Construct(EventOperation *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(EventOperation));

    return ret;
}

TINY_LOR
void EventOperation_Dispose(EventOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->arguments != NULL)
    {
        JsonArray_Delete(thiz->arguments);
    }
}

TINY_LOR
EventOperation * EventOperation_CopyFrom(EventOperation *other)
{
    EventOperation * thiz = NULL;

    RETURN_VAL_IF_FAIL(other, NULL);

    do
    {
        thiz = (EventOperation *)tiny_malloc(sizeof(EventOperation));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(EventOperation_Construct(thiz)))
        {
            EventOperation_Delete(thiz);
            thiz = NULL;
            break;
        }

        strncpy(thiz->eid.did, other->eid.did, IOT_DEVICE_ID_LENGTH);
        thiz->eid.siid = other->eid.siid;
        thiz->eid.iid = other->eid.iid;
        thiz->status = other->status;

        if (other->arguments == NULL)
        {
            break;
        }

        thiz->arguments = JsonArray_NewFrom(other->arguments);
        if (thiz->arguments == NULL)
        {
            EventOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
TinyRet EventOperation_Copy(EventOperation *dst, EventOperation *src)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(dst, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(src, TINY_RET_E_ARG_NULL);

    do
    {
        if (src == dst)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        strncpy(dst->eid.did, src->eid.did, IOT_DEVICE_ID_LENGTH);
        dst->eid.siid = src->eid.siid;
        dst->eid.iid = src->eid.iid;
        dst->status = src->status;

        if (src->arguments == NULL)
        {
            break;
        }

        if (dst->arguments != NULL)
        {
            JsonArray_Delete(dst->arguments);
            dst->arguments = NULL;
        }

        dst->arguments = JsonArray_NewFrom(src->arguments);
        if (dst->arguments == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (false);

    return ret;
}