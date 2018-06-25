#-----------------------------------------------------------------------------
#
# IotExecute
#
#-----------------------------------------------------------------------------

SET(IotExecute_Header
        IotExcute.h
        )

SET(IotExecute_Source
        IotExcute.c
        )

SOURCE_GROUP(IotExecute\\headers        FILES     ${IotExecute_Header})
SOURCE_GROUP(IotExecute\\sources        FILES     ${IotExecute_Source})

SET(SRC
        ${IotExecute_Header}
        ${IotExecute_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_operation_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_operation_static PROPERTIES OUTPUT_NAME "iot_operation_static")
SET_TARGET_PROPERTIES(iot_operation_static PROPERTIES LINKER_LANGUAGE C)