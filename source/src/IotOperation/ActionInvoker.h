/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ActionInvoker.h
 *
 * @remark
 *
 */

#ifndef __ACTION_INVOKER_H__
#define __ACTION_INVOKER_H__

#include <JsonArray.h>
#include <tiny_base.h>
#include <device/Action.h>
#include "api/iot_api.h"

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
bool ActionInvoker_Set(Action *action, JsonArray *in);



TINY_END_DECLS

#endif /* __ACTION_INVOKER_H__ */
