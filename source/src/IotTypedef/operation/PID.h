/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
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
#include "api/iot_api.h"
#include <constant/iot_constant.h>

TINY_BEGIN_DECLS


typedef struct _PID
{
    char                did[DEVICE_ID_LENGTH];      /** device id */
    uint16_t            siid;                       /** service instance id */
    uint16_t            iid;                        /** property instance id */
    uint16_t            aid;                        /** homekit accessory id */
} PID;

IOT_API
TINY_LOR
PID * PID_New(void);

IOT_API
TINY_LOR
void PID_Delete(PID *thiz);


TINY_END_DECLS

#endif /* __PID_H__  */
