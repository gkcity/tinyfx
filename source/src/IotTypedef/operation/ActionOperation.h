/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   ActionOperation.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ACTION_OPERATION_H__
#define __ACTION_OPERATION_H__

#include <tiny_base.h>
#include <JsonArray.h>
#include "AID.h"
#include "PropertyOperations.h"

TINY_BEGIN_DECLS


typedef struct _ActionOperation
{
    AID                     aid;
    int                     status;
    JsonArray             * in;
    JsonArray             * out;
} ActionOperation;

TINY_LOR
ActionOperation * ActionOperation_New(void);

TINY_LOR
void ActionOperation_Delete(ActionOperation *thiz);

TINY_LOR
TinyRet ActionOperation_Construct(ActionOperation *thiz);

TINY_LOR
void ActionOperation_Dispose(ActionOperation *thiz);

TINY_LOR
TinyRet ActionOperation_Copy(ActionOperation *dst, ActionOperation *src);


TINY_END_DECLS

#endif /* __ACTION_OPERATION_H__  */