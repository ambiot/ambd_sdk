
#include "mbedtls/sha256.h"


void mbedtls_sha256_starts_ret(mbedtls_sha256_context *ctx, int is224)
{
    mbedtls_sha256_starts(ctx, is224);
}

void mbedtls_sha256_update_ret(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen)
{
    mbedtls_sha256_update(ctx, input, ilen);
}

void mbedtls_sha256_finish_ret(mbedtls_sha256_context *ctx, unsigned char output[32])
{
    mbedtls_sha256_finish(ctx, output);
}

void mbedtls_sha256_ret(const unsigned char *input, size_t ilen, unsigned char output[32], int is224)
{
    mbedtls_sha256(input, ilen, output, is224);
}