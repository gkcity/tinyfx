/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EID.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EID_H__
#define __EID_H__

#include <tiny_base.h>
#include <constant/iot_constant.h>

TINY_BEGIN_DECLS


typedef struct _EID
{
    char                did[IOT_DEVICE_ID_LENGTH];
    uint16_t            siid;
    uint16_t            iid;
} EID;


TINY_END_DECLS

#endif /* __EID_H__  */
