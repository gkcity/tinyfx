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

#include "DeviceHostConfig.h"
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
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(DeviceHostConfig));
    } while (0);

    return ret;
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
        strncpy(dst->ip, src->ip, TINY_IP_LEN);
        strncpy(dst->pin, src->pin, DEVICE_PIN_LENGTH);
        strncpy(dst->id, src->id, DEVICE_ID_LENGTH);
        strncpy(dst->name, src->name, DEVICE_NAME_LENGTH);
        strncpy(dst->model, src->model, DEVICE_MODEL_LENGTH);
        dst->port = src->port;
        dst->configurationNumber = src->configurationNumber;
        dst->categoryIdentifier = src->categoryIdentifier;
        dst->featureFlags = src->featureFlags;
        dst->stateNumber = src->stateNumber;
        dst->statusFlags = src->statusFlags;
        dst->protocolVersion = src->protocolVersion;
        dst->precomputed.valid = src->precomputed.valid;

        if (src->precomputed.valid)
        {
            memcpy(dst->precomputed.s, src->precomputed.s, SRP_salt_LEN);
            memcpy(dst->precomputed.v, src->precomputed.v, SRP_v_LEN);
            memcpy(dst->precomputed.b, src->precomputed.b, SRP_b_LEN);
            memcpy(dst->precomputed.B, src->precomputed.B, SRP_B_LEN);
        }
    }
}

TINY_LOR
void DeviceHostConfig_SetIp(DeviceHostConfig *thiz, const char *ip)
{
    printf("DeviceHostConfig_SetIp: %s\n", ip);
    strncpy(thiz->ip, ip, TINY_IP_LEN);
}

TINY_LOR
void DeviceHostConfig_SetIpByInt(DeviceHostConfig *thiz, uint32_t ip)
{
    char value[TINY_IP_LEN];
    uint8_t a = (uint8_t)(ip & 0xff);
    uint8_t b = (uint8_t)(ip >> 8 & 0xff);
    uint8_t c = (uint8_t)(ip >> 16 & 0xff);
    uint8_t d = (uint8_t)(ip >> 24 & 0xff);

    memset(value, 0, TINY_IP_LEN);
    tiny_snprintf(value, TINY_IP_LEN, "%d.%d.%d.%d", a, b, c, d);
    DeviceHostConfig_SetIp(thiz, value);
}

TINY_LOR
void DeviceHostConfig_SetPort(DeviceHostConfig *thiz, uint16_t port)
{
    thiz->port = port;
}

TINY_LOR
void DeviceHostConfig_SetName(DeviceHostConfig *thiz, const char *name)
{
    strncpy(thiz->name, name, DEVICE_NAME_LENGTH);
}

TINY_LOR
void DeviceHostConfig_SetId(DeviceHostConfig *thiz, const char *id)
{
    printf("DeviceHostConfig_SetId: %s\n", id);
    strncpy(thiz->id, id, DEVICE_ID_LENGTH);
}

TINY_LOR
void DeviceHostConfig_SetIdByInt(DeviceHostConfig *thiz, const uint8_t *id, uint32_t len)
{
    char value[DEVICE_ID_LENGTH];

    if (len < 6)
    {
        return;
    }

    memset(value, 0, DEVICE_ID_LENGTH);
    tiny_snprintf(value, TINY_IP_LEN, "%02x:%02x:%02x:%02x:%02x:%02x", id[0], id[1], id[2], id[3], id[4], id[5]);
    DeviceHostConfig_SetId(thiz, value);
}

TINY_LOR
void DeviceHostConfig_SetModelName(DeviceHostConfig *thiz, const char *model)
{
    strncpy(thiz->model, model, DEVICE_MODEL_LENGTH);
}

TINY_LOR
void DeviceHostConfig_SetConfigurationNumber(DeviceHostConfig *thiz, uint32_t value)
{
    thiz->configurationNumber = value;
}

TINY_LOR
void DeviceHostConfig_SetCurrentStateNumber(DeviceHostConfig *thiz, uint32_t value)
{
    thiz->stateNumber = value;
}

TINY_LOR
void DeviceHostConfig_SetFeatureFlags(DeviceHostConfig *thiz, uint32_t value)
{
    thiz->featureFlags = value;
}

TINY_LOR
void DeviceHostConfig_SetCategoryIdentifier(DeviceHostConfig *thiz, uint32_t value)
{
    thiz->categoryIdentifier = value;
}

TINY_LOR
void DeviceHostConfig_SetPinCode(DeviceHostConfig *thiz, const char *pin, SRPPrecomputed *precomputed)
{
    strncpy(thiz->pin, pin, DEVICE_PIN_LENGTH);

    if (precomputed != NULL)
    {
        thiz->precomputed.valid = true;
        memcpy(thiz->precomputed.s, precomputed->s, SRP_salt_LEN);
        memcpy(thiz->precomputed.v, precomputed->v, SRP_v_LEN);
        memcpy(thiz->precomputed.b, precomputed->b, SRP_b_LEN);
        memcpy(thiz->precomputed.B, precomputed->B, SRP_B_LEN);
    }
}