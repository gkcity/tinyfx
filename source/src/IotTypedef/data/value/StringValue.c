/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StringValue.c
 *
 * @remark
 *
 */

#include "StringValue.h"
#include <tiny_log.h>
#include <tiny_strdup.h>
#include <tiny_malloc.h>

#define TAG     "StringValue"

TINY_LOR
static bool isValidLength(StringValue *thiz, size_t len)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    if (! thiz->hasMaxLength) {
        return true;
    }

    if (len <= thiz->maxLength) {
        return true;
    }

    return false;
}

TINY_LOR
TinyRet StringValue_SetMaxLength(StringValue *thiz, uint32_t length)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (length == 0)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->hasMaxLength = true;
    thiz->maxLength = length;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet StringValue_Set(StringValue *thiz, const char *string)
{
    size_t len = 0;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(string, TINY_RET_E_ARG_NULL);

    len = strlen(string);

    if (!isValidLength(thiz, len))
    {
        LOG_E(TAG, "value too long");
        return TINY_RET_E_ARG_INVALID;
    }

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
    }

    thiz->value = tiny_strdup(string);
    thiz->length = (uint32_t)len;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet StringValue_Clear(StringValue *thiz)
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
TinyRet StringValue_Copy(StringValue *thiz, StringValue *other)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(other, TINY_RET_E_ARG_NULL);

    if (thiz == other)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->hasMaxLength = other->hasMaxLength;
    thiz->maxLength = other->maxLength;
    thiz->length = other->length;

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
        thiz->value = NULL;
    }

    thiz->value = tiny_strdup(other->value);

    return TINY_RET_OK;
}