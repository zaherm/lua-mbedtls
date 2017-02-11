#ifndef LMBEDTLS_BASE64_H
#define LMBEDTLS_BASE64_H
#include "lmbedtls_aux.h"
#include "mbedtls/base64.h"

LUALIB_API int lmbedtls_base64_open(lua_State *L);
LUALIB_API int lmbedtls_base64_encode(lua_State *L);
LUALIB_API int lmbedtls_base64_decode(lua_State *L);

#endif

