/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ValueRange.h
 *
 * @remark
 *
 */

#ifndef __VALUE_RANGE_H__
#define __VALUE_RANGE_H__

#include <JsonValue.h>
#include "tiny_base.h"
#include "api/iot_api.h"

TINY_BEGIN_DECLS


typedef struct _ValueRange
{
    JsonValue   *min;
    JsonValue   *max;
    JsonValue   *step;
} ValueRange;

IOT_API
TINY_LOR
ValueRange* ValueRange_NewFrom(JsonArray *range);

IOT_API
TINY_LOR
void ValueRange_Delete(ValueRange *thiz);

IOT_API
TINY_LOR
bool ValueRange_CheckValue(ValueRange *thiz, JsonValue *value);


TINY_END_DECLS

#endif /* __VALUE_RANGE_H__ */
