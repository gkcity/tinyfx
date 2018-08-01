/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   ActionOperation.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "ActionOperation.h"

#define TAG     "ActionOperation"

TINY_LOR
ActionOperation * ActionOperation_New(void)
{
    ActionOperation *thiz = NULL;

    do
    {
        thiz = (ActionOperation *)tiny_malloc(sizeof(ActionOperation));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ActionOperation_Construct(thiz)))
        {
            ActionOperation_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void ActionOperation_Delete(ActionOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    ActionOperation_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet ActionOperation_Construct(ActionOperation *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ActionOperation));

    return ret;
}

TINY_LOR
void ActionOperation_Dispose(ActionOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    JsonArray_Dispose(&thiz->in);
    JsonArray_Dispose(&thiz->out);
}

TINY_LOR
TinyRet ActionOperation_Copy(ActionOperation *dst, ActionOperation *src)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(dst, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(src, TINY_RET_E_ARG_NULL);

    if (src != dst)
    {
        strncpy(dst->aid.did, src->aid.did, DEVICE_ID_LENGTH);
        dst->aid.siid = src->aid.siid;
        dst->aid.iid = src->aid.iid;
        dst->status = src->status;
        JsonArray_Copy(&dst->in, &src->in);
        JsonArray_Copy(&dst->out, &src->out);
    }

    return ret;
}