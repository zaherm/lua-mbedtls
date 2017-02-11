#include "lmbedtls_ripemd160.h"

mbedtls_ripemd160_context *lmbedtls_ripemd160_check(lua_State *L, int index) {
  mbedtls_ripemd160_context *c = (mbedtls_ripemd160_context *) luaL_checkudata(L, index, "ripemd160.ctx");
  luaL_argcheck(L, c != NULL, index, "ripemd160.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_ripemd160(lua_State *L) {
  size_t ilen;
  unsigned char output[20];
  int index = lua_istable(L, 1) ? 2 : 1; //2 is used if was invoked via __call
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, index, &ilen);

  mbedtls_ripemd160(input, ilen, output);

  if(lua_toboolean(L, index + 1)) {
    lmbedtls_pushhexstring(L, output, 20);
  }
  else {
    lua_pushlstring(L, (const char *)output, 20);
  }
  return 1;
}

LUALIB_API int lmbedtls_ripemd160_new(lua_State *L) {
  mbedtls_ripemd160_context *ctx = (mbedtls_ripemd160_context *)
                                lua_newuserdata(L, sizeof(mbedtls_ripemd160_context));
  mbedtls_ripemd160_init(ctx);
  mbedtls_ripemd160_starts(ctx);
  lmbedtls_setmeta(L, "ripemd160.ctx");
  return 1;
}

LUALIB_API int lmbedtls_ripemd160_starts(lua_State *L) {
  mbedtls_ripemd160_context *ctx = lmbedtls_ripemd160_check(L, 1);
  mbedtls_ripemd160_starts(ctx);
  return 0;
}

LUALIB_API int lmbedtls_ripemd160_clone(lua_State *L) {
  mbedtls_ripemd160_context *src = lmbedtls_ripemd160_check(L, 1);
  mbedtls_ripemd160_context *dst = (mbedtls_ripemd160_context *)
                                lua_newuserdata(L, sizeof(mbedtls_ripemd160_context));
  mbedtls_ripemd160_clone(dst, src);
  lmbedtls_setmeta(L, "ripemd160.ctx");
  return 1;
}

LUALIB_API int lmbedtls_ripemd160_update(lua_State *L) {
  mbedtls_ripemd160_context *ctx = lmbedtls_ripemd160_check(L, 1);
  size_t dlen;
  const unsigned char *data =  (unsigned char *) luaL_checklstring(L, 2, &dlen);
  mbedtls_ripemd160_update(ctx, data, dlen);
  return 0;
}

LUALIB_API int lmbedtls_ripemd160_finish(lua_State *L) {
  mbedtls_ripemd160_context *ctx = lmbedtls_ripemd160_check(L, 1);
  unsigned char output[20];
  mbedtls_ripemd160_finish(ctx, output);
  if(lua_toboolean(L, 2)) {
    lmbedtls_pushhexstring(L, output, 20);
  }
  else {
    lua_pushlstring(L, (const char *)output, 20);
  }
  return 1;
}

LUALIB_API int lmbedtls_ripemd160_free(lua_State *L) {
  mbedtls_ripemd160_context *ctx = lmbedtls_ripemd160_check(L, 1);
  mbedtls_ripemd160_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_ripemd160_funcs[] = {
  { "new", lmbedtls_ripemd160_new },
  { "calc", lmbedtls_ripemd160 },
  { "__call", lmbedtls_ripemd160 },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_ripemd160_methods[] = {
  { "starts", lmbedtls_ripemd160_starts },
  { "clone", lmbedtls_ripemd160_clone },
  { "update", lmbedtls_ripemd160_update },
  { "finish", lmbedtls_ripemd160_finish },
  { "free", lmbedtls_ripemd160_free },
  { "__gc", lmbedtls_ripemd160_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_ripemd160_open(lua_State *L) {
  lmbedtls_createmeta(L, "ripemd160.ctx", lmbedtls_ripemd160_methods);
  lmbedtls_createmeta(L, "ripemd160", lmbedtls_ripemd160_funcs);
  lmbedtls_setmeta(L, "ripemd160");
  return 1;
}

