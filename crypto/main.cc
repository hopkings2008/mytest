
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <openssl/hmac.h>

int main() {

    const char key[] = "012345678";

    char data[] = "hello world";


    unsigned char* result;
    unsigned int len = 32;

    result = (unsigned char*)malloc(sizeof(char) * len);

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);


    HMAC_Init_ex(&ctx, key, strlen(key), EVP_sha256(), NULL);
    HMAC_Update(&ctx, (unsigned char*)&data, strlen(data));
    HMAC_Final(&ctx, result, &len);
    HMAC_CTX_cleanup(&ctx);

    printf("HMAC digest: ");

    std::stringstream ss;
    for (unsigned int i = 0; i != len; i++){
        printf("%02x", (unsigned int)result[i]);
        ss << result[i];
    }

    printf("\n");
    printf("ss: %s\n", ss.str().c_str());

    free(result);

    return 0;
}
