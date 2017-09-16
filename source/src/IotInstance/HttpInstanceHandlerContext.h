/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpInstanceHandlerContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=454
 *      set expandtab
 */

#ifndef __HTTP_INSTANCE_HANDLER_CONTEXT_H__
#define __HTTP_INSTANCE_HANDLER_CONTEXT_H__

#include <channel/ChannelHandler.h>
#include <codec-http/HttpMessage.h>

TINY_BEGIN_DECLS


typedef struct _HttpInstanceHandlerContext
{
    char                      ip[TINY_IP_LEN];
    uint16_t                  port;
    char                    * uri;
    int                       status;
    uint32_t                  length;
    char                    * content;
} HttpInstanceHandlerContext;

TINY_LOR
HttpInstanceHandlerContext * HttpInstanceHandlerContext_New(const char *ip, uint16_t port, const char *uri);

TINY_LOR
void HttpInstanceHandlerContext_Delete(HttpInstanceHandlerContext *thiz);


TINY_END_DECLS

#endif /* __HTTP_INSTANCE_HANDLER_CONTEXT_H__ */