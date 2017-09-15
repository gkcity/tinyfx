#-----------------------------------------------------------------------------
#
# IotTypedef
#
#-----------------------------------------------------------------------------

#-----------------------
# constraint
#-----------------------
SET(Constraint_Header
        constraint/typedef_constraint.h
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
        device/DeviceHost.h
        device/DeviceHostConfig.h
        device/Device.h
        device/Service.h
        device/Property.h
    )

SET(Device_Source
        device/DeviceHost.c
        device/DeviceHostConfig.c
        device/Device.c
        device/Service.c
        device/Property.c
    )

#-----------------------
# error
#-----------------------
SET(Error_Header
        error/IotError.h
    )

#-----------------------
# controlled
#-----------------------
SET(Controlled_Header
        controlled/PropertyOnControl.h
        controlled/PropertyChangedListener.h
        controlled/DeviceIdentifyListener.h
        controlled/PropertyChangedObserver.h
    )

SET(Controlled_Source
        controlled/PropertyChangedObserver.c
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
        )

#-----------------------
# unit
#-----------------------
SET(Unit_Header
        unit/Unit.h
        )

#-----------------------
# access
#-----------------------
SET(Access_Header
        access/AccessType.h
        )

#-----------------------
# api
#-----------------------
SET(Api_Header
        api/iot_api.h
    )

#----------------------------------------------------------------------------
# source
#----------------------------------------------------------------------------
SET(SRC
        ${Constraint_Header}
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
        ${Access_Header}
        ${Api_Header}
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
