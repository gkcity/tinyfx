/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertyOperations.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PROPERTY_OPERATIONS_H__
#define __PROPERTY_OPERATIONS_H__

#include "api/iot_api.h"
#include <tiny_base.h>
#include <data/Data.h>
#include "PID.h"

TINY_BEGIN_DECLS


typedef struct _PropertyOperations
{
    TinyList        properties;
} PropertyOperations;

IOT_API
TINY_LOR
PropertyOperations * PropertyOperations_New(void);

IOT_API
TINY_LOR
void PropertyOperations_Delete(PropertyOperations *thiz);

IOT_API
TINY_LOR
TinyRet PropertyOperations_Construct(PropertyOperations *thiz);

IOT_API
TINY_LOR
void PropertyOperations_Dispose(PropertyOperations *thiz);

IOT_API
TINY_LOR
TinyRet PropertyOperations_Copy(PropertyOperations *dst, PropertyOperations *src);


TINY_END_DECLS

#endif /* __PROPERTY_OPERATIONS_H__  */
