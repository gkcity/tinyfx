/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Action.h
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "Action.h"
#include "Property.h"

#define TAG     "Action"

TINY_LOR
static TinyRet Action_Construct(Action *thiz);

TINY_LOR
static void Action_Dispose(Action *thiz);

TINY_LOR
static void in_release_handler(void *data, void *ctx)
{
}

TINY_LOR
static void out_release_handler(void *data, void *ctx)
{
}

TINY_LOR
Action* Action_New(void)
{
    Action *thiz = NULL;

    do
    {
        thiz = (Action *)tiny_malloc(sizeof(Action));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Action_Construct(thiz)))
        {
            Action_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Action_Construct(Action *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Action));

        ret = Urn_Construct(&thiz->type);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Urn_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        ret = TinyList_Construct(&thiz->in);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        thiz->in.additionalData = thiz;
        TinyList_SetDeleteListener(&thiz->in, in_release_handler, thiz);

        ret = TinyList_Construct(&thiz->out);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str( ret));
            break;
        }

        thiz->out.additionalData = thiz;
        TinyList_SetDeleteListener(&thiz->out, out_release_handler, thiz);
    } while (false);

    return ret;
}

TINY_LOR
static void Action_Dispose(Action *thiz)
{
    RETURN_IF_FAIL(thiz);

    Urn_Dispose(&thiz->type);
    TinyList_Dispose(&thiz->in);
    TinyList_Dispose(&thiz->out);
}

TINY_LOR
void Action_Delete(Action *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Action_Delete (iid: %d)", thiz->iid);

    Action_Dispose(thiz);
    tiny_free(thiz);
}