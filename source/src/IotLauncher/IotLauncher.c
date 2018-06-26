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

TINY_LOR
IotLauncher *IotLauncher_New(void)
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

        if (RET_FAILED(IotLauncher_Construct(thiz)))
        {
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
TinyRet IotLauncher_Construct(IotLauncher *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(IotLauncher));
        thiz->started = false;

        ret = Bootstrap_Construct(&thiz->bootstrap);
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

    IotRuntime_Copy(&thiz->runtime, runtime);

    return TINY_RET_OK;
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

    thiz->runtime.Stop(&thiz->runtime);
    thiz->runtime.Destroy(&thiz->runtime);
    thiz->started = false;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet IotLauncher_Run(IotLauncher *thiz, Device *device)
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

        if (! Device_CheckHandler(device))
        {
            ret = TINY_RET_E_NOT_IMPLEMENTED;
            break;
        }

        for (uint32_t  i = 0; i < device->children.size; ++i)
        {
            Device *child = (Device *) TinyList_GetAt(&device->children, i);
            if (! Device_CheckHandler(child))
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
        thiz->runtime.Initialize(&thiz->runtime);

        ret = thiz->runtime.Run(&thiz->runtime, &thiz->bootstrap, device);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Runtime.Run failed");
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