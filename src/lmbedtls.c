#include "lmbedtls.h"

LUALIB_API int luaopen_mbedtls(lua_State *L) {
  lua_newtable(L);
  //set mbedtls top level functions
  luaL_setfuncs(L, lmbedtls_funcs, 0);
  //init modules
  for(int i = 0; lmbedtls_mods[i].name; i++) {
    lua_newtable(L);
    lmbedtls_mods[i].func(L);
    lua_setfield(L, -2, lmbedtls_mods[i].name);
  }

  lua_pushliteral(L, LMBEDTLS_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LMBEDTLS_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LMBEDTLS_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");
  return 1;
}

