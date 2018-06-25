/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceConfig.h
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


typedef struct _DeviceConfig
{
    uint64_t            id;
    char                key[DEVICE_KEY_LENGTH + 1];
    char                model[DEVICE_MODEL_LENGTH + 1];
    char                vendor[DEVICE_VENDOR_LENGTH + 1];
} DeviceConfig;

typedef void (* DeviceConfigurationInitializer)(DeviceConfig *thiz, void *ctx);

//IOT_API DeviceConfig * DeviceConfig_New(void);
//IOT_API void DeviceConfig_Delete(DeviceConfig *thiz);

IOT_API
TINY_LOR
TinyRet DeviceConfig_Construct(DeviceConfig *thiz);

IOT_API
TINY_LOR
void DeviceConfig_Dispose(DeviceConfig *thiz);

IOT_API
TINY_LOR
void DeviceConfig_Initialize(DeviceConfig *thiz, DeviceConfigurationInitializer initializer, void *ctx);

IOT_API
TINY_LOR
void DeviceConfig_Copy(DeviceConfig *dst, DeviceConfig *src);

TINY_LOR
void DeviceConfig_SetId(DeviceConfig *thiz, uint64_t id);

IOT_API
TINY_LOR
void DeviceConfig_SetKey(DeviceConfig *thiz, const char *key);

IOT_API
TINY_LOR
void DeviceConfig_SetModel(DeviceConfig *thiz, const char *model);

IOT_API
TINY_LOR
void DeviceConfig_SetVendor(DeviceConfig *thiz, const char *vendor);


TINY_END_DECLS

#endif /* __DEVICE_HOST_CONFIG_H__ */
