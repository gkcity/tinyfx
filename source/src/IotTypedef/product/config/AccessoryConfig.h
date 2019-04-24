/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   AccessoryConfig.h
 *
 * @remark
 *
 */

#ifndef __ACCESSORY_CONFIG_H__
#define __ACCESSORY_CONFIG_H__

#include <tiny_base.h>
#include <constant/iot_constant.h>

TINY_BEGIN_DECLS


#define ACCESSORY_NAME_LENGTH              128
#define ACCESSORY_MODEL_LENGTH             128
#define ACCESSORY_SETUP_CODE_LENGTH        10   // 034-31-154
#define ACCESSORY_SETUP_ID_LENGTH          4

typedef struct _AccessoryConfig
{
//    /**
//     * accessory id
//     */
//    uint16_t            aid;

    char                name[ACCESSORY_NAME_LENGTH + 1];
    char                model[ACCESSORY_MODEL_LENGTH + 1];
    char                setupId[ACCESSORY_SETUP_ID_LENGTH + 1];
    char                setupCode[ACCESSORY_SETUP_CODE_LENGTH + 1];

    /**
     * Current configuration number. Required.
     * Updates only when an accessory, service, or characteristic is
     * added or removed on the accessory server.
     * This must have a range of 1 - 4294967295 and wrap to 1 when it overflows.
     * This value must persist across reboots, power cycles, etc.
     */
    uint32_t            configurationNumber;        // c#

    /**
     * Accessory Categories
     * 1.   Other
     * 2.   Bridges
     * 3.   Fans
     * 4.   Garage Door Openers *
     * 5.   Lighting
     * 6.   Locks *
     * 7.   Outlets
     * 8.   Switches
     * 9.   Thermostats
     * 10.  Sensors
     * 11.  Security System *
     * 12.  Doors
     * 13.  Windows *
     * 14.  Window Coverings
     * 15.  Programmable Switches
     * 16.  Reserved
     * 17.  IP Cameras *
     * 18.  Video Doorbells*
     * 19.  AirPurifiers
     * 20.  Heaters
     * 21.  Air Conditioners
     * 22.  Humidifiers
     * 23.  Dehumidifiers
     * 24.  Reserved
     * 25.  Reserved
     * 26.  Reserved
     * 27.  Reserved
     * 28.  Sprinklers
     * 29.  Faucets
     * 30.  Shower Systems
     * 30+  Reserved
     */
    uint32_t            categoryIdentifier;         // ci

    /**
     * Pairing Feature flags.
     * Mask         Bit     Description
     * -------------------------------------------------------------------------------------
     * 0x01         1       Supports Apple Authentication Coprocessor.
     * 0x02         2       Supports Software Authentication.
     * 0x04 - 0x80  3-8     Reserved.
     */
    uint32_t            featureFlags;               // ff

    /**
     * Current state number. Required.
     * This must have a value of "1".
     */
    uint32_t            stateNumber;                // s#

    /**
     * Status flags.
     * Mask         Bit     Description
     * -------------------------------------------------------------------------------------
     * 0x01         1       Accessory has not been paired with any controllers.
     * 0x02         2       Accessory has not been configured to join a Wi-Fi network.
     * 0x04         3       A problem has been detected on the accessory.
     * 0x08 - 0x80  4-8     Reserved.
     */
    uint32_t            statusFlags;                // sf

    /**
     * Protocol version string <major>.<minor>. Required if value is not "1.0"
     */
    uint32_t            protocolMajorVersion;
    uint32_t            protocolMinorVersion;
} AccessoryConfig;


TINY_END_DECLS

#endif /* __ACCESSORY_CONFIG_H__ */