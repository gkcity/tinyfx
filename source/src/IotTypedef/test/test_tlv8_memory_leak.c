#include <tiny_log.h>
#include "data/value/Tlv8Value.h"

#define TAG     "TEST"


/**
* format: integer
* Method to use for pairing
*/
#define TLV8_TYPE_METHOD                                         0

/**
* format: UTF-8
* Identifier for authentication.
*/
#define TLV8_TYPE_IDENTIFIER                                     1

/**
* format: bytes
* 16+ bytes of random salt.
*/
#define TLV8_TYPE_SALT                                           2

/**
* format: bytes
* Curve25519     SRP public key     or signed Ed25519 key.
*/
#define TLV8_TYPE_PUBLIC_KEY                                     3

/**
* format: bytes
* Ed25519 or SRP proof.
*/
#define TLV8_TYPE_PROOF                                          4

/**
* format: bytes
* Encrypted data with auth tag at end.
*/
#define TLV8_TYPE_ENCRYPTED_DATA                                 5

/**
* format: integer
* State of the pairing process. 1=M1     2=M2     etc.
*/
#define TLV8_TYPE_STATE                                          6

/**
* format: integer
* Error code. Must only be present if error code is not 0.
*/
#define TLV8_TYPE_ERROR                                          7

/**
* format: integer
* Seconds to delay until retrying a setup code.
*/
#define TLV8_TYPE_RETRY_DELAY                                    8

/**
* format: bytes
* X.509 Certificate.
*/
#define TLV8_TYPE_CERTIFICATE                                    9

/**
* format: bytes
* Ed25519 or Apple Authentication Coprocessor signature.
*/
#define TLV8_TYPE_SIGNATURE                                      0x0a

/**
* format: integer
* Bit value describing permissions of the controller being added.
*  None ( 0x00 ) : Regular user
*  Bit 1 ( 0x01 ) : Admin that is able to add and remove pairings against the accessory.
*/
#define TLV8_TYPE_PERMISSIONS                                    0x0b

/**
* format: bytes
* Non-last fragment of data. If length is 0     it's an ACK
*/
#define TLV8_TYPE_FRAGMENT_DATA                                  0x0c

/**
* format: bytes
* Last fragment of data.
*/
#define TLV8_TYPE_FRAGMENT_LAST                                  0x0d

/**
* format: null
* Zero-length TLV that separates different TLVs in a list
*/
#define TLV8_TYPE_SEPARATOR                                      0xff


#define PAIRING_STATE_NULL                0xFF
#define PAIRING_STATE_M1                  0x01
#define PAIRING_STATE_M2                  0x02
#define PAIRING_STATE_M3                  0x03
#define PAIRING_STATE_M4                  0x04
#define PAIRING_STATE_M5                  0x05
#define PAIRING_STATE_M6                  0x06

const char *salt = "BEB25379D1A8581EB5A727673A2441EE";
const char *B = "86578DAF73143151E2E12AA869D7779BAC70CA2B8D16C50CE1667A7EAB82206D939694D790F8736F6BF5FCA6BC0592F81FE976D7AC113C58CC51BAC10866404601B36D04A513AF6621E903D7B9E08C66E9A80031C85B43BE5B542E0BBF68914A50CF4DBC0570B432171CE5A9356674120B1A8AE21854A7D9195BAF570E84CDBD8AA7F475E954434303ADB746386B64D06D0CE2D7EB1617C9BB05EEE1455E2EF2B6E6DE50F9BC19F437374BE6181D984C425BE00A279BE6A46D89F2FACE038A56257A7C2F77BB8CE1B67E4A98759AD4189077EBBA3663909577C2173ABB0054D56969F0CE9743D50DFE4B9E76398FCA3FDB8D0B1B8467254396FE76461B38A01CABBEBFCCDB9F8A10637A0AA83BDF7390D0787C82B0A7054827929E2E2391DC7ED66CA781D8B636B278BF580DC68EA4F4726D33C78613C7123EF8C4A456741120CC69E0C029B302E7273295E44319BA8F8288F595015E4006F51B3D89EA13D6719BE8BE92CB6A9A9F4759F02254688AFEF502A485878E5CCD9FBAEA411546EAB5";

static void test()
{
    Tlv8Value m2;
    const char *bytes = NULL;
    uint32_t size = 0;

    if (RET_FAILED(Tlv8Value_Construct(&m2)))
    {
        printf("Tlv8Value_Construct FAILED\n");
        return;
    }

    Tlv8Value_AddByte(&m2, TLV8_TYPE_STATE, PAIRING_STATE_M2, false);
    Tlv8Value_AddBytes(&m2, TLV8_TYPE_SALT, salt, (uint32_t)(strlen(salt)), false);
    Tlv8Value_AddBytes(&m2, TLV8_TYPE_PUBLIC_KEY, B, (uint32_t)(strlen(B)), false);

    bytes = Tlv8Value_GetBytes(&m2);
    size = Tlv8Value_GetBytesSize(&m2);
    printf("size: %d\n", size);

    Tlv8Value_Dispose(&m2);
}

int main()
{
    test();

    return 0;
}