/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceHostConfig.c
 *
 * @remark
 *
 */

#include "DeviceConfig.h"
#include <tiny_malloc.h>
#include <tiny_snprintf.h>
#include "tiny_log.h"

#define TAG     "DeviceHostConfig"

//DeviceHostConfig * DeviceHostConfig_New(void)
//{
//    DeviceHostConfig *thiz = NULL;
//
//    do
//    {
//        thiz = (DeviceHostConfig *)tiny_malloc(sizeof(DeviceHostConfig));
//        if (thiz == NULL)
//        {
//            LOG_E(TAG, "OUT OF MEMORY");
//            break;
//        }
//
//        if (RET_FAILED(DeviceHostConfig_Construct(thiz)))
//        {
//            LOG_E(TAG, "DeviceHostConfig_Construct failed");
//            DeviceHostConfig_Delete(thiz);
//            thiz = NULL;
//            break;
//        }
//    } while (0);
//
//    return thiz;
//}

//void DeviceHostConfig_Delete(DeviceHostConfig *thiz)
//{
//    RETURN_IF_FAIL(thiz);
//
//    DeviceHostConfig_Dispose(thiz);
//    tiny_free(thiz);
//}

TINY_LOR
TinyRet DeviceHostConfig_Construct(DeviceHostConfig *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(DeviceHostConfig));

    return TINY_RET_OK;
}

TINY_LOR
void DeviceHostConfig_Dispose(DeviceHostConfig *thiz)
{
    RETURN_IF_FAIL(thiz);

    memset(thiz, 0, sizeof(DeviceHostConfig));
}

TINY_LOR
void DeviceHostConfig_Initialize(DeviceHostConfig *thiz, DeviceHostConfigurationInitializer initializer, void *ctx)
{
    initializer(thiz, ctx);
}

TINY_LOR
void DeviceHostConfig_Copy(DeviceHostConfig *dst, DeviceHostConfig *src)
{
    if (dst != src)
    {
        dst->id = src->id;
        strncpy(dst->key, src->key, DEVICE_KEY_LENGTH);
        strncpy(dst->model, src->model, DEVICE_MODEL_LENGTH);
        strncpy(dst->vendor, src->vendor, DEVICE_MODEL_LENGTH);
    }
}

TINY_LOR
void DeviceHostConfig_SetId(DeviceHostConfig *thiz, uint64_t id)
{
    thiz->id = id;
}

IOT_API
TINY_LOR
void DeviceHostConfig_SetKey(DeviceHostConfig *thiz, const char *key)
{
    strncpy(thiz->key, key, DEVICE_KEY_LENGTH);
}

IOT_API
TINY_LOR
void DeviceHostConfig_SetModel(DeviceHostConfig *thiz, const char *model)
{
    strncpy(thiz->model, model, DEVICE_MODEL_LENGTH);
}

IOT_API
TINY_LOR
void DeviceHostConfig_SetVendor(DeviceHostConfig *thiz, const char *vendor)
{
    strncpy(thiz->vendor, vendor, DEVICE_VENDOR_LENGTH);
}