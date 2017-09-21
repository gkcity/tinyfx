#-----------------------------------------------------------------------------
#
# IotOperation
#
#-----------------------------------------------------------------------------

SET(IotOperation_Header
        PropertySetter.h
        )

SET(IotOperation_Source
        PropertySetter.c
        )

SOURCE_GROUP(IotOperation\\headers        FILES     ${IotOperation_Header})
SOURCE_GROUP(IotOperation\\sources        FILES     ${IotOperation_Source})

SET(SRC
        ${IotOperation_Header}
        ${IotOperation_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_operation_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_operation_static PROPERTIES OUTPUT_NAME "iot_operation_static")
SET_TARGET_PROPERTIES(iot_operation_static PROPERTIES LINKER_LANGUAGE C)