/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotRuntime.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "IotRuntime.h"

#define TAG     "IotRuntime"

TINY_LOR
static TinyRet IotRuntime_Construct(IotRuntime *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(IotRuntime));

    return ret;
}

TINY_LOR
static void IotRuntime_Dispose(IotRuntime *thiz)
{
    RETURN_IF_FAIL(thiz);
}

TINY_LOR
IotRuntime * IotRuntime_New(void)
{
    IotRuntime *thiz = NULL;

    do
    {
        thiz = (IotRuntime *) tiny_malloc(sizeof(IotRuntime));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED.");
            break;
        }

        if (RET_FAILED(IotRuntime_Construct(thiz)))
        {
            IotRuntime_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void IotRuntime_Delete(IotRuntime *thiz)
{
    RETURN_IF_FAIL(thiz);

    IotRuntime_Dispose(thiz);
    tiny_free(thiz);
}