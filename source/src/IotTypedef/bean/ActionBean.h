/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   ActionBean.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ACTION_BEAN_H__
#define __ACTION_BEAN_H__

#include <tiny_base.h>
#include "AID.h"
#include "PropertiesBean.h"

TINY_BEGIN_DECLS


typedef struct _ActionBean
{
    AID                 aid;
    int                 status;
    PropertiesBean      in;
    PropertiesBean      out;
} ActionBean;

TINY_LOR
ActionBean * ActionBean_New(void);

TINY_LOR
void ActionBean_Delete(ActionBean *thiz);

TINY_LOR
TinyRet ActionBean_Construct(ActionBean *thiz);

TINY_LOR
void ActionBean_Dispose(ActionBean *thiz);


TINY_END_DECLS

#endif /* __ACTION_BEAN_H__  */