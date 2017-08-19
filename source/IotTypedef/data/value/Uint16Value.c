/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Uint16Value.c
 *
 * @remark
 *
 */

#include "Uint16Value.h"
#include <tiny_log.h>

#define TAG     "Uint16Value"

TINY_LOR
static bool isValidValue(Uint16Value *thiz, uint16_t value)
{
    if (! thiz->hasRange) {
        return true;
    }

    if (value < thiz->range.min) {
        LOG_D(TAG, "value(%d) < min(%d)", value, thiz->range.min);
        return false;
    }

    if (value > thiz->range.max) {
        LOG_D(TAG, "value(%d) > max(%d)", value, thiz->range.max);
        return false;
    }

    if (thiz->range.hasStep)
    {
        uint16_t d = value - thiz->range.min;
        if ((d % thiz->range.step) > 0)
        {
            LOG_D(TAG, "value(%d) invalid, step is %d", value, thiz->range.step);
            return false;
        }
    }

    return true;
}

TINY_LOR
TinyRet Uint16Value_SetRange(Uint16Value *thiz, uint16_t min, uint16_t max, uint16_t step)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (min >= max)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->hasRange = true;
    thiz->range.min = min;
    thiz->range.max = max;
    thiz->range.hasStep = (step != 0);
    thiz->range.step = step;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet Uint16Value_Set(Uint16Value *thiz, uint16_t value)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (!isValidValue(thiz, value))
    {
        LOG_E(TAG, "value invalid");
        return TINY_RET_E_ARG_INVALID;
    }

    thiz->value = value;
    return TINY_RET_OK;
}