/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpInstanceHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=454
 *      set expandtab
 */

#ifndef __HTTP_INSTANCE_HANDLER_H__
#define __HTTP_INSTANCE_HANDLER_H__

#include <channel/ChannelHandler.h>
#include "HttpInstanceHandlerContext.h"

TINY_BEGIN_DECLS


#define HttpInstanceHandler_Name "HttpInstanceHandler"

TINY_LOR
ChannelHandler * HttpInstanceHandler(HttpInstanceHandlerContext *context);


TINY_END_DECLS

#endif /* __HTTP_INSTANCE_HANDLER_H__ */