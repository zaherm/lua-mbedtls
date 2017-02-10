#ifndef LMBEDTLS_SHA1_H
#define LMBEDTLS_SHA1_H
#include "lmbedtls_aux.h"
#include "mbedtls/sha1.h"

LUALIB_API int lmbedtls_sha1_open(lua_State *L);
LUALIB_API int lmbedtls_sha1(lua_State *L);
LUALIB_API int lmbedtls_sha1_new(lua_State *L);
LUALIB_API int lmbedtls_sha1_starts(lua_State *L);
LUALIB_API int lmbedtls_sha1_clone(lua_State *L);
LUALIB_API int lmbedtls_sha1_update(lua_State *L);
LUALIB_API int lmbedtls_sha1_finish(lua_State *L);
LUALIB_API int lmbedtls_sha1_free(lua_State *L);

#endif

