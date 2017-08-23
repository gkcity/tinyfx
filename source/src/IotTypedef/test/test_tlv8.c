#include <tiny_log.h>
#include "data/value/Tlv8Value.h"

#define TAG     "TEST"

const char *salt = "BEB25379D1A8581EB5A727673A2441EE";
const char *B = "86578DAF73143151E2E12AA869D7779BAC70CA2B8D16C50CE1667A7EAB82206D939694D790F8736F6BF5FCA6BC0592F81FE976D7AC113C58CC51BAC10866404601B36D04A513AF6621E903D7B9E08C66E9A80031C85B43BE5B542E0BBF68914A50CF4DBC0570B432171CE5A9356674120B1A8AE21854A7D9195BAF570E84CDBD8AA7F475E954434303ADB746386B64D06D0CE2D7EB1617C9BB05EEE1455E2EF2B6E6DE50F9BC19F437374BE6181D984C425BE00A279BE6A46D89F2FACE038A56257A7C2F77BB8CE1B67E4A98759AD4189077EBBA3663909577C2173ABB0054D56969F0CE9743D50DFE4B9E76398FCA3FDB8D0B1B8467254396FE76461B38A01CABBEBFCCDB9F8A10637A0AA83BDF7390D0787C82B0A7054827929E2E2391DC7ED66CA781D8B636B278BF580DC68EA4F4726D33C78613C7123EF8C4A456741120CC69E0C029B302E7273295E44319BA8F8288F595015E4006F51B3D89EA13D6719BE8BE92CB6A9A9F4759F02254688AFEF502A485878E5CCD9FBAEA411546EAB5";

static void parse(const uint8_t *bytes, uint32_t size)
{
    Tlv8Value value;

    if (RET_FAILED(Tlv8Value_Construct(&value)))
    {
        LOG_D(TAG, "Tlv8Value_Construct FAILED");
        return;
    }

    if (RET_FAILED(Tlv8Value_Parse(&value, bytes, size, true)))
    {
        LOG_D(TAG, "Tlv8Value_Parse FAILED");
        return;
    }

    {
        Tlv8 *t = Tlv8Value_Get(&value, 6);
        printf("state: %d\n", t->length);
    }

    {
        char buf[1024];
        memset(buf, 0, 1024);

        Tlv8 *t = Tlv8Value_Get(&value, 2);
        printf("salt: %d\n", t->length);

        memcpy(buf, t->data, t->length);
        printf("state: %s\n", buf);

        if (strcmp(buf, salt) != 0)
        {
            printf("salt INVALID");
        }
        else
        {
            printf("read salt ok");
        }
    }

    {
        char buf[1024];
        memset(buf, 0, 1024);

        Tlv8 *t = Tlv8Value_Get(&value, 3);
        printf("B: %d\n", t->length);

        memcpy(buf, t->data, t->length);
        printf("B: %s\n", buf);

        if (strcmp(buf, B) != 0)
        {
            printf("B INVALID");
        }
        else
        {
            printf("read B ok");
        }
    }

    Tlv8Value_Dispose(&value);
}

static void test()
{
    Tlv8Value tlv8Value;

    if (RET_FAILED(Tlv8Value_Construct(&tlv8Value)))
    {
        LOG_D(TAG, "Tlv8Value_Construct FAILED");
        return;
    }

    // PairingValue_AddState: PAIRING_STATE_M2
    Tlv8Value_AddByte(&tlv8Value, 6, 0x02, false);

    // PairingValue_AddSalt
    Tlv8Value_AddBytes(&tlv8Value, 2, (const uint8_t *)salt, (uint32_t)(strlen(salt)), false);

    // PairingValue_AddPublicKey
    Tlv8Value_AddBytes(&tlv8Value, 3, (const uint8_t *)B, (uint32_t)(strlen(B)), false);

    parse(Tlv8Value_GetBytes(&tlv8Value), Tlv8Value_GetBytesSize(&tlv8Value));

    Tlv8Value_Dispose(&tlv8Value);
}

int main()
{
    test();

    return 0;
}