/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   FloatValue.c
 *
 * @remark
 *
 */

#include "FloatValue.h"
#include <tiny_log.h>

#define TAG     "FloatValue"

TINY_LOR
static bool isValidValue(FloatValue *thiz, float value)
{
    if (! thiz->hasRange) {
        return true;
    }

    if (value < thiz->range.min) {
        LOG_D(TAG, "value(%f) < min(%f)", value, thiz->range.min);
        return false;
    }

    if (value > thiz->range.max) {
        LOG_D(TAG, "value(%f) > max(%f)", value, thiz->range.max);
        return false;
    }

    if (thiz->range.hasStep)
    {
        float d = value - thiz->range.min;
        float c = (d / thiz->range.step);
        float x = c - (int)c;
        if (x > 0.0f)
        {
            LOG_D(TAG, "value(%f) invalid, step is %f", value, thiz->range.step);
            return false;
        }
    }

    return true;
}

TINY_LOR
TinyRet FloatValue_SetRange(FloatValue *thiz, float min, float max, float step)
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
TinyRet FloatValue_Set(FloatValue *thiz, float value)
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
