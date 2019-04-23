#-----------------------------------------------------------------------------
#
# IotTypedef
#
#-----------------------------------------------------------------------------

#-----------------------
# constant
#-----------------------
SET(Constant_Header
        constant/iot_constant.h
    )

#-----------------------
# device
#-----------------------
SET(Device_Header
        thing/Thing.h
        thing/config/AccessoryCategoryIdentifier.h
        thing/config/AccessoryConfig.h
        thing/config/ThingConfig.h
        device/Service.h
        device/Action.h
        device/Event.h
        device/Property.h
        device/Argument.h
        device/access/Access.h
        device/format/Format.h
        device/constraint/ValueList.h
        device/constraint/ValueRange.h
    )

SET(Device_Source
        thing/Thing.c
        device/Service.c
        device/Action.c
        device/Event.c
        device/Property.c
        device/Argument.c
        device/access/Access.c
        device/format/Format.c
        device/constraint/ValueList.c
        device/constraint/ValueRange.c
    )

#-----------------------
# status
#-----------------------
SET(Error_Header
        status/IotError.h
        status/IotStatus.h
    )

#-----------------------
# urn
#-----------------------
SET(Urn_Header
        urn/Urn.h
        urn/UrnType.h
    )

SET(Urn_Source
        urn/Urn.c
        urn/UrnType.c
    )

#-----------------------
# unit
#-----------------------
SET(Unit_Header
        unit/Unit.h
    )

#-----------------------
# api
#-----------------------
SET(api_Header
        api/iot_api.h
    )

#-----------------------
# operation
#-----------------------
SET(operation_Header
        operation/AID.h
        operation/EID.h
        operation/PID.h
        operation/ActionOperation.h
        operation/EventOperation.h
        operation/PropertyOperation.h
        operation/PropertyOperations.h
    )

SET(operation_Source
        operation/PID.c
        operation/ActionOperation.c
        operation/EventOperation.c
        operation/PropertyOperation.c
        operation/PropertyOperations.h
    )

#-----------------------
# operator
#-----------------------
SET(operator_Header
        operator/DeviceOperator.h
        )

SET(operator_Source
        operator/DeviceOperator.c
        )

#----------------------------------------------------------------------------
# source
#----------------------------------------------------------------------------
SET(SRC
        ${api_Header}
        ${Constant_Header}
        ${Error_Header}
        ${Device_Header}
        ${Device_Source}
        ${Urn_Header}
        ${Urn_Source}
        ${Unit_Header}
        ${operation_Header}
        ${operation_Source}
        ${operator_Header}
        ${operator_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_typedef_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_typedef_static PROPERTIES OUTPUT_NAME "iot_typedef_static")
SET_TARGET_PROPERTIES(iot_typedef_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# shared library
#----------------------------------------------------------------------------
#ADD_LIBRARY(iot_typedef_shared SHARED ${SRC})
#SET_TARGET_PROPERTIES(iot_typedef_shared PROPERTIES OUTPUT_NAME "iot_typedef")
#SET_TARGET_PROPERTIES(iot_typedef_shared PROPERTIES LINKER_LANGUAGE C)
#TARGET_LINK_LIBRARIES(iot_typedef_shared tiny_shared ${OS_LIB})