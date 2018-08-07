/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   AccessKeyHandler.h
 *
 * @remark
 *
 */

#ifndef __ACCESS_KEY_HANDLER_H__
#define __ACCESS_KEY_HANDLER_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef void (*OnGetAccessKeySucceed)(const char *accessKey);
typedef void (*OnGetAccessKeyFailed)(int status, const char *description);

typedef void (*OnResetAccessKeySucceed)(void);
typedef void (*OnResetAccessKeyFailed)(int status, const char *description);


TINY_END_DECLS

#endif /* __ACCESS_KEY_HANDLER_H__ */