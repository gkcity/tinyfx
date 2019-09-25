/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   ProductLocker.h
 *
 * @remark
 *
 */

#ifndef __PRODUCT_LOCKER_H__
#define __PRODUCT_LOCKER_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef void (*PropertyLock)(void);
typedef void (*PropertyUnlock)(void);

typedef struct _ProductLocker
{
    PropertyLock              lock;
    PropertyUnlock            unlock;
} ProductLocker;


TINY_END_DECLS

#endif /* __PRODUCT_LOCKER_H__ */