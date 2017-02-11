#include "lmbedtls_sha512.h"

mbedtls_sha512_context *lmbedtls_sha512_check(lua_State *L, int index) {
  mbedtls_sha512_context *c = (mbedtls_sha512_context *) luaL_checkudata(L, index, "sha512.ctx");
  luaL_argcheck(L, c != NULL, index, "sha512.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_sha512(lua_State *L) {
  size_t ilen;
  unsigned char output[64];
  int index = lua_istable(L, 1) ? 2 : 1; //2 is used if was invoked via __call
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, index, &ilen);
  int is384 = lua_toboolean(L, index + 2);
  size_t olen = is384 == 1 ? 48 : 64;
  mbedtls_sha512(input, ilen, output, is384);

  if(lua_toboolean(L, index + 1)) {
    lmbedtls_pushhexstring(L, output, olen);
  }
  else {
    lua_pushlstring(L, (const char *)output, olen);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha512_new(lua_State *L) {
  int is384 = lua_toboolean(L, 1);
  mbedtls_sha512_context *ctx = (mbedtls_sha512_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha512_context));
  mbedtls_sha512_init(ctx);
  mbedtls_sha512_starts(ctx, is384);
  lmbedtls_setmeta(L, "sha512.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha512_starts(lua_State *L) {
  mbedtls_sha512_context *ctx = lmbedtls_sha512_check(L, 1);
  int is384 = lua_toboolean(L, 2);
  mbedtls_sha512_starts(ctx, is384);
  return 0;
}

LUALIB_API int lmbedtls_sha512_clone(lua_State *L) {
  mbedtls_sha512_context *src = lmbedtls_sha512_check(L, 1);
  mbedtls_sha512_context *dst = (mbedtls_sha512_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha512_context));
  mbedtls_sha512_clone(dst, src);
  lmbedtls_setmeta(L, "sha512.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha512_update(lua_State *L) {
  mbedtls_sha512_context *ctx = lmbedtls_sha512_check(L, 1);
  size_t dlen;
  const unsigned char *data =  (unsigned char *) luaL_checklstring(L, 2, &dlen);
  mbedtls_sha512_update(ctx, data, dlen);
  return 0;
}

LUALIB_API int lmbedtls_sha512_finish(lua_State *L) {
  mbedtls_sha512_context *ctx = lmbedtls_sha512_check(L, 1);
  size_t olen = ctx->is384 == 1 ? 48 : 64;
  unsigned char output[olen];
  mbedtls_sha512_finish(ctx, output);
  if(lua_toboolean(L, 2)) {
    lmbedtls_pushhexstring(L, output, olen);
  }
  else {
    lua_pushlstring(L, (const char *)output, olen);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha512_free(lua_State *L) {
  mbedtls_sha512_context *ctx = lmbedtls_sha512_check(L, 1);
  mbedtls_sha512_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_sha512_funcs[] = {
  { "new", lmbedtls_sha512_new },
  { "calc", lmbedtls_sha512 },
  { "__call", lmbedtls_sha512 },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_sha512_methods[] = {
  { "starts", lmbedtls_sha512_starts },
  { "clone", lmbedtls_sha512_clone },
  { "update", lmbedtls_sha512_update },
  { "finish", lmbedtls_sha512_finish },
  { "free", lmbedtls_sha512_free },
  { "__gc", lmbedtls_sha512_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_sha512_open(lua_State *L) {
  lmbedtls_createmeta(L, "sha512.ctx", lmbedtls_sha512_methods);
  lmbedtls_createmeta(L, "sha512", lmbedtls_sha512_funcs);
  lmbedtls_setmeta(L, "sha512");
  return 1;
}

