/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HexValue.c
 *
 * @remark
 *
 */

#include "HexValue.h"
#include <tiny_log.h>
#include <tiny_strdup.h>
#include <tiny_malloc.h>

#define TAG     "HexValue"

TINY_LOR
static bool isValidLength(HexValue *thiz, size_t len)
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
TinyRet HexValue_SetMaxLength(HexValue *thiz, uint32_t length)
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
TinyRet HexValue_Set(HexValue *thiz, const char *value)
{
    size_t len = 0;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(value, TINY_RET_E_ARG_NULL);

    len = strlen(value);

    if (!isValidLength(thiz, len))
    {
        LOG_E(TAG, "value too long");
        return TINY_RET_E_ARG_INVALID;
    }

    if (thiz->value != NULL)
    {
        tiny_free(thiz->value);
    }

    thiz->value = tiny_strdup(value);
    thiz->length = (uint32_t)len;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet HexValue_Clear(HexValue *thiz)
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
TinyRet HexValue_Copy(HexValue *thiz, HexValue *other)
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