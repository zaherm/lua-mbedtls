#ifndef LMBEDTLS_AUX_H
#define LMBEDTLS_AUX_H
#include <string.h>
#include "lauxlib.h"

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup);
#endif

LUALIB_API void lmbedtls_setmeta(lua_State *L, const char *name);
LUALIB_API int lmbedtls_createmeta(lua_State *L, const char *name, const luaL_Reg *methods);

LUALIB_API void lmbedtls_pushhexstring(lua_State *L, const unsigned char *buf, int len);

void lmbedtls_error(lua_State *L, const char *msg);
void lmbedtls_assert(lua_State *L, int cond, const char *msg);
void lmbedtls_hexify(unsigned char *obuf, const unsigned char *ibuf, int len);

int lmbedtls_checkoption(lua_State *L, int index, const char *key,
    const char *const keys[], const int values[]);
#endif

