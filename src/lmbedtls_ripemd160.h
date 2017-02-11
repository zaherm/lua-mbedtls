#ifndef LMBEDTLS_RIPEMD160_H
#define LMBEDTLS_RIPEMD160_H
#include "lmbedtls_aux.h"
#include "mbedtls/ripemd160.h"

LUALIB_API int lmbedtls_ripemd160_open(lua_State *L);
LUALIB_API int lmbedtls_ripemd160(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_new(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_starts(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_clone(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_update(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_finish(lua_State *L);
LUALIB_API int lmbedtls_ripemd160_free(lua_State *L);

#endif

