/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertyOperation.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PROPERTY_OPERATION_H__
#define __PROPERTY_OPERATION_H__

#include "api/iot_api.h"
#include <tiny_base.h>
#include <JsonValue.h>
#include "PID.h"

TINY_BEGIN_DECLS

typedef struct _PropertyOperation
{
    PID             pid;
    int             status;
    JsonValue     * value;
} PropertyOperation;

IOT_API
TINY_LOR
PropertyOperation * PropertyOperation_New(void);

IOT_API
TINY_LOR
PropertyOperation * PropertyOperation_NewFrom(const char *did, uint16_t siid, uint16_t piid);

IOT_API
TINY_LOR
PropertyOperation * PropertyOperation_NewValue(const char *did, uint16_t siid, uint16_t piid, JsonValue *value);

IOT_API
TINY_LOR
PropertyOperation * PropertyOperation_NewFromHomeKit(const char *value);

IOT_API
TINY_LOR
PropertyOperation * PropertyOperation_CopyFrom(PropertyOperation *other);

IOT_API
TINY_LOR
void PropertyOperation_Delete(PropertyOperation *thiz);

IOT_API
TINY_LOR
TinyRet PropertyOperation_Construct(PropertyOperation *thiz);

IOT_API
TINY_LOR
void PropertyOperation_Dispose(PropertyOperation *thiz);


TINY_END_DECLS

#endif /* __PROPERTY_OPERATION_H__  */
