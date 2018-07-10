/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
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

#include <tiny_base.h>
#include <data/Data.h>
#include "PID.h"

TINY_BEGIN_DECLS


typedef struct _PropertyOperations
{
    TinyList        properties;
} PropertyOperations;

TINY_LOR
PropertyOperations * PropertyOperations_New(void);

TINY_LOR
void PropertyOperations_Delete(PropertyOperations *thiz);

TINY_LOR
TinyRet PropertyOperations_Construct(PropertyOperations *thiz);

TINY_LOR
void PropertyOperations_Dispose(PropertyOperations *thiz);

TINY_LOR
TinyRet PropertyOperations_Copy(PropertyOperations *dst, PropertyOperations *src);


TINY_END_DECLS

#endif /* __PROPERTY_OPERATIONS_H__  */