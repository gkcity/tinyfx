/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ThingManager.c
 *
 * @remark
 *
 */

#include "ThingManager.h"
#include <tiny_malloc.h>
#include <tiny_log.h>

#define TAG     "ThingManager"

//TINY_LOR
//ThingManager *ThingManager_New(void)
//{
//    ThingManager *thiz = NULL;
//
//    do
//    {
//        thiz = (ThingManager *) tiny_malloc(sizeof(ThingManager));
//        if (thiz == NULL)
//        {
//            LOG_D(TAG, "tiny_malloc FAILED.");
//            break;
//        }
//
//        if (RET_FAILED(ThingManager_Construct(thiz)))
//        {
//            ThingManager_Delete(thiz);
//            thiz = NULL;
//            break;
//        }
//    } while (false);
//
//    return thiz;
//}
//
//TINY_LOR
//void ThingManager_Delete(ThingManager *thiz)
//{
//    RETURN_IF_FAIL(thiz);
//
//    ThingManager_Dispose(thiz);
//    tiny_free(thiz);
//}

TINY_LOR
TinyRet ThingManager_Construct(ThingManager *thiz)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ThingManager));
    thiz->started = false;

    return ret;
}

TINY_LOR
void ThingManager_Dispose(ThingManager *thiz)
{
    RETURN_IF_FAIL(thiz);

    memset(thiz, 0, sizeof(ThingManager));
}

TINY_LOR
TinyRet ThingManager_SetRuntimeImpl(ThingManager *thiz, ThingRuntime *impl)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(impl, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    ThingRuntime_Copy(&thiz->runtime, impl);

    return TINY_RET_OK;
}

TINY_LOR
TinyRet ThingManager_Stop(ThingManager *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (! thiz->started)
    {
        return TINY_RET_E_STOPPED;
    }

    thiz->runtime.Stop(&thiz->runtime);
    thiz->runtime.Destroy(&thiz->runtime);
    thiz->started = false;

    return TINY_RET_OK;
}

TINY_LOR
TinyRet ThingManager_Run(ThingManager *thiz, Device *device)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    if (thiz->started)
    {
        return TINY_RET_E_STARTED;
    }

    thiz->started = true;
    thiz->runtime.Initialize(&thiz->runtime);

    return thiz->runtime.Run(&thiz->runtime, device);
}