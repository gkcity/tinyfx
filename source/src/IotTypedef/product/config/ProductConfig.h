/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ProductConfig.h
 *
 * @remark
 *
 */

#ifndef __PRODUCT_CONFIG_H__
#define __PRODUCT_CONFIG_H__

#include <tiny_base.h>
#include "AccessoryConfig.h"

TINY_BEGIN_DECLS


typedef struct _ProductConfig
{
    char                        did[IOT_DEVICE_ID_LENGTH + 1];
    char                        serialNumber[IOT_SERIAL_NUMBER_LENGTH + 1];
    uint16_t                    productId;
    uint16_t                    productVersion;
    char                        ltsk[IOT_DEVICE_LTSK_BASE64_LENGTH + 1];
    char                        ltpk[IOT_DEVICE_LTPK_BASE64_LENGTH + 1];
    char                        ip[TINY_IP_LEN];
    uint16_t                    port;
    AccessoryConfig             accessoryConfig;
} ProductConfig;


TINY_END_DECLS

#endif /* __PRODUCT_CONFIG_H__ */