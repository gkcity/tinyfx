/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertyOnControl.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_ON_CONTROL_H__
#define __PROPERTY_ON_CONTROL_H__

#include <operation/PropertyOperation.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef void (*PropertyOnGet)(PropertyOperation *operation);
typedef void (*PropertyOnSet)(PropertyOperation *operation);
typedef void (*PropertyOnChanged)(PropertyOperation *operation);


TINY_END_DECLS

#endif /* __PROPERTY_ON_CONTROL_H__ */