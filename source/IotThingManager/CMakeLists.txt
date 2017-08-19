#-----------------------------------------------------------------------------
#
# IotThingManager
#
#-----------------------------------------------------------------------------

SET(Thing_Header
        thing/thing_api.h
        thing/ThingRuntime.h
        thing/ThingManager.h
    )

SET(Thing_Source
        thing/ThingManager.c
        thing/ThingRuntime.c
    )

SET(SRC
        ${Thing_Header}
        ${Thing_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_thing_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_thing_static PROPERTIES OUTPUT_NAME "iot_thing_static")
SET_TARGET_PROPERTIES(iot_thing_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# shared library
#----------------------------------------------------------------------------
#ADD_LIBRARY(iot_thing_shared SHARED ${SRC})
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES OUTPUT_NAME "iot_thing")
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES LINKER_LANGUAGE C)
#TARGET_LINK_LIBRARIES(iot_thing_shared tiny_shared iot_typedef_shared ${OS_LIB})
