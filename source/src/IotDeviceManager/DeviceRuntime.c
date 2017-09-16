/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceRuntime.c
 *
 * @remark
 *
 */

#include "DeviceRuntime.h"

TINY_LOR
void DeviceRuntime_Copy(DeviceRuntime *dst, DeviceRuntime *src)
{
    if (dst != src)
    {
        dst->Name           = src->Name;
        dst->Initialize     = src->Initialize;
        dst->Run            = src->Run;
        dst->Stop           = src->Stop;
        dst->Destroy        = src->Destroy;
        dst->persistence    = src->persistence;
    }
}