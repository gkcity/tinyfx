/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-9-1
 *
 * @file   IotStatus.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IOT_STATUS_H__
#define __IOT_STATUS_H__

#include <tiny_base.h>



#define IOT_STATUS_OK                  (0)
#define IOT_STATUS_ACCEPT              (1)
#define IOT_STATUS_CANNOT_READ         (-1)
#define IOT_STATUS_CANNOT_WRITE        (-2)
#define IOT_STATUS_CANNOT_NOTIFY       (-3)
#define IOT_STATUS_NOT_EXIST           (-4)
#define IOT_STATUS_INTERNAL_ERROR      (-5)
#define IOT_STATUS_VALUE_ERROR         (-6)
#define IOT_STATUS_ACTION_IN_ERROR     (-7)
#define IOT_STATUS_ACTION_OUT_ERROR    (-8)
#define IOT_STATUS_VERIFY_ERROR        (-9)


#endif /* __IOT_STATUS_H__ */
