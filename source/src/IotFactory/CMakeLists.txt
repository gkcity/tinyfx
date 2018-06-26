#-----------------------------------------------------------------------------
#
# IotFactory
#
#-----------------------------------------------------------------------------

SET(IotFactory_Header
        DeviceFactory.h
        )

SET(IotFactory_Source
        DeviceFactory.c
        )

SOURCE_GROUP(IotFactory\\headers        FILES     ${IotFactory_Header})
SOURCE_GROUP(IotFactory\\sources        FILES     ${IotFactory_Source})

SET(SRC
        ${IotFactory_Header}
        ${IotFactory_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_factory_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_factory_static PROPERTIES OUTPUT_NAME "iot_factory_static")
SET_TARGET_PROPERTIES(iot_factory_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# example
#----------------------------------------------------------------------------
ADD_SUBDIRECTORY(example)