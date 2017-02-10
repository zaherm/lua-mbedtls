#ifndef LMBEDTLS_SHA256_H
#define LMBEDTLS_SHA256_H
#include "lmbedtls_aux.h"
#include "mbedtls/sha256.h"

LUALIB_API int lmbedtls_sha256_open(lua_State *L);
LUALIB_API int lmbedtls_sha256(lua_State *L);
LUALIB_API int lmbedtls_sha256_new(lua_State *L);
LUALIB_API int lmbedtls_sha256_starts(lua_State *L);
LUALIB_API int lmbedtls_sha256_clone(lua_State *L);
LUALIB_API int lmbedtls_sha256_update(lua_State *L);
LUALIB_API int lmbedtls_sha256_finish(lua_State *L);
LUALIB_API int lmbedtls_sha256_free(lua_State *L);

#endif

