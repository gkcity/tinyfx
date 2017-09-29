/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   PropertyBean.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PROPERTY_BEAN_H__
#define __PROPERTY_BEAN_H__

#include <tiny_base.h>
#include <data/Data.h>
#include "PID.h"

TINY_BEGIN_DECLS


typedef struct _PropertyBean
{
    PID         pid;
    int         status;
    Data        value;
} PropertyBean;

TINY_LOR
PropertyBean * PropertyBean_New(void);

TINY_LOR
void PropertyBean_Delete(PropertyBean *thiz);

TINY_LOR
TinyRet PropertyBean_Construct(PropertyBean *thiz);

TINY_LOR
void PropertyBean_Dispose(PropertyBean *thiz);


TINY_END_DECLS

#endif /* __PROPERTY_BEAN_H__  */