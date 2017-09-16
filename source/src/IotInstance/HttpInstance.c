/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpInstance.c
 *
 * @remark
 *
 */
#include <tiny_log.h>
#include <bootstrap/Bootstrap.h>
#include <channel/stream/StreamClientChannel.h>
#include <channel/SocketChannel.h>
#include <codec-http/HttpMessageCodec.h>
#include <channel/ChannelIdleStateHandler.h>
#include "HttpInstance.h"
#include "HttpInstanceHandler.h"

#define TAG     "HttpInstance"

static void HttpClientInitializer(Channel *channel, void *ctx)
{
    LOG_D(TAG, "HttpClientInitializer: %s", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 5));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, HttpInstanceHandler((HttpInstanceHandlerContext *)ctx));
}

TINY_LOR
JsonObject * HttpInstance_Get(const char *ip, uint16_t port, const char *uri, uint32_t second)
{
    JsonObject *object = NULL;

    do
    {
        TinyRet ret = TINY_RET_OK;

        HttpInstanceHandlerContext *context = NULL;
        Channel *client = NULL;
        Bootstrap sb;

        client = StreamClientChannel_New();
        if (client == NULL)
        {
            LOG_E(TAG, "StreamClientChannel_New FAILED!");
            break;
        }

        context = HttpInstanceHandlerContext_New(ip, port, uri);
        if (context == NULL)
        {
            LOG_E(TAG, "HttpInstanceHandlerContext_New FAILED!");
            StreamClientChannel_Delete(client);
            break;
        }

        do
        {
            ret = StreamClientChannel_Initialize(client, HttpClientInitializer, context);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "StreamClientChannel_Initialize failed: %d", TINY_RET_CODE(ret));
                break;
            }

            ret = StreamClientChannel_Connect(client, ip, port, second * 1000);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "StreamClientChannel_Connect failed: %d", TINY_RET_CODE(ret));
                break;
            }

            ret = Bootstrap_Construct(&sb);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "Bootstrap_Construct failed: %d", TINY_RET_CODE(ret));
                break;
            }

            ret = Bootstrap_AddChannel(&sb, client);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "Bootstrap_AddChannel failed: %d", TINY_RET_CODE(ret));
                break;
            }

            ret = Bootstrap_Sync(&sb);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "Bootstrap_Sync failed: %d", TINY_RET_CODE(ret));
                break;
            }

            ret = Bootstrap_Shutdown(&sb);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "Bootstrap_Shutdown failed: %d", TINY_RET_CODE(ret));
                break;
            }

            Bootstrap_Dispose(&sb);
        } while (false);

        if (RET_SUCCEEDED(ret))
        {
            if (context->status == HTTP_STATUS_OK && context->content != NULL)
            {
                object = JsonObject_NewString(context->content);
            }
        }

        StreamClientChannel_Delete(client);
        HttpInstanceHandlerContext_Delete(context);
    } while (false);

    return object;
}