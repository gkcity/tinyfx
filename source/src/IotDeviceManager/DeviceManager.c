/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceManager.c
 *
 * @remark
 *
 */

#include "DeviceManager.h"
#include <tiny_malloc.h>
#include <tiny_log.h>

#define TAG     "DeviceManager"

//TINY_LOR
//DeviceManager *DeviceManager_New(void)
//{
//    DeviceManager *thiz = NULL;
//
//    do
//    {
//        thiz = (DeviceManager *) tiny_malloc(sizeof(DeviceManager));
//        if (thiz == NULL)
//        {
//            LOG_D(TAG, "tiny_malloc FAILED.");
//            break;
//        }
//
//        if (RET_FAILED(DeviceManager_Construct(thiz)))
//        {
//            DeviceManager_Delete(thiz);
//            thiz = NULL;
//            break;
//        }
//    } while (false);
//
//    return thiz;
//}
//
//TINY_LOR
//void DeviceManager_Delete(DeviceManager *thiz)
//{
//    RETURN_IF_FAIL(thiz);
//
//    DeviceManager_Dispose(thiz);
//    tiny_free(thiz);
//}

TINY_LOR
TinyRet DeviceManager_Construct(DeviceManager *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(DeviceManager));
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
void DeviceManager_Dispose(DeviceManager *thiz)
{
    RETURN_IF_FAIL(thiz);

    Bootstrap_Dispose(&thiz->bootstrap);
    memset(thiz, 0, sizeof(DeviceManager));
}

TINY_LOR
TinyRet DeviceManager_AddRuntime(DeviceManager *thiz, DeviceRuntime *runtime)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(runtime, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    DeviceRuntime_Copy(&thiz->runtime, runtime);

    return TINY_RET_OK;
}

TINY_LOR
TinyRet DeviceManager_Stop(DeviceManager *thiz)
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
TinyRet DeviceManager_Run(DeviceManager *thiz, DeviceControllable *host)
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

        for (uint32_t  i = 0; i < host->devices.size; ++i)
        {
            Device *device = (Device *) TinyList_GetAt(&host->devices, i);
            if (! Device_CheckHandler(device))
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

        ret = thiz->runtime.Run(&thiz->runtime, &thiz->bootstrap, host);
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