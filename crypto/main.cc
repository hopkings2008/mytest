#include <stdio.h>
#include <string>
#include <apr-1/apr_crypto.h>

#define ALIGNED_STRING "123456"

int main(int argc, char *argv[]) {
	const std::string plain = "123456";
	const std::string mykey = "mykey";
	const std::string salt = "salt";
	const std::string myiv = "myiv";
	//const unsigned char *in = (const unsigned char *) ALIGNED_STRING;
	//apr_size_t inlen = sizeof(ALIGNED_STRING);
	apr_pool_t *pool = NULL;
	const apr_crypto_driver_t *driver = NULL;
	const apu_err_t *err = NULL;
	apr_status_t rv;
	rv = apr_initialize();
	if(rv != APR_SUCCESS) {
		printf("pool init failed.\n");
		return 1;
	}
	apr_pool_create(&pool, NULL);
	rv = apr_crypto_init(pool);
	if(rv != APR_SUCCESS) {
		printf("init pool failed.\n");
		return 1;
	}
	rv = apr_crypto_get_driver(&driver, "openssl", NULL, &err, pool);
	if(rv != APR_SUCCESS) {
		printf("get driver failed.\n");
		return 1;
	}
	apr_crypto_t *f = NULL;
	apr_crypto_make(&f, driver, "engine=openssl", pool);
	if(!f){
		printf("cannot create crypto f.\n");
		return 1;
	}
	apr_crypto_key_t *key = NULL;
	rv = apr_crypto_passphrase(&key, NULL, mykey.c_str(), mykey.length(),
			(unsigned char *)salt.c_str(), salt.length(), APR_KEY_AES_256, APR_MODE_CBC, 1, 4096, f, pool);
	if(rv != APR_SUCCESS) {
		printf("failed to create key. \n");
		return 1;
	}

	unsigned char *cipherText = NULL;
	apr_size_t cipherTextLen = 0;
	unsigned char *plainText = NULL;
	apr_size_t plainTextLen = 0;
	const unsigned char *iv = (const unsigned char *)myiv.c_str();
	apr_size_t blockSize = 0;
	apr_size_t len = 0;

	apr_crypto_block_t *block = NULL;
	rv = apr_crypto_block_encrypt_init(&block, &iv, key, &blockSize, pool);
	if(rv != APR_SUCCESS) {
		printf("init encrypt failed.\n");
		return 1;
	}
	if(!block || rv) {
		printf("block or rv is faied.\n");
		return 1;
	}
	rv = apr_crypto_block_encrypt(&cipherText, &cipherTextLen, (const unsigned char*)plain.c_str(), plain.length(), block);
	if(rv != APR_SUCCESS){
	       printf("encrypt failed.\n");
return 1;
	}
	rv = apr_crypto_block_encrypt_finish(cipherText + cipherTextLen, &len, block);
	if(rv != APR_SUCCESS) {
		apr_crypto_error(&err, f);
		printf("encrypt finish failed, err: %d %s(%s)\n", err->rc, err->reason ? err->reason : "", err->msg ? err->msg:"");
		return 1;
	}
	cipherTextLen += len;
	apr_crypto_block_cleanup(block);
	printf("encrypt succeed., cipherTextLen: %ld\n", cipherTextLen);
	block = NULL;
	blockSize = 0;

	rv = apr_crypto_block_decrypt_init(&block, &blockSize, iv, key, pool);
	if(rv != APR_SUCCESS) {
		printf("failed to decrypt init.\n");
		return 1;
	}
	if(!block || rv) {
		printf("decrypt, block or iv is invalid.\n");
		return 1;
	}

	rv = apr_crypto_block_decrypt(&plainText, &plainTextLen, cipherText, cipherTextLen, block);
	if (rv != APR_SUCCESS) {
		printf("decryt failed.\n");
		return 1;
	}
	rv = apr_crypto_block_decrypt_finish(plainText+plainTextLen, &len, block);
	if (rv != APR_SUCCESS) {
		printf("decrypt finish failed.\n");
		return 1;
	}

	plainTextLen += len;
	std::string out((const char *)plainText);
	out.resize(len);
	printf("plainText: %s, len: %ld\n", out.c_str(), plainTextLen);
	apr_crypto_block_cleanup(block);
	apr_pool_destroy(pool);
	apr_terminate();
	return 0;
}
