/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   PropertiesBean.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PROPERTIES_BEAN_H__
#define __PROPERTIES_BEAN_H__

#include <tiny_base.h>
#include <data/Data.h>
#include "PID.h"

TINY_BEGIN_DECLS


typedef struct _PropertiesBean
{
    TinyList        properties;
} PropertiesBean;

TINY_LOR
PropertiesBean * PropertiesBean_New(void);

TINY_LOR
void PropertiesBean_Delete(PropertiesBean *thiz);

TINY_LOR
TinyRet PropertiesBean_Construct(PropertiesBean *thiz);

TINY_LOR
void PropertiesBean_Dispose(PropertiesBean *thiz);


TINY_END_DECLS

#endif /* __PROPERTIES_BEAN_H__  */