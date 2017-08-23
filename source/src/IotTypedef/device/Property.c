/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Property.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "Property.h"

#define TAG     "Property"

TINY_LOR
static TinyRet Property_Construct(Property *thiz);

TINY_LOR
static void Property_Dispose(Property *thiz);

TINY_LOR
Property* Property_New(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = (Property *)tiny_malloc(sizeof(Property));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Property_Construct(thiz)))
        {
            Property_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Property_Construct(Property *thiz)
{
    TinyRet ret;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Property));

        ret = Data_Construct(&thiz->data);
        if (RET_FAILED(ret)) {
            LOG_D(TAG, "Data_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static void Property_Dispose(Property *thiz)
{
    RETURN_IF_FAIL(thiz);

    Data_Dispose(&thiz->data);
}

TINY_LOR
void Property_Delete(Property *thiz)
{
    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "Property_Delete (iid: %d)", thiz->iid);

    Property_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
bool Property_IsReadable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_READ) != 0);
}

TINY_LOR
bool Property_IsWritable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_WRITE) != 0);
}

TINY_LOR
bool Property_IsNotifiable(Property *thiz)
{
    return ((thiz->accessType & ACCESS_NOTIFY) != 0);
}