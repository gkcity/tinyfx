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
# data
#-----------------------
SET(Data_Header
        data/Data.h
        data/DataType.h
        data/DataValue.h
        data/value/BoolValue.h
        data/value/DataBlobValue.h
        data/value/FloatValue.h
        data/value/IntValue.h
        data/value/StringValue.h
        data/value/Tlv8Value.h
        data/value/Tlv8.h
        data/value/Uint8Value.h
        data/value/Uint16Value.h
        data/value/Uint32Value.h
        data/value/Uint64Value.h
    )

SET(Data_Source
        data/Data.c
        data/DataType.c
        data/value/BoolValue.c
        data/value/DataBlobValue.c
        data/value/FloatValue.c
        data/value/IntValue.c
        data/value/StringValue.c
        data/value/Tlv8Value.c
        data/value/Tlv8.c
        data/value/Uint8Value.c
        data/value/Uint16Value.c
        data/value/Uint32Value.c
        data/value/Uint64Value.c
    )

#-----------------------
# device
#-----------------------
SET(Device_Header
        device/Device.h
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
        device/Device.c
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
# controlled
#-----------------------
SET(Controlled_Header
        controlled/DeviceControllable.h
        device/handler/PropertyOnControl.h
        device/handler/ActionOnInvoke.h
        device/handler/EventOnOccurred.h
        device/handler/DeviceIdentifyListener.h
    )

SET(Controlled_Source
        controlled/DeviceControllable.c
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
        operation/ActionOperation.c
        operation/EventOperation.c
        operation/PropertyOperation.c
        operation/PropertyOperations.h
    )

#----------------------------------------------------------------------------
# source
#----------------------------------------------------------------------------
SET(SRC
        ${api_Header}
        ${Constant_Header}
        ${Error_Header}
        ${Data_Header}
        ${Data_Source}
        ${Device_Header}
        ${Device_Source}
        ${Controlled_Header}
        ${Controlled_Source}
        ${Urn_Header}
        ${Urn_Source}
        ${Unit_Header}
        ${operation_Header}
        ${operation_Source}
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

#----------------------------------------------------------------------------
# test
#----------------------------------------------------------------------------
ADD_SUBDIRECTORY(test)
