/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOperation.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EVENT_OPERATION_H__
#define __EVENT_OPERATION_H__

#include <tiny_base.h>
#include <JsonArray.h>
#include <api/iot_api.h>
#include "EID.h"

TINY_BEGIN_DECLS


typedef struct _EventOperation
{
    EID                     eid;
    int                     status;
    JsonArray             * arguments;
} EventOperation;

IOT_API
TINY_LOR
EventOperation * EventOperation_New(void);

IOT_API
TINY_LOR
void EventOperation_Delete(EventOperation *thiz);

IOT_API
TINY_LOR
TinyRet EventOperation_Construct(EventOperation *thiz);

IOT_API
TINY_LOR
void EventOperation_Dispose(EventOperation *thiz);

IOT_API
TINY_LOR
EventOperation * EventOperation_CopyFrom(EventOperation *other);

IOT_API
TINY_LOR
TinyRet EventOperation_Copy(EventOperation *dst, EventOperation *src);


TINY_END_DECLS

#endif /* __EVENT_OPERATION_H__  */