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
    char                        did[DEVICE_ID_LENGTH + 1];
    char                        serialNumber[SERIAL_NUMBER_LENGTH + 1];
    uint16_t                    productId;
    uint16_t                    productVersion;
    char                        ltsk[DEVICE_LTSK_BASE64_LENGTH + 1];
    char                        ltpk[DEVICE_LTPK_BASE64_LENGTH + 1];
    char                        ip[TINY_IP_LEN];
    uint16_t                    port;
    AccessoryConfig             accessoryConfig;
} ProductConfig;


TINY_END_DECLS

#endif /* __PRODUCT_CONFIG_H__ */