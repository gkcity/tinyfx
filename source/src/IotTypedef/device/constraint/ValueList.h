/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ValueList.h
 *
 * @remark
 *
 */

#ifndef __VALUE_LIST_H__
#define __VALUE_LIST_H__

#include <TinyList.h>
#include <JsonValue.h>
#include "tiny_base.h"
#include "api/iot_api.h"

TINY_BEGIN_DECLS


typedef struct _ValueList
{
    TinyList        list;
} ValueList;

IOT_API
TINY_LOR
ValueList* ValueList_New(void);

IOT_API
TINY_LOR
ValueList* ValueList_NewFrom(JsonArray *array);

IOT_API
TINY_LOR
void ValueList_Delete(ValueList *thiz);

IOT_API
TINY_LOR
TinyRet ValueList_Put(ValueList *thiz, JsonValue *value);

IOT_API
TINY_LOR
bool ValueList_CheckValue(ValueList *thiz, JsonValue *value);


TINY_END_DECLS

#endif /* __VALUE_LIST_H__ */
