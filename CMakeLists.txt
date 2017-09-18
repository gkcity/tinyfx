CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TinyFx C)

SET(PROJ_NAME "TinyFx")

#---------------------------------------------------------------------------------------
#
# include dir
#
#---------------------------------------------------------------------------------------
SET(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/source/src)
SET(TINY_ROOT ${PROJECT_SOURCE_DIR}/../tiny)

INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotTypedef)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotDeviceManager)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotInstance)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/TinyBase)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/TinyPortable)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/TinyContainer)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/TinyLog)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/TinyStringUtil)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/Netty)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/Json)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/HttpClient)
INCLUDE_DIRECTORIES(${TINY_ROOT}/source/src/StringArray)

#---------------------------------------------------------------------------------------
#
# link dir
#
#---------------------------------------------------------------------------------------
LINK_DIRECTORIES(${TINY_ROOT}/target)

#-------------------------------------------------------------------------------------
# output dir
#-------------------------------------------------------------------------------------
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)
MESSAGE(STATUS "executable output:  ${EXECUTABLE_OUTPUT_PATH}")
MESSAGE(STATUS "library output: ${LIBRARY_OUTPUT_PATH}")

#-------------------------------------------------------------------------------------
#
# Source
#
#-------------------------------------------------------------------------------------

#-----------------------
# IotTypedef
#-----------------------

SET(IotTypedef_Header
        ${SOURCE_ROOT}/IotTypedef/constraint/typedef_constraint.h
        ${SOURCE_ROOT}/IotTypedef/data/Data.h
        ${SOURCE_ROOT}/IotTypedef/data/DataType.h
        ${SOURCE_ROOT}/IotTypedef/data/DataValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/BoolValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/DataBlobValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/FloatValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/IntValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/StringValue.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Tlv8Value.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Tlv8.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint8Value.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint16Value.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint32Value.h
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint64Value.h
        ${SOURCE_ROOT}/IotTypedef/device/DeviceHostConfig.h
        ${SOURCE_ROOT}/IotTypedef/device/DeviceHost.h
        ${SOURCE_ROOT}/IotTypedef/device/Device.h
        ${SOURCE_ROOT}/IotTypedef/device/Service.h
        ${SOURCE_ROOT}/IotTypedef/device/Action.h
        ${SOURCE_ROOT}/IotTypedef/device/Property.h
        ${SOURCE_ROOT}/IotTypedef/error/IotError.h
        ${SOURCE_ROOT}/IotTypedef/controlled/PropertyOnControl.h
        ${SOURCE_ROOT}/IotTypedef/controlled/PropertyChangedListener.h
        ${SOURCE_ROOT}/IotTypedef/controlled/DeviceIdentifyListener.h
        ${SOURCE_ROOT}/IotTypedef/controlled/PropertyChangedObserver.h
        ${SOURCE_ROOT}/IotTypedef/urn/Urn.h
        ${SOURCE_ROOT}/IotTypedef/urn/UrnType.h
        ${SOURCE_ROOT}/IotTypedef/unit/Unit.h
        ${SOURCE_ROOT}/IotTypedef/access/AccessType.h
        ${SOURCE_ROOT}/IotTypedef/api/iot_api.h
        )

SET(IotTypedef_Source
        ${SOURCE_ROOT}/IotTypedef/data/Data.c
        ${SOURCE_ROOT}/IotTypedef/data/DataType.c
        ${SOURCE_ROOT}/IotTypedef/data/value/BoolValue.c
        ${SOURCE_ROOT}/IotTypedef/data/value/DataBlobValue.c
        ${SOURCE_ROOT}/IotTypedef/data/value/FloatValue.c
        ${SOURCE_ROOT}/IotTypedef/data/value/IntValue.c
        ${SOURCE_ROOT}/IotTypedef/data/value/StringValue.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Tlv8Value.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Tlv8.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint8Value.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint16Value.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint32Value.c
        ${SOURCE_ROOT}/IotTypedef/data/value/Uint64Value.c
        ${SOURCE_ROOT}/IotTypedef/device/DeviceHostConfig.c
        ${SOURCE_ROOT}/IotTypedef/device/DeviceHost.c
        ${SOURCE_ROOT}/IotTypedef/device/Device.c
        ${SOURCE_ROOT}/IotTypedef/device/Service.c
        ${SOURCE_ROOT}/IotTypedef/device/Action.c
        ${SOURCE_ROOT}/IotTypedef/device/Property.c
        ${SOURCE_ROOT}/IotTypedef/controlled/PropertyChangedObserver.c
        ${SOURCE_ROOT}/IotTypedef/access/AccessType.c
        ${SOURCE_ROOT}/IotTypedef/urn/Urn.c
        ${SOURCE_ROOT}/IotTypedef/urn/UrnType.c
        )

#-----------------------
# IotDeviceManager
#-----------------------

SET(IotDeviceManager_Header
        ${SOURCE_ROOT}/IotDeviceManager/DeviceRuntime.h
        ${SOURCE_ROOT}/IotDeviceManager/DeviceManager.h
        )

SET(IotDeviceManager_Source
        ${SOURCE_ROOT}/IotDeviceManager/DeviceManager.c
        ${SOURCE_ROOT}/IotDeviceManager/DeviceRuntime.c
        )

#-----------------------
# IotInstance
#-----------------------

SET(IotInstance_Header
        ${SOURCE_ROOT}/IotInstance/DeviceInstance.h
        )

SET(IotInstance_Source
        ${SOURCE_ROOT}/IotInstance/DeviceInstance.c
        )

SOURCE_GROUP(IotTypedef\\headers             FILES     ${IotTypedef_Header})
SOURCE_GROUP(IotTypedef\\sources             FILES     ${IotTypedef_Source})
SOURCE_GROUP(IotDeviceManager\\headers       FILES     ${IotDeviceManager_Header})
SOURCE_GROUP(IotDeviceManager\\sources       FILES     ${IotDeviceManager_Source})
SOURCE_GROUP(IotInstance\\headers            FILES     ${IotInstance_Header})
SOURCE_GROUP(IotInstance\\sources            FILES     ${IotInstance_Source})

SET(SRC
        ${IotTypedef_Header}
        ${IotTypedef_Source}
        ${IotDeviceManager_Header}
        ${IotDeviceManager_Source}
        ${IotInstance_Header}
        ${IotInstance_Source}
   )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(tinyfx_static STATIC ${SRC})
SET_TARGET_PROPERTIES(tinyfx_static PROPERTIES OUTPUT_NAME "tinyfx_static")
SET_TARGET_PROPERTIES(tinyfx_static PROPERTIES LINKER_LANGUAGE C)

ADD_LIBRARY(tinyfx SHARED ${SRC})
SET_TARGET_PROPERTIES(tinyfx PROPERTIES OUTPUT_NAME "tinyfx")
SET_TARGET_PROPERTIES(tinyfx PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(tinyfx ${DEPENDENCE_LIB})
