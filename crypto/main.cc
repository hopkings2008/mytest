
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <openssl/hmac.h>

int main() {

    const char key[] = "$shiQI!1234";

    char data[] = "13";


    unsigned char* result;
    unsigned int len = 32;

    result = (unsigned char*)malloc(sizeof(char) * len);

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);


    HMAC_Init_ex(&ctx, key, strlen(key), EVP_sha256(), NULL);
    HMAC_Update(&ctx, (unsigned char*)&data, strlen(data));
    HMAC_Final(&ctx, result, &len);
    HMAC_CTX_cleanup(&ctx);

    printf("HMAC digest %d: \n", len);

    std::string ss;
    for (unsigned int i = 0; i < len; i++){
        char by[4] = {0};
        printf("%02x", (unsigned int)result[i]);
        snprintf(by, 4, "%02x", (unsigned int)result[i]);
        ss += by;
    }

    printf("\n");
    printf("ss: %s\n", ss.c_str());

    free(result);

    return 0;
}
