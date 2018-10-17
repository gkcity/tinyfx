CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TinyFX C)

SET(PROJ_NAME "TinyFX")

#---------------------------------------------------------------------------------------
#
# include dir
#
#---------------------------------------------------------------------------------------
SET(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/source/src)
SET(TINY_ROOT ${PROJECT_SOURCE_DIR}/../tiny)

INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotTypedef)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotFactory)
INCLUDE_DIRECTORIES(${SOURCE_ROOT}/IotLauncher)

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

SET(IotTypedef_Header
        ${SOURCE_ROOT}/IotTypedef/constant/iot_constant.h
        ${SOURCE_ROOT}/IotTypedef/device/config/DeviceConfig.h
        ${SOURCE_ROOT}/IotTypedef/device/config/AccessoryConfig.h
        ${SOURCE_ROOT}/IotTypedef/device/Device.h
        ${SOURCE_ROOT}/IotTypedef/device/Service.h
        ${SOURCE_ROOT}/IotTypedef/device/Action.h
        ${SOURCE_ROOT}/IotTypedef/device/Event.h
        ${SOURCE_ROOT}/IotTypedef/device/Property.h
        ${SOURCE_ROOT}/IotTypedef/device/Argument.h
        ${SOURCE_ROOT}/IotTypedef/device/access/Access.h
        ${SOURCE_ROOT}/IotTypedef/device/format/Format.h
        ${SOURCE_ROOT}/IotTypedef/device/constraint/ValueList.h
        ${SOURCE_ROOT}/IotTypedef/device/constraint/ValueRange.h
        ${SOURCE_ROOT}/IotTypedef/device/handler/DeviceIdentifyListener.h
        ${SOURCE_ROOT}/IotTypedef/device/handler/PropertyHandler.h
        ${SOURCE_ROOT}/IotTypedef/device/handler/ActionHandler.h
        ${SOURCE_ROOT}/IotTypedef/operation/AID.h
        ${SOURCE_ROOT}/IotTypedef/operation/EID.h
        ${SOURCE_ROOT}/IotTypedef/operation/PID.h
        ${SOURCE_ROOT}/IotTypedef/operation/ActionOperation.h
        ${SOURCE_ROOT}/IotTypedef/operation/EventOperation.h
        ${SOURCE_ROOT}/IotTypedef/operation/PropertyOperation.h
        ${SOURCE_ROOT}/IotTypedef/operation/PropertyOperations.h
        ${SOURCE_ROOT}/IotTypedef/status/IotStatus.h
        ${SOURCE_ROOT}/IotTypedef/urn/Urn.h
        ${SOURCE_ROOT}/IotTypedef/urn/UrnType.h
        ${SOURCE_ROOT}/IotTypedef/unit/Unit.h
        ${SOURCE_ROOT}/IotTypedef/api/iot_api.h
        )

SET(IotTypedef_Source
        ${SOURCE_ROOT}/IotTypedef/device/Device.c
        ${SOURCE_ROOT}/IotTypedef/device/Service.c
        ${SOURCE_ROOT}/IotTypedef/device/Action.c
        ${SOURCE_ROOT}/IotTypedef/device/Event.c
        ${SOURCE_ROOT}/IotTypedef/device/Property.c
        ${SOURCE_ROOT}/IotTypedef/device/Argument.c
        ${SOURCE_ROOT}/IotTypedef/device/access/Access.c
        ${SOURCE_ROOT}/IotTypedef/device/format/Format.c
        ${SOURCE_ROOT}/IotTypedef/device/constraint/ValueList.c
        ${SOURCE_ROOT}/IotTypedef/device/constraint/ValueRange.c
        ${SOURCE_ROOT}/IotTypedef/operation/ActionOperation.c
        ${SOURCE_ROOT}/IotTypedef/operation/EventOperation.c
        ${SOURCE_ROOT}/IotTypedef/operation/PropertyOperation.c
        ${SOURCE_ROOT}/IotTypedef/operation/PropertyOperations.c
        ${SOURCE_ROOT}/IotTypedef/urn/Urn.c
        ${SOURCE_ROOT}/IotTypedef/urn/UrnType.c
        )

#-----------------------
# IotLauncher
#-----------------------

SET(IotLauncher_Header
        ${SOURCE_ROOT}/IotLauncher/IotLauncher.h
        ${SOURCE_ROOT}/IotLauncher/IotRuntime.h
        )

SET(IotLauncher_Source
        ${SOURCE_ROOT}/IotLauncher/IotLauncher.c
        ${SOURCE_ROOT}/IotLauncher/IotRuntime.c
        )

#-----------------------
# IotFactory
#-----------------------

SET(IotFactory_Header
        ${SOURCE_ROOT}/IotFactory/DeviceFactory.h
        )

SET(IotFactory_Source
        ${SOURCE_ROOT}/IotFactory/DeviceFactory.c
        )

SOURCE_GROUP(IotTypedef\\headers             FILES     ${IotTypedef_Header})
SOURCE_GROUP(IotTypedef\\sources             FILES     ${IotTypedef_Source})
SOURCE_GROUP(IotLauncher\\headers            FILES     ${IotLauncher_Header})
SOURCE_GROUP(IotLauncher\\sources            FILES     ${IotLauncher_Source})
SOURCE_GROUP(IotFactory\\headers             FILES     ${IotFactory_Header})
SOURCE_GROUP(IotFactory\\sources             FILES     ${IotFactory_Source})

SET(SRC
        ${IotTypedef_Header}
        ${IotTypedef_Source}
        ${IotLauncher_Header}
        ${IotLauncher_Source}
        ${IotFactory_Header}
        ${IotFactory_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
IF (EXPORT_STATIC_LIBRARY EQUAL 1)
ADD_LIBRARY(tinyfx_static STATIC ${SRC})
SET_TARGET_PROPERTIES(tinyfx_static PROPERTIES OUTPUT_NAME "tinyfx_static")
SET_TARGET_PROPERTIES(tinyfx_static PROPERTIES LINKER_LANGUAGE C)
ENDIF ()

#----------------------------------------------------------------------------
# shared library
#----------------------------------------------------------------------------
IF (EXPORT_SHARED_LIBRARY EQUAL 1)
ADD_LIBRARY(tinyfx SHARED ${SRC})
SET_TARGET_PROPERTIES(tinyfx PROPERTIES OUTPUT_NAME "tinyfx")
SET_TARGET_PROPERTIES(tinyfx PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(tinyfx ${DEPENDENCE_LIB})
ENDIF ()
