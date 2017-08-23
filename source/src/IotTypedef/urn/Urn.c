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

#include "Urn.h"

TINY_LOR
void Urn_Initialize(Urn *thiz, const char *ns, UrnType type, const char *name, uint32_t value)
{
    strncpy(thiz->namespace, ns, URN_NAMESPACE_LENGTH);
    thiz->type = type;
    strncpy(thiz->name, name, URN_NAME_LENGTH);
    thiz->value = value;
}
