/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   ActionBean.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "ActionBean.h"

#define TAG     "ActionBean"

TINY_LOR
ActionBean * ActionBean_New(void)
{
    ActionBean *thiz = NULL;

    do
    {
        thiz = (ActionBean *)tiny_malloc(sizeof(ActionBean));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(ActionBean_Construct(thiz)))
        {
            ActionBean_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void ActionBean_Delete(ActionBean *thiz)
{
    RETURN_IF_FAIL(thiz);

    ActionBean_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet ActionBean_Construct(ActionBean *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(ActionBean));

        ret = PropertiesBean_Construct(&thiz->in);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = PropertiesBean_Construct(&thiz->out);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    return TINY_RET_OK;
}

TINY_LOR
void ActionBean_Dispose(ActionBean *thiz)
{
    RETURN_IF_FAIL(thiz);

    PropertiesBean_Dispose(&thiz->in);
    PropertiesBean_Dispose(&thiz->out);
}