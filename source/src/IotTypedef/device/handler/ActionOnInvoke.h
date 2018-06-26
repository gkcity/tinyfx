/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ActionOnInvoke.h
 *
 * @remark
 *
 */

#ifndef __ACTION_ON_INVOKE_H__
#define __ACTION_ON_INVOKE_H__

#include <tiny_base.h>
#include <operation/ActionOperation.h>

TINY_BEGIN_DECLS


typedef void (*ActionOnInvoke)(ActionOperation *operation);


TINY_END_DECLS

#endif /* __ACTION_ON_INVOKE_H__ */