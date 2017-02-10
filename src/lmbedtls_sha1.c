#include "lmbedtls_sha1.h"

mbedtls_sha1_context *lmbedtls_sha1_check(lua_State *L, int index) {
  mbedtls_sha1_context *c = (mbedtls_sha1_context *) luaL_checkudata(L, index, "sha1.ctx");
  luaL_argcheck(L, c != NULL, index, "sha1.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_sha1(lua_State *L) {
  size_t ilen;
  unsigned char output[20];
  int index = lua_istable(L, 1) ? 2 : 1; //2 is used if was invoked via __call
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, index, &ilen);

  mbedtls_sha1(input, ilen, output);

  if(lua_toboolean(L, index + 1)) {
    lmbedtls_pushhexstring(L, output, 20);
  }
  else {
    lua_pushlstring(L, (const char *)output, 20);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha1_new(lua_State *L) {
  mbedtls_sha1_context *ctx = (mbedtls_sha1_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha1_context));
  mbedtls_sha1_init(ctx);
  mbedtls_sha1_starts(ctx);
  lmbedtls_setmeta(L, "sha1.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha1_starts(lua_State *L) {
  mbedtls_sha1_context *ctx = lmbedtls_sha1_check(L, 1);
  mbedtls_sha1_starts(ctx);
  return 0;
}

LUALIB_API int lmbedtls_sha1_clone(lua_State *L) {
  mbedtls_sha1_context *src = lmbedtls_sha1_check(L, 1);
  mbedtls_sha1_context *dst = (mbedtls_sha1_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha1_context));
  mbedtls_sha1_clone(dst, src);
  lmbedtls_setmeta(L, "sha1.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha1_update(lua_State *L) {
  mbedtls_sha1_context *ctx = lmbedtls_sha1_check(L, 1);
  size_t dlen;
  const unsigned char *data =  (unsigned char *) luaL_checklstring(L, 2, &dlen);
  mbedtls_sha1_update(ctx, data, dlen);
  return 0;
}

LUALIB_API int lmbedtls_sha1_finish(lua_State *L) {
  mbedtls_sha1_context *ctx = lmbedtls_sha1_check(L, 1);
  unsigned char output[20];
  mbedtls_sha1_finish(ctx, output);
  if(lua_toboolean(L, 2)) {
    lmbedtls_pushhexstring(L, output, 20);
  }
  else {
    lua_pushlstring(L, (const char *)output, 20);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha1_free(lua_State *L) {
  mbedtls_sha1_context *ctx = lmbedtls_sha1_check(L, 1);
  mbedtls_sha1_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_sha1_funcs[] = {
  { "new", lmbedtls_sha1_new },
  { "calc", lmbedtls_sha1 },
  { "__call", lmbedtls_sha1 },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_sha1_methods[] = {
  { "starts", lmbedtls_sha1_starts },
  { "clone", lmbedtls_sha1_clone },
  { "update", lmbedtls_sha1_update },
  { "finish", lmbedtls_sha1_finish },
  { "free", lmbedtls_sha1_free },
  { "__gc", lmbedtls_sha1_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_sha1_open(lua_State *L) {
  lmbedtls_createmeta(L, "sha1.ctx", lmbedtls_sha1_methods);
  lmbedtls_createmeta(L, "sha1", lmbedtls_sha1_funcs);
  lmbedtls_setmeta(L, "sha1");
  return 1;
}

