/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceHostConfig.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_HOST_CONFIG_H__
#define __DEVICE_HOST_CONFIG_H__

#include "tiny_base.h"
#include "api/iot_api.h"
#include <constraint/typedef_constraint.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


typedef struct _DeviceHostConfig
{
    char                id[DEVICE_ID_LENGTH + 1];
    char                key[DEVICE_KEY_LENGTH + 1];
    char                model[DEVICE_MODEL_LENGTH + 1];
    char                vendor[DEVICE_VENDOR_LENGTH + 1];
} DeviceHostConfig;

typedef void (* DeviceHostConfigurationInitializer)(DeviceHostConfig *thiz, void *ctx);

//IOT_API DeviceHostConfig * DeviceHostConfig_New(void);
//IOT_API void DeviceHostConfig_Delete(DeviceHostConfig *thiz);

IOT_API
TINY_LOR
TinyRet DeviceHostConfig_Construct(DeviceHostConfig *thiz);

IOT_API
TINY_LOR
void DeviceHostConfig_Dispose(DeviceHostConfig *thiz);

IOT_API
TINY_LOR
void DeviceHostConfig_Initialize(DeviceHostConfig *thiz, DeviceHostConfigurationInitializer initializer, void *ctx);

IOT_API
TINY_LOR
void DeviceHostConfig_Copy(DeviceHostConfig *dst, DeviceHostConfig *src);

TINY_LOR
void DeviceHostConfig_SetId(DeviceHostConfig *thiz, const char *id);

IOT_API
TINY_LOR
void DeviceHostConfig_SetKey(DeviceHostConfig *thiz, const char *key);

IOT_API
TINY_LOR
void DeviceHostConfig_SetModel(DeviceHostConfig *thiz, const char *model);

IOT_API
TINY_LOR
void DeviceHostConfig_SetVendor(DeviceHostConfig *thiz, const char *vendor);


TINY_END_DECLS

#endif /* __DEVICE_HOST_CONFIG_H__ */
