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


typedef struct _AccessoryConfig
{
    uint16_t            aid;                            // accessory id
    char                pin[DEVICE_PIN_LENGTH + 1];     // pin code
    char                name[DEVICE_NAME_LENGTH + 1];   // name
    char                model[DEVICE_MODEL_LENGTH + 1]; // md

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
     * 2.   Bridge
     * 3.   Fan
     * 4.   Garage
     * 5.   Lightbulb
     * 6.   Door Lock
     * 7.   Outlet
     * 8.   Switch
     * 9.   Thermostat
     * 10.  Sensor
     * 11.  Security System
     * 12.  Door
     * 13.  Window
     * 14.  Window Covering
     * 15.  Programmable Switch
     * 16.  Range Extender
     * 17+  Reserved
     */
    uint32_t            categoryIdentifier;         // ci

    /**
     * Feature flags.
     * Mask         Bit     Description
     * -------------------------------------------------------------------------------------
     * 0x01         1       Supports HAP Pairing. This flag is required for all accessories.
     * 0x02 - 0x80  2-8     Reserved.
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
    uint32_t            protocolVersion;
} AccessoryConfig;


TINY_END_DECLS

#endif /* __ACCESSORY_CONFIG_H__ */