/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IotLauncher.c
 *
 * @remark
 *
 */

#include "IotLauncher.h"
#include <tiny_malloc.h>
#include <tiny_log.h>

#define TAG     "IotLauncher"

static void _OnRuntimeDelete (void * data, void *ctx)
{
    IotRuntime * runtime = (IotRuntime *) data;
    IotRuntime_Delete(runtime);
}

TINY_LOR
IotLauncher *IotLauncher_New(Product *thing, BootstrapLoopHook hook, void *ctx)
{
    IotLauncher *thiz = NULL;

    do
    {
        thiz = (IotLauncher *) tiny_malloc(sizeof(IotLauncher));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED.");
            break;
        }

        if (RET_FAILED(IotLauncher_Construct(thiz, thing, hook, ctx)))
        {
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
IotLauncher * IotLauncher_NewRuntime(Product *thing, IotRuntime *runtime, Channel *executor, BootstrapLoopHook hook, void *ctx)
{
    IotLauncher *thiz = IotLauncher_New(thing, hook, ctx);

    do
    {
        if (thiz == NULL)
        {
            break;
        }

        if (executor != NULL)
        {
            if (RET_FAILED(Bootstrap_AddChannel(&thiz->bootstrap, executor)))
            {
                executor->_close(executor);
                IotRuntime_Delete(runtime);
                IotLauncher_Delete(thiz);
                thiz = NULL;
                break;
            }
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, runtime)))
        {
            IotRuntime_Delete(runtime);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
IotLauncher * IotLauncher_NewRuntime2(Product *thing, IotRuntime *r1, IotRuntime *r2, Channel *executor, BootstrapLoopHook hook, void *ctx)
{
    IotLauncher *thiz = IotLauncher_New(thing, hook, ctx);

    do
    {
        if (thiz == NULL)
        {
            break;
        }

        if (executor != NULL)
        {
            if (RET_FAILED(Bootstrap_AddChannel(&thiz->bootstrap, executor)))
            {
                executor->_close(executor);
                IotRuntime_Delete(r1);
                IotRuntime_Delete(r2);
                IotLauncher_Delete(thiz);
                thiz = NULL;
                break;
            }
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, r1)))
        {
            IotRuntime_Delete(r1);
            IotRuntime_Delete(r2);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, r2)))
        {
            IotRuntime_Delete(r2);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
IotLauncher * IotLauncher_NewRuntime3(Product *thing, IotRuntime *r1, IotRuntime *r2, IotRuntime *r3, Channel *executor, BootstrapLoopHook hook, void *ctx)
{
    IotLauncher *thiz = IotLauncher_New(thing, hook, ctx);

    do
    {
        if (thiz == NULL)
        {
            break;
        }

        if (executor != NULL)
        {
            if (RET_FAILED(Bootstrap_AddChannel(&thiz->bootstrap, executor)))
            {
                executor->_close(executor);
                IotRuntime_Delete(r1);
                IotRuntime_Delete(r2);
                IotRuntime_Delete(r3);
                IotLauncher_Delete(thiz);
                thiz = NULL;
                break;
            }
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, r1)))
        {
            IotRuntime_Delete(r1);
            IotRuntime_Delete(r2);
            IotRuntime_Delete(r3);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, r2)))
        {
            IotRuntime_Delete(r2);
            IotRuntime_Delete(r3);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(IotLauncher_AddRuntime(thiz, r3)))
        {
            IotRuntime_Delete(r3);
            IotLauncher_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void IotLauncher_Delete(IotLauncher *thiz)
{
    RETURN_IF_FAIL(thiz);

    IotLauncher_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet IotLauncher_Construct(IotLauncher *thiz, Product *thing, BootstrapLoopHook hook, void *ctx)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(IotLauncher));
        thiz->started = false;
        thiz->thing = thing;

        ret = Bootstrap_Construct(&thiz->bootstrap, hook, ctx);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = TinyList_Construct(&thiz->runtimes, _OnRuntimeDelete, NULL);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
void IotLauncher_Dispose(IotLauncher *thiz)
{
    RETURN_IF_FAIL(thiz);

    Bootstrap_Dispose(&thiz->bootstrap);
    TinyList_Dispose(&thiz->runtimes);
    memset(thiz, 0, sizeof(IotLauncher));
}

TINY_LOR
TinyRet IotLauncher_AddRuntime(IotLauncher *thiz, IotRuntime *runtime)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(runtime, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    return TinyList_AddTail(&thiz->runtimes, runtime);
}

TINY_LOR
TinyRet IotLauncher_Stop(IotLauncher *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (! thiz->started)
    {
        return TINY_RET_E_STOPPED;
    }

    Bootstrap_Shutdown(&thiz->bootstrap);

    for (uint32_t i = 0; i < thiz->runtimes.size; ++i)
    {
        IotRuntime * runtime = (IotRuntime *) TinyList_GetAt(&thiz->runtimes, i);
        runtime->Stop(runtime);
        runtime->Destroy(runtime);
    }

    thiz->started = false;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet IotLauncher_Run(IotLauncher *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        if (thiz->started)
        {
            ret = TINY_RET_E_STARTED;
            break;
        }

        if (!Product_CheckHandler(thiz->thing))
        {
            ret = TINY_RET_E_NOT_IMPLEMENTED;
            break;
        }

        for (uint32_t  i = 0; i < thiz->thing->children.size; ++i)
        {
            Product *child = (Product *) TinyList_GetAt(&thiz->thing->children, i);
            if (!Product_CheckHandler(child))
            {
                ret = TINY_RET_E_NOT_IMPLEMENTED;
                break;
            }
        }

        if (RET_FAILED(ret))
        {
            break;
        }

        thiz->started = true;

        for (uint32_t i = 0; i < thiz->runtimes.size; ++i)
        {
            IotRuntime * runtime = (IotRuntime *) TinyList_GetAt(&thiz->runtimes, i);
            runtime->Initialize(runtime);

            ret = runtime->Run(runtime, &thiz->bootstrap, thiz->thing);
            if (RET_FAILED(ret))
            {
                LOG_D(TAG, "Runtime.Run failed");
                break;
            }
        }

        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Start Runtime failed");
            break;
        }

        ret = Bootstrap_Sync(&thiz->bootstrap);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Bootstrap_Sync failed");
            break;
        }
    } while (false);

    return ret;
}