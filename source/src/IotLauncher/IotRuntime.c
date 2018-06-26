/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotRuntime.c
 *
 * @remark
 *
 */

#include "IotRuntime.h"

TINY_LOR
void IotRuntime_Copy(IotRuntime *dst, IotRuntime *src)
{
    if (dst != src)
    {
        dst->Name           = src->Name;
        dst->Initialize     = src->Initialize;
        dst->Run            = src->Run;
        dst->Stop           = src->Stop;
        dst->Destroy        = src->Destroy;
        dst->context        = src->context;
    }
}