/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Uint64Value.c
 *
 * @remark
 *
 */

#include "Uint64Value.h"
#include <tiny_log.h>

#define TAG     "Uint64Value"

TINY_LOR
static bool isValidValue(Uint64Value *thiz, uint64_t value)
{
    if (! thiz->hasRange) {
        return true;
    }

    if (value < thiz->range.min) {
#ifdef __MAC_OSX__
        LOG_D(TAG, "value(%llu) < min(%llu)", value, thiz->range.min);
#else
        LOG_D(TAG, "value(%ld) < min(%ld)", (long)value, (long)thiz->range.min);
#endif
        return false;
    }

    if (value > thiz->range.max) {
#ifdef __MAC_OSX__
        LOG_D(TAG, "value(%llu) > max(%llu)", value, thiz->range.max);
#else
        LOG_D(TAG, "value(%ld) > max(%ld)", (long)value, (long)thiz->range.max);
#endif
        return false;
    }

    if (thiz->range.hasStep)
    {
        uint64_t d = value - thiz->range.min;
        if ((d % thiz->range.step) > 0)
        {
#ifdef __MAC_OSX__
            LOG_D(TAG, "value(%llu) invalid, step is %llu", value, thiz->range.step);
#else
            LOG_D(TAG, "value(%ld) invalid, step is %ld", (long)value, (long)thiz->range.step);
#endif
            return false;
        }
    }

    return true;
}

TINY_LOR
TinyRet Uint64Value_SetRange(Uint64Value *thiz, uint64_t min, uint64_t max, uint64_t step)
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
TinyRet Uint64Value_Set(Uint64Value *thiz, uint64_t value)
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
