#-----------------------------------------------------------------------------
#
# IotDeviceManager
#
#-----------------------------------------------------------------------------

SET(DeviceManager_Header
        DeviceRuntime.h
        DeviceManager.h
    )

SET(DeviceManager_Source
        DeviceManager.c
        DeviceRuntime.c
    )

SET(SRC
        ${DeviceManager_Header}
        ${DeviceManager_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_device_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_device_static PROPERTIES OUTPUT_NAME "iot_device_static")
SET_TARGET_PROPERTIES(iot_device_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# shared library
#----------------------------------------------------------------------------
#ADD_LIBRARY(iot_thing_shared SHARED ${SRC})
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES OUTPUT_NAME "iot_thing")
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES LINKER_LANGUAGE C)
#TARGET_LINK_LIBRARIES(iot_thing_shared tiny_shared iot_typedef_shared ${OS_LIB})
