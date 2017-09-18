#include <tiny_log.h>
#include "../DeviceInstance.h"

#define URI "/homekit/instance/device?type=urn:homtkit-spec:device:lightbulb:00000000:arrizo-v1"

int main(void)
{
    Device * device = DeviceInstance_New("47.93.60.147", 8080, URI, 5);
    if (device == NULL)
    {
        printf("DeviceInstance_New failed!\n");
        return 0;
    }

    return 0;
}