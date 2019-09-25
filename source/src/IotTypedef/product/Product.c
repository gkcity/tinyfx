/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Thing.c
 *
 * @remark
 *
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <operation/PropertyOperation.h>
#include <status/IotStatus.h>
#include "device/Property.h"
#include "Product.h"
#include "device/Service.h"
#include "device/Action.h"

#define TAG     "Thing"

TINY_LOR
static TinyRet Product_Construct(Product *thiz, PropertyLock lock, PropertyUnlock unlock, void *ctx);

TINY_LOR
static void Product_Dispose(Product *thiz);

TINY_LOR
static void device_release_handler(void *data, void *ctx)
{
    Device_Delete((Device *)data);
}

TINY_LOR
Product* Product_New(PropertyLock lock, PropertyUnlock unlock, void *ctx)
{
    Product *thiz = NULL;

    do
    {
        thiz = (Product *)tiny_malloc(sizeof(Product));
        if (thiz == NULL)
        {
            LOG_D(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(Product_Construct(thiz, lock, unlock, ctx)))
        {
            Product_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}

TINY_LOR
static TinyRet Product_Construct(Product *thiz, PropertyLock lock, PropertyUnlock unlock, void *ctx)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(Product));

        thiz->locker.lock = lock;
        thiz->locker.unlock = unlock;
        thiz->locker.ctx = ctx;

        ret = Device_Construct(&thiz->device);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "Device_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }

        ret = TinyList_Construct(&thiz->children, device_release_handler, NULL);
        if (RET_FAILED(ret))
        {
            LOG_D(TAG, "TinyList_Construct FAILED: %s", tiny_ret_to_str(ret));
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static void Product_Dispose(Product *thiz)
{
    RETURN_IF_FAIL(thiz);

    TinyList_Dispose(&thiz->children);
    Device_Dispose(&thiz->device);
}

TINY_LOR
void Product_Delete(Product *thiz)
{
    RETURN_IF_FAIL(thiz);

    Product_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
bool Product_CheckHandler(Product *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, false);

    LOG_D(TAG, "Product_CheckHandler");

    if (thiz->onSet == NULL)
    {
        LOG_E(TAG, "Property Setter is null");
        return false;
    }

    if (thiz->onGet == NULL)
    {
        LOG_E(TAG, "Property Getter is null");
        return false;
    }

    if (thiz->onInvoke == NULL)
    {
        LOG_E(TAG, "Action Invocation is null");
    }

    return true;
}