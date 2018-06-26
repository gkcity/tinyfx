/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   AID.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __AID_H__
#define __AID_H__

#include <tiny_base.h>
#include <constraint/typedef_constraint.h>

TINY_BEGIN_DECLS


typedef struct _AID
{
    char                did[DEVICE_ID_LENGTH];
    uint16_t            siid;
    uint16_t            iid;
} AID;


TINY_END_DECLS

#endif /* __AID_H__  */