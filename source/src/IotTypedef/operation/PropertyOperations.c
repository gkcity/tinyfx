/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertyOperations.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "PropertyOperations.h"
#include "PropertyOperation.h"

#define TAG     "PropertyOperations"

TINY_LOR
static void OnPropertyOperationDelete(void *data, void *ctx)
{
    PropertyOperation_Delete((PropertyOperation *) data);
}

TINY_LOR
PropertyOperations * PropertyOperations_New(void)
{
    PropertyOperations *thiz = NULL;

    do
    {
        thiz = (PropertyOperations *)tiny_malloc(sizeof(PropertyOperations));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(PropertyOperations_Construct(thiz)))
        {
            PropertyOperations_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void PropertyOperations_Delete(PropertyOperations *thiz)
{
    PropertyOperations_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet PropertyOperations_Construct(PropertyOperations *thiz)
{
    return TinyList_Construct(&thiz->properties, OnPropertyOperationDelete, NULL);
}

TINY_LOR
void PropertyOperations_Dispose(PropertyOperations *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->properties);
}

TINY_LOR
TinyRet PropertyOperations_Copy(PropertyOperations *dst, PropertyOperations *src)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(dst, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(src, TINY_RET_E_ARG_NULL);

    if (src != dst)
    {
        for (uint32_t i = 0; i < src->properties.size; ++i)
        {
            PropertyOperation * o = (PropertyOperation *) TinyList_GetAt(&src->properties, i);
            PropertyOperation * newOperation = PropertyOperation_CopyFrom(o);
            if (newOperation == NULL)
            {
                ret = TINY_RET_E_NEW;
                break;
            }

            ret = TinyList_AddTail(&dst->properties, newOperation);
            if (RET_FAILED(ret))
            {
                break;
            }
        }
    }

    return ret;
}
