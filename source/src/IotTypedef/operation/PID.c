/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PID.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include "PID.h"

#define TAG     "PID"

TINY_LOR
PID * PID_New(void)
{
    PID *thiz = NULL;

    do
    {
        thiz = (PID *)tiny_malloc(sizeof(PID));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        memset(thiz, 0, sizeof(PID));
    } while (false);

    return thiz;
}

IOT_API
TINY_LOR
void PID_Delete(PID *thiz)
{
    tiny_free(thiz);
}