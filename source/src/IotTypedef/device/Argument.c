/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Argument.c
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <tiny_malloc.h>
#include "Argument.h"

#define TAG     "Argument"

TINY_LOR
static TinyRet Argument_Construct(Argument *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    thiz->iid = 0;

    return TINY_RET_OK;
}

TINY_LOR
static void Argument_Dispose(Argument *thiz)
{
    RETURN_IF_FAIL(thiz);
}

TINY_LOR
Argument* Argument_New(void)
{
    Argument *thiz = NULL;

    do
    {
        thiz = (Argument *)tiny_malloc(sizeof(Argument));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Argument_Construct(thiz)))
        {
            Argument_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void Argument_Delete(Argument *thiz)
{
    RETURN_IF_FAIL(thiz);

    Argument_Dispose(thiz);
    tiny_free(thiz);
}