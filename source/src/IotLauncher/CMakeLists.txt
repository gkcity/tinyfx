#-----------------------------------------------------------------------------
#
# IotLauncher
#
#-----------------------------------------------------------------------------

SET(IotLauncher_Header
        IotRuntime.h
        IotLauncher.h
    )

SET(IotLauncher_Source
        IotLauncher.c
        IotRuntime.c
    )

SET(SRC
        ${IotLauncher_Header}
        ${IotLauncher_Source}
    )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(iot_launcher_static STATIC ${SRC})
SET_TARGET_PROPERTIES(iot_launcher_static PROPERTIES OUTPUT_NAME "iot_launcher_static")
SET_TARGET_PROPERTIES(iot_launcher_static PROPERTIES LINKER_LANGUAGE C)

#----------------------------------------------------------------------------
# shared library
#----------------------------------------------------------------------------
#ADD_LIBRARY(iot_thing_shared SHARED ${SRC})
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES OUTPUT_NAME "iot_thing")
#SET_TARGET_PROPERTIES(iot_thing_shared PROPERTIES LINKER_LANGUAGE C)
#TARGET_LINK_LIBRARIES(iot_thing_shared tiny_shared iot_typedef_shared ${OS_LIB})
