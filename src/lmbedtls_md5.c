#include "lmbedtls_md5.h"

mbedtls_md5_context *lmbedtls_md5_check(lua_State *L, int index) {
  mbedtls_md5_context *c = (mbedtls_md5_context *) luaL_checkudata(L, index, "md5.ctx");
  luaL_argcheck(L, c != NULL, index, "md5.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_md5(lua_State *L) {
  size_t ilen;
  unsigned char output[16];
  int index = lua_istable(L, 1) ? 2 : 1; //2 is used if was invoked via __call
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, index, &ilen);

  mbedtls_md5(input, ilen, output);

  if(lua_toboolean(L, index + 1)) {
    lmbedtls_pushhexstring(L, output, 16);
  }
  else {
    lua_pushlstring(L, (const char *)output, 16);
  }
  return 1;
}

LUALIB_API int lmbedtls_md5_new(lua_State *L) {
  mbedtls_md5_context *ctx = (mbedtls_md5_context *)
                                lua_newuserdata(L, sizeof(mbedtls_md5_context));
  mbedtls_md5_init(ctx);
  mbedtls_md5_starts(ctx);
  lmbedtls_setmeta(L, "md5.ctx");
  return 1;
}

LUALIB_API int lmbedtls_md5_starts(lua_State *L) {
  mbedtls_md5_context *ctx = lmbedtls_md5_check(L, 1);
  mbedtls_md5_starts(ctx);
  return 0;
}

LUALIB_API int lmbedtls_md5_clone(lua_State *L) {
  mbedtls_md5_context *src = lmbedtls_md5_check(L, 1);
  mbedtls_md5_context *dst = (mbedtls_md5_context *)
                                lua_newuserdata(L, sizeof(mbedtls_md5_context));
  mbedtls_md5_clone(dst, src);
  lmbedtls_setmeta(L, "md5.ctx");
  return 1;
}

LUALIB_API int lmbedtls_md5_update(lua_State *L) {
  mbedtls_md5_context *ctx = lmbedtls_md5_check(L, 1);
  size_t dlen;
  const unsigned char *data =  (unsigned char *) luaL_checklstring(L, 2, &dlen);
  mbedtls_md5_update(ctx, data, dlen);
  return 0;
}

LUALIB_API int lmbedtls_md5_finish(lua_State *L) {
  mbedtls_md5_context *ctx = lmbedtls_md5_check(L, 1);
  unsigned char output[16];
  mbedtls_md5_finish(ctx, output);
  if(lua_toboolean(L, 2)) {
    lmbedtls_pushhexstring(L, output, 16);
  }
  else {
    lua_pushlstring(L, (const char *)output, 16);
  }
  return 1;
}

LUALIB_API int lmbedtls_md5_free(lua_State *L) {
  mbedtls_md5_context *ctx = lmbedtls_md5_check(L, 1);
  mbedtls_md5_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_md5_funcs[] = {
  { "new", lmbedtls_md5_new },
  { "calc", lmbedtls_md5 },
  { "__call", lmbedtls_md5 },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_md5_methods[] = {
  { "starts", lmbedtls_md5_starts },
  { "clone", lmbedtls_md5_clone },
  { "update", lmbedtls_md5_update },
  { "finish", lmbedtls_md5_finish },
  { "free", lmbedtls_md5_free },
  { "__gc", lmbedtls_md5_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_md5_open(lua_State *L) {
  lmbedtls_createmeta(L, "md5.ctx", lmbedtls_md5_methods);
  lmbedtls_createmeta(L, "md5", lmbedtls_md5_funcs);
  lmbedtls_setmeta(L, "md5");
  return 1;
}

