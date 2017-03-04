#include "lmbedtls_aux.h"

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
  luaL_checkstack(L, nup+1, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    lua_pushstring(L, l->name);
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      lua_pushvalue(L, -(nup+1));
    lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    lua_settable(L, -(nup + 3));
  }
  lua_pop(L, nup);  /* remove upvalues */
}
#endif


void lmbedtls_error(lua_State *L, const char *msg) {
  luaL_error(L, msg);
}

LUALIB_API void lmbedtls_setmeta(lua_State *L, const char *name) {
  luaL_getmetatable(L, name);
  lua_setmetatable(L, -2);
}

LUALIB_API int lmbedtls_createmeta(lua_State *L, const char *name, const luaL_Reg *methods) {
  if (!luaL_newmetatable(L, name)) {
    return 0;
  }

  lua_pushstring(L, "__index");
  lua_newtable(L);
  lua_pushstring(L, "class");
  lua_pushstring(L, name);
  lua_rawset(L, -3);

  for (; methods->name; methods++) {
    lua_pushstring(L, methods->name);
    lua_pushcfunction(L, methods->func);
    lua_rawset(L, methods->name[0] == '_' ? -5: -3);
  }
  lua_rawset(L, -3);
  lua_pop(L, 1);
  return 1;
}

LUALIB_API void lmbedtls_pushhexstring(lua_State *L, const unsigned char *buf, int len) {
  int olen = (len * 2);
  unsigned char output[olen];
  lmbedtls_hexify(output, buf, len);
  lua_pushlstring(L, (const char *)output, olen);
}

void lmbedtls_assert(lua_State *L, int cond, const char *msg)  {
  if(!cond) {
    lmbedtls_error(L, msg);
  }
}

/*
 * source: mbedtls/tests/suites/helpers.function
 */
void lmbedtls_hexify(unsigned char *obuf, const unsigned char *ibuf, int len){
  unsigned char l, h;

  while( len != 0 ) {
    h = *ibuf / 16;
    l = *ibuf % 16;

    if( h < 10 )
      *obuf++ = '0' + h;
    else
      *obuf++ = 'a' + h - 10;

    if( l < 10 )
      *obuf++ = '0' + l;
    else
      *obuf++ = 'a' + l - 10;

    ++ibuf;
    len--;
  }
}

int lmbedtls_checkoption(lua_State *L, int index, const char *key,
    const char *const keys[], const int values[]) {
  int i = luaL_checkoption(L, index, key, keys);
  return values[i];
}
