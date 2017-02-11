#ifndef LMBEDTLS_SHA512_H
#define LMBEDTLS_SHA512_H
#include "lmbedtls_aux.h"
#include "mbedtls/sha512.h"

LUALIB_API int lmbedtls_sha512_open(lua_State *L);
LUALIB_API int lmbedtls_sha512(lua_State *L);
LUALIB_API int lmbedtls_sha512_new(lua_State *L);
LUALIB_API int lmbedtls_sha512_starts(lua_State *L);
LUALIB_API int lmbedtls_sha512_clone(lua_State *L);
LUALIB_API int lmbedtls_sha512_update(lua_State *L);
LUALIB_API int lmbedtls_sha512_finish(lua_State *L);
LUALIB_API int lmbedtls_sha512_free(lua_State *L);

#endif

