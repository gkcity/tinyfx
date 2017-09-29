/**
 * Copyright (C) 2017-2020
 *
 * @author wenzhenwei@xiaomi.com
 * @date   2017-7-1
 *
 * @file   PropertiesBean.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "PropertiesBean.h"
#include "PropertyBean.h"

#define TAG     "PropertiesBean"

TINY_LOR
static void OnPropertyBeanDelete (void * data, void *ctx)
{
    PropertyBean_Delete((PropertyBean *)data);
}

TINY_LOR
PropertiesBean * PropertiesBean_New(void)
{
    PropertiesBean *thiz = NULL;

    do
    {
        thiz = (PropertiesBean *)tiny_malloc(sizeof(PropertiesBean));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(PropertiesBean_Construct(thiz)))
        {
            PropertiesBean_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
void PropertiesBean_Delete(PropertiesBean *thiz)
{
    PropertiesBean_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
TinyRet PropertiesBean_Construct(PropertiesBean *thiz)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        ret = TinyList_Construct(&thiz->properties);
        if (RET_FAILED(ret))
        {
            break;
        }

        TinyList_SetDeleteListener(&thiz->properties, OnPropertyBeanDelete, NULL);
    } while (false);

    return ret;
}

TINY_LOR
void PropertiesBean_Dispose(PropertiesBean *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->properties);
}