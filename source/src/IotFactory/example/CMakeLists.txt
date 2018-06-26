#-----------------------------------------------------------------------------
#
# examples
#
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(example_device_instance example_device_instance.c)
SET_TARGET_PROPERTIES(example_device_instance PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(example_device_instance iot_instance_static iot_typedef_static ${DEPENDENCE_LIB})