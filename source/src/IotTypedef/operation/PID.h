/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   PID.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PID_H__
#define __PID_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef struct _PID
{
    uint16_t            diid;
    uint16_t            siid;
    uint16_t            iid;
} PID;


TINY_END_DECLS

#endif /* __PID_H__  */