#ifndef LMBEDTLS_MD5_H
#define LMBEDTLS_MD5_H
#include "lmbedtls_aux.h"
#include "mbedtls/md5.h"

LUALIB_API int lmbedtls_md5_open(lua_State *L);
LUALIB_API int lmbedtls_md5(lua_State *L);
LUALIB_API int lmbedtls_md5_new(lua_State *L);
LUALIB_API int lmbedtls_md5_starts(lua_State *L);
LUALIB_API int lmbedtls_md5_clone(lua_State *L);
LUALIB_API int lmbedtls_md5_update(lua_State *L);
LUALIB_API int lmbedtls_md5_finish(lua_State *L);
LUALIB_API int lmbedtls_md5_free(lua_State *L);

#endif

