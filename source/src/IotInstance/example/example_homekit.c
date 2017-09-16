#include <tiny_log.h>
#include "../HttpInstance.h"

#define URI "/homekit/instance/device?type=urn:homtkit-spec:device:lightbulb:00000000:arrizo-v1"

int main(void)
{
    do
    {
        JsonObject *json = HttpInstance_Get("47.93.60.147", 8080, URI, 5);
        if (json == NULL)
        {
            printf("HttpInstance_Get Failed\n");
            break;
        }

        if (RET_SUCCEEDED(JsonObject_Encode(json, true)))
        {
            printf("JsonObject_Encode:\n%s\n", json->string);
        }

        JsonObject_Delete(json);
    } while (false);

    return 0;
}