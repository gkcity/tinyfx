/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertyChangedObserver.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include "PropertyChangedObserver.h"

TINY_LOR
PropertyChangedObserver* PropertyChangedObserver_New(void)
{
    return (PropertyChangedObserver *)tiny_malloc(sizeof(PropertyChangedObserver));
}

TINY_LOR
void PropertyChangedObserver_Delete(PropertyChangedObserver *thiz)
{
    tiny_free(thiz);
}