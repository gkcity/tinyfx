/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   PropertyBean.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <tiny_malloc.h>
#include "PropertyBean.h"

#define TAG     "PropertyBean"

TINY_LOR
TinyRet PropertyBean_Construct(PropertyBean *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(PropertyBean));
    Data_Construct(&thiz->value);

    return TINY_RET_OK;
}

TINY_LOR
void PropertyBean_Dispose(PropertyBean *thiz)
{
    RETURN_IF_FAIL(thiz);

    Data_Dispose(&thiz->value);
}

TINY_LOR
PropertyBean * PropertyBean_New(void)
{
    PropertyBean *thiz = NULL;

    do
    {
        thiz = (PropertyBean *)tiny_malloc(sizeof(PropertyBean));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(PropertyBean_Construct(thiz)))
        {
            PropertyBean_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void PropertyBean_Delete(PropertyBean *thiz)
{
    RETURN_IF_FAIL(thiz);

    PropertyBean_Dispose(thiz);
    tiny_free(thiz);
}