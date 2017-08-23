/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   BoolValue.c
 *
 * @remark
 *
 */

#include "BoolValue.h"
#include <tiny_str_equal.h>
#include <tiny_log.h>

#define TAG     "BoolValue"

TINY_LOR
TinyRet BoolValue_Set(BoolValue *thiz, bool value)
{
    thiz->value = value;
    return TINY_RET_OK;
}

//TINY_LOR
//TinyRet BoolValue_Retrieve(BoolValue *thiz, const char *string)
//{
//    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
//    RETURN_VAL_IF_FAIL(string, TINY_RET_E_ARG_NULL);
//
//    if (STR_EQUAL("1", string) || str_equal("YES", string, true) || str_equal("TRUE", string, true))
//    {
//        thiz->value = true;
//        return TINY_RET_OK;
//    }
//
//    if (STR_EQUAL("0", string) || str_equal("NO", string, true) || str_equal("FALSE", string, true))
//    {
//        thiz->value = false;
//        return TINY_RET_OK;
//    }
//
//    LOG_W(TAG, "invalid boolean value: %s", string);
//
//    return TINY_RET_E_ARG_INVALID;
//}
//
//TINY_LOR
//const char * BoolValue_ToString(BoolValue *thiz)
//{
//    return thiz->value ? "1" : "0";
//}