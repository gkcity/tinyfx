#-----------------------------------------------------------------------------
#
# IotInstance
#
#-----------------------------------------------------------------------------

SET(IotInstance_Header
        HttpInstance.h
        HttpInstanceHandler.h
        HttpInstanceHandlerContext.h
        )

SET(IotInstance_Source
        HttpInstance.c
        HttpInstanceHandler.c
        HttpInstanceHandlerContext.c
        )

SOURCE_GROUP(IotInstance\\headers        FILES     ${IotInstance_Header})
SOURCE_GROUP(IotInstance\\sources        FILES     ${IotInstance_Source})

SET(SRC
        ${IotInstance_Header}
        ${IotInstance_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_instance_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_instance_static PROPERTIES OUTPUT_NAME "iot_instance_static")
SET_TARGET_PROPERTIES(iot_instance_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# example
#----------------------------------------------------------------------------
ADD_SUBDIRECTORY(example)