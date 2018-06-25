/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
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
#include "PropertyOperation.h"

#define TAG     "PropertyOperation"

TINY_LOR
TinyRet PropertyOperation_Construct(PropertyOperation *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(PropertyOperation));
    Data_Construct(&thiz->value);

    return TINY_RET_OK;
}

TINY_LOR
void PropertyOperation_Dispose(PropertyOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    Data_Dispose(&thiz->value);
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
void PropertyOperation_Delete(PropertyOperation *thiz)
{
    RETURN_IF_FAIL(thiz);

    PropertyOperation_Dispose(thiz);
    tiny_free(thiz);
}