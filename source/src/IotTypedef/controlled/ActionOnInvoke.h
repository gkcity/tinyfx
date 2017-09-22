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

TINY_BEGIN_DECLS


struct _Action;
typedef struct _Action Action;

typedef void (*ActionOnInvoke)(Action *action);


TINY_END_DECLS

#endif /* __ACTION_ON_INVOKE_H__ */