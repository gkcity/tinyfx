/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertySetter.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_SETTER_H__
#define __PROPERTY_SETTER_H__

#include <device/Property.h>
#include <JsonValue.h>
#include <tiny_base.h>
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "data/Data.h"

TINY_BEGIN_DECLS


bool PropertySetter_Set(Property *property, JsonValue *value);



TINY_END_DECLS

#endif /* __PROPERTY_SETTER_H__ */
