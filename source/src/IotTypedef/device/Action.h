/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Action.h
 *
 * @remark
 *
 */

#ifndef __ACTION_H__
#define __ACTION_H__

#include <TinyList.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"

TINY_BEGIN_DECLS


struct _Action
{
    uint16_t            aiid;
    uint16_t            siid;
    uint16_t            iid;
    Urn                 type;
    TinyList            in;
    TinyList            out;
};

typedef struct _Action Action;

IOT_API
TINY_LOR
Action* Action_New(void);

IOT_API
TINY_LOR
void Action_Delete(Action *thiz);


TINY_END_DECLS

#endif /* __ACTION_H__ */
