#include <tiny_log.h>
#include <device/Service.h>
#include <device/Property.h>
#include <device/Action.h>
#include "../DeviceInstance.h"

/**
 * NO ACTION
 */
#define ZHIMI_FAN "/instance/device?type=urn:miot-spec:device:fan:00000A04:zhimi"

/**
 * Contains Action without arguments
 */
#define ROCK_SWEEPER "/instance/device?type=urn:miot-spec:device:sweeper:00000A0A:rock"

/**
 * Contains Action with arguments
 */
#define CHUNMI_COOKER "/instance/device?type=urn:miot-spec:device:cooker:00000A08:chunmi"

int main(void)
{
    Device * device = DeviceInstance_New("47.93.60.147", 8080, CHUNMI_COOKER, 5);
    if (device == NULL)
    {
        printf("DeviceInstance_New failed!\n");
        return 0;
    }

    printf("Device: %d\n", device->iid);
    printf("Service: [%d]\n", device->services.size);
    for (uint32_t i = 0; i < device->services.size; ++i)
    {
        Service *service = (Service *) TinyList_GetAt(&device->services, i);

        printf("  service: %d\n", service->iid);
        printf("    type: urn:%s:%s:%s:%08x\n", service->type.namespace, UrnType_ToString(service->type.type), service->type.name, service->type.value);
        printf("    Properties: [%d]\n", service->properties.size);

        for (uint32_t j = 0; j < service->properties.size; ++j)
        {
            Property *p = (Property *) TinyList_GetAt(&service->properties, j);
            printf("      property: %d\n", p->iid);
            printf("        type: urn:%s:%s:%s:%08x\n", p->type.namespace, UrnType_ToString(p->type.type), p->type.name, p->type.value);
            printf("        format: %s\n", DataType_GetName(p->data.type));
        }

        printf("    Actions: [%d]\n", service->actions.size);

        for (uint32_t j = 0; j < service->actions.size; ++j)
        {
            Action *action = (Action *) TinyList_GetAt(&service->actions, j);
            printf("      action: %d\n", action->iid);
            printf("        type: urn:%s:%s:%s:%08x\n", action->type.namespace, UrnType_ToString(action->type.type), action->type.name, action->type.value);
            printf("        in(%d): \n", action->in.size);

            for (uint32_t k = 0; k < action->in.size; ++k)
            {
                Property *p = (Property *) TinyList_GetAt(&action->in, j);
                printf("          iid: %d\n", p->iid);
                printf("          type: urn:%s:%s:%s:%08x\n", p->type.namespace, UrnType_ToString(p->type.type), p->type.name, p->type.value);
            }

            printf("        out(%d): \n", action->out.size);

            for (uint32_t k = 0; k < action->out.size; ++k)
            {
                Property *p = (Property *) TinyList_GetAt(&action->out, j);
                printf("          iid: %d\n", p->iid);
                printf("          type: urn:%s:%s:%s:%08x\n", p->type.namespace, UrnType_ToString(p->type.type), p->type.name, p->type.value);
            }
        }
    }

    Device_Delete(device);

    return 0;
}