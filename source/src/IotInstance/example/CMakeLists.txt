#-----------------------------------------------------------------------------
#
# examples
#
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(example_instance_homekit example_homekit.c)
SET_TARGET_PROPERTIES(example_instance_homekit PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(example_instance_homekit iot_instance_static iot_typedef_static ${DEPENDENCE_LIB})