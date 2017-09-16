/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpInstance.h
 *
 * @remark
 *
 */

#ifndef __HTPP_INSTANCE_H__
#define __HTPP_INSTANCE_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <controlled/PropertyOnControl.h>
#include <api/iot_api.h>

TINY_BEGIN_DECLS


IOT_API
TINY_LOR
JsonObject * HttpInstance_Get(const char *ip, uint16_t port, const char *uri, uint32_t second);


TINY_END_DECLS

#endif /* __HTPP_INSTANCE_H__ */