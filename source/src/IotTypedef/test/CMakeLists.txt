#-----------------------------------------------------------------------------
#
# test
#
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(test_tlv8 test_tlv8.c)
SET_TARGET_PROPERTIES(test_tlv8 PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(test_tlv8 iot_typedef_static ${DEPENDENCE_LIB})

ADD_EXECUTABLE(test_tlv8_memory_leak test_tlv8_memory_leak.c)
SET_TARGET_PROPERTIES(test_tlv8_memory_leak PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(test_tlv8_memory_leak iot_typedef_static ${DEPENDENCE_LIB})
