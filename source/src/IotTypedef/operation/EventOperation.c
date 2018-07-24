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