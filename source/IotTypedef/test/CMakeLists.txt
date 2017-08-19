#-----------------------------------------------------------------------------
#
# srp-test
#
#-----------------------------------------------------------------------------
ADD_EXECUTABLE(test_tlv8
        test_tlv8.c
    )

SET_TARGET_PROPERTIES(test_tlv8 PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(test_tlv8
        iot_typedef_static
        tiny_container_static
        tiny_log_static
        tiny_portable_static
        tiny_base_static
        ${OS_LIB})