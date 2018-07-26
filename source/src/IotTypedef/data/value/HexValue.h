/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HexValue.h
 *
 * @remark
 *
 */

#ifndef __HEX_VALUE_H__
#define __HEX_VALUE_H__

#include <tiny_lor.h>
#include "api/iot_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _HexValue
{
    char              * value;
    uint32_t            length;
    bool                hasMaxLength;
    uint32_t            maxLength;
} HexValue;

IOT_API
TINY_LOR
TinyRet HexValue_SetMaxLength(HexValue *thiz, uint32_t length);

IOT_API
TINY_LOR
TinyRet HexValue_Set(HexValue *thiz, const char *value);

IOT_API
TINY_LOR
TinyRet HexValue_Clear(HexValue *thiz);

IOT_API
TINY_LOR
TinyRet HexValue_Copy(HexValue *thiz, HexValue *other);


TINY_END_DECLS

#endif /* __HEX_VALUE_H__ */
