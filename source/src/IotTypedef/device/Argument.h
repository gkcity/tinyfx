/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Argument.h
 *
 * @remark
 *
 */

#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include "tiny_base.h"
#include "api/iot_api.h"

TINY_BEGIN_DECLS


typedef struct _Argument
{
    uint16_t            iid;
} Argument;

IOT_API
TINY_LOR
Argument* Argument_New(void);

IOT_API
TINY_LOR
void Argument_Delete(Argument *thiz);


TINY_END_DECLS

#endif /* __ARGUMENT_H__ */
