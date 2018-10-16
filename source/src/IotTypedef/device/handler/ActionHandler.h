/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ActionHandler.h
 *
 * @remark
 *
 */

#ifndef __ACTION_HANDLER_H__
#define __ACTION_HANDLER_H__

#include <tiny_base.h>
#include <operation/ActionOperation.h>

TINY_BEGIN_DECLS


typedef void (*ActionOnInvoke)(ActionOperation *operation);


TINY_END_DECLS

#endif /* __ACTION_HANDLER_H__ */