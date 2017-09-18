#include <tiny_log.h>
#include <device/Service.h>
#include <device/Property.h>
#include "../DeviceInstance.h"

//#define URI "/homekit/instance/device?type=urn:homtkit-spec:device:lightbulb:00000000:arrizo-v1"
#define URI "/instance/device?type=urn:miot-spec:device:fan:00000A04:zhimi"

int main(void)
{
    Device * device = DeviceInstance_New("47.93.60.147", 8080, URI, 5);
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
        printf("    type: urn:%s:<%d>:%s:%08x\n", service->type.namespace, service->type.type, service->type.name, service->type.value);
        printf("    Properties: [%d]\n", service->properties.size);

        for (uint32_t j = 0; j < service->properties.size; ++j)
        {
            Property *property = (Property *) TinyList_GetAt(&service->properties, j);
            printf("      property: %d\n", property->iid);
            printf("        type: urn:%s:<%d>:%s:%08x\n", property->type.namespace, property->type.type, property->type.name, property->type.value);
            printf("        format: %s\n", DataType_GetName(property->data.type));
        }
    }

    Device_Delete(device);

    return 0;
}