/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DataBlobValue.c
 *
 * @remark
 *
 */

#include <tiny_strdup.h>
#include <tiny_malloc.h>
#include "DataBlobValue.h"

TINY_LOR
TinyRet DataBlobValue_Set(DataBlobValue *thiz, const char *dataBlob)
{
    size_t len = strlen(dataBlob);

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
    }

    thiz->value = tiny_strdup(dataBlob);
    thiz->length = (uint32_t)len;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet DataBlobValue_Clear(DataBlobValue *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
        thiz->value = NULL;
        thiz->length = 0;
    }

    return TINY_RET_OK;
}

TINY_LOR
TinyRet DataBlobValue_Copy(DataBlobValue *thiz, DataBlobValue *other)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(other, TINY_RET_E_ARG_NULL);

    if (thiz == other)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->length = other->length;

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
        thiz->value = NULL;
    }

    thiz->value = tiny_strdup(other->value);

    return TINY_RET_OK;
}