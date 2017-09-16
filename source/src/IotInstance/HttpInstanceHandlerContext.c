/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpInstanceHandlerContext.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=454
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "HttpInstanceHandlerContext.h"

#define TAG     "HttpInstanceHandlerContext"

TINY_LOR
static TinyRet HttpInstanceHandlerContext_Construct(HttpInstanceHandlerContext *thiz, const char *ip, uint16_t port, const char *uri)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(uri, TINY_RET_E_ARG_NULL);

    do
    {
        uint32_t length = 0;

        memset(thiz, 0, sizeof(HttpInstanceHandlerContext));
        length = (uint32_t) (strlen(uri) + 1);

        strncpy(thiz->ip, ip, TINY_IP_LEN);
        thiz->port = port;
        thiz->uri = tiny_malloc(length);
        if (thiz->uri == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        memset(thiz->uri, 0, length);
        strncpy(thiz->uri, uri, length);
    } while (false);

    return ret;
}

TINY_LOR
static void HttpInstanceHandlerContext_Dispose(HttpInstanceHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->uri != NULL)
    {
        tiny_free(thiz->uri);
    }

    if (thiz->content != NULL)
    {
        tiny_free(thiz->content);
    }
}

TINY_LOR
HttpInstanceHandlerContext * HttpInstanceHandlerContext_New(const char *ip, uint16_t port, const char *uri)
{
    HttpInstanceHandlerContext *thiz = NULL;

    do
    {
        thiz = (HttpInstanceHandlerContext *)tiny_malloc(sizeof(HttpInstanceHandlerContext));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(HttpInstanceHandlerContext_Construct(thiz, ip, port, uri)))
        {
            HttpInstanceHandlerContext_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void HttpInstanceHandlerContext_Delete(HttpInstanceHandlerContext *thiz)
{
    RETURN_IF_FAIL(thiz);

    HttpInstanceHandlerContext_Dispose(thiz);
    tiny_free(thiz);
}