#ifndef LMBEDTLS_AES_H
#define LMBEDTLS_AES_H
#include "lmbedtls_aux.h"
#include "mbedtls/aes.h"

LUALIB_API int lmbedtls_aes_open(lua_State *L);
LUALIB_API int lmbedtls_aes_new(lua_State *L);
LUALIB_API int lmbedtls_aes_setkey_enc(lua_State *L);
LUALIB_API int lmbedtls_aes_setkey_dec(lua_State *L);
LUALIB_API int lmbedtls_aes_crypt_cfb8(lua_State *L);
LUALIB_API int lmbedtls_aes_free(lua_State *L);

#endif

