/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Urn.h
 *
 * @remark
 *
 */

#include <tiny_str_split.h>
#include <StringArray.h>
#include <tiny_malloc.h>
#include "Urn.h"


TINY_LOR
TinyRet Urn_Construct(Urn *thiz)
{
    memset(thiz, 0, sizeof(Urn));

    return TINY_RET_OK;
}

TINY_LOR
void Urn_Dispose(Urn *thiz)
{
    if (thiz->namespace != NULL)
    {
        tiny_free(thiz->namespace);
    }

    if (thiz->name != NULL)
    {
        tiny_free(thiz->name);
    }

    memset(thiz, 0, sizeof(Urn));
}

TINY_LOR
TinyRet Urn_Set(Urn *thiz, const char *ns, UrnType type, const char *name, uint32_t value)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        size_t length = 0;

        length = strlen(ns) + 1;
        thiz->namespace = tiny_malloc(length);
        if (thiz->namespace == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
        memset(thiz->namespace, 0, length);
        strncpy(thiz->namespace, ns, length);

        length = strlen(name) + 1;
        thiz->name = tiny_malloc(length);
        if (thiz->name == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
        memset(thiz->name, 0, length);
        strncpy(thiz->name, name, length);

        thiz->type = type;
        thiz->value = value;
    } while (false);

    return ret;
}

TINY_LOR
TinyRet Urn_SetString(Urn *thiz, const char *string)
{
    TinyRet ret = TINY_RET_OK;
    StringArray *array = NULL;

    do
    {
        const char *urn = NULL;
        const char *namespace = NULL;
        const char *type = NULL;
        const char *name = NULL;
        const char *value = NULL;
        const char *vendor = NULL;

        array = StringArray_NewString(string, ":");
        if (array == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (! (array->values.size == 5 || array->values.size == 6))
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        urn = (const char *) TinyList_GetAt(&array->values, 0);
        if (! STR_EQUAL(urn, "urn"))
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        namespace = (const char *) TinyList_GetAt(&array->values, 1);
        type = (const char *) TinyList_GetAt(&array->values, 2);
        name = (const char *) TinyList_GetAt(&array->values, 3);
        value = (const char *) TinyList_GetAt(&array->values, 4);
        vendor = (const char *) TinyList_GetAt(&array->values, 5);

//        strncpy(thiz->namespace, namespace, URN_NAMESPACE_LENGTH);
//        strncpy(thiz->name, name, URN_NAME_LENGTH);

    } while (false);

    if (array != NULL)
    {
        StringArray_Delete(array);
    }

    return ret;
}