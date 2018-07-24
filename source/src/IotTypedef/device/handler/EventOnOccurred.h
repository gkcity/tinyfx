/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   EventOnOccurred.h
 *
 * @remark
 *
 */

#ifndef __EVENT_ON_OCCURRED_H__
#define __EVENT_ON_OCCURRED_H__

#include <tiny_base.h>
#include <operation/EventOperation.h>

TINY_BEGIN_DECLS


typedef void (*EventOnOccurred)(EventOperation *operation);


TINY_END_DECLS

#endif /* __EVENT_ON_OCCURRED_H__ */