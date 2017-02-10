#include "lmbedtls_sha256.h"

mbedtls_sha256_context *lmbedtls_sha256_check(lua_State *L, int index) {
  mbedtls_sha256_context *c = (mbedtls_sha256_context *) luaL_checkudata(L, index, "sha256.ctx");
  luaL_argcheck(L, c != NULL, index, "sha256.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_sha256(lua_State *L) {
  size_t ilen;
  unsigned char output[32];
  int index = lua_istable(L, 1) ? 2 : 1; //2 is used if was invoked via __call
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, index, &ilen);
  int is224 = lua_toboolean(L, index + 2);
  size_t olen = is224 == 1 ? 28 : 32;
  mbedtls_sha256(input, ilen, output, is224);

  if(lua_toboolean(L, index + 1)) {
    lmbedtls_pushhexstring(L, output, olen);
  }
  else {
    lua_pushlstring(L, (const char *)output, olen);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha256_new(lua_State *L) {
  int is224 = lua_toboolean(L, 1);
  mbedtls_sha256_context *ctx = (mbedtls_sha256_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha256_context));
  mbedtls_sha256_init(ctx);
  mbedtls_sha256_starts(ctx, is224);
  lmbedtls_setmeta(L, "sha256.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha256_starts(lua_State *L) {
  mbedtls_sha256_context *ctx = lmbedtls_sha256_check(L, 1);
  int is224 = lua_toboolean(L, 2);
  mbedtls_sha256_starts(ctx, is224);
  return 0;
}

LUALIB_API int lmbedtls_sha256_clone(lua_State *L) {
  mbedtls_sha256_context *src = lmbedtls_sha256_check(L, 1);
  mbedtls_sha256_context *dst = (mbedtls_sha256_context *)
                                lua_newuserdata(L, sizeof(mbedtls_sha256_context));
  mbedtls_sha256_clone(dst, src);
  lmbedtls_setmeta(L, "sha256.ctx");
  return 1;
}

LUALIB_API int lmbedtls_sha256_update(lua_State *L) {
  mbedtls_sha256_context *ctx = lmbedtls_sha256_check(L, 1);
  size_t dlen;
  const unsigned char *data =  (unsigned char *) luaL_checklstring(L, 2, &dlen);
  mbedtls_sha256_update(ctx, data, dlen);
  return 0;
}

LUALIB_API int lmbedtls_sha256_finish(lua_State *L) {
  mbedtls_sha256_context *ctx = lmbedtls_sha256_check(L, 1);
  size_t olen = ctx->is224 == 1 ? 28 : 32;
  unsigned char output[olen];
  mbedtls_sha256_finish(ctx, output);
  if(lua_toboolean(L, 2)) {
    lmbedtls_pushhexstring(L, output, olen);
  }
  else {
    lua_pushlstring(L, (const char *)output, olen);
  }
  return 1;
}

LUALIB_API int lmbedtls_sha256_free(lua_State *L) {
  mbedtls_sha256_context *ctx = lmbedtls_sha256_check(L, 1);
  mbedtls_sha256_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_sha256_funcs[] = {
  { "new", lmbedtls_sha256_new },
  { "calc", lmbedtls_sha256 },
  { "__call", lmbedtls_sha256 },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_sha256_methods[] = {
  { "starts", lmbedtls_sha256_starts },
  { "clone", lmbedtls_sha256_clone },
  { "update", lmbedtls_sha256_update },
  { "finish", lmbedtls_sha256_finish },
  { "free", lmbedtls_sha256_free },
  { "__gc", lmbedtls_sha256_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_sha256_open(lua_State *L) {
  lmbedtls_createmeta(L, "sha256.ctx", lmbedtls_sha256_methods);
  lmbedtls_createmeta(L, "sha256", lmbedtls_sha256_funcs);
  lmbedtls_setmeta(L, "sha256");
  return 1;
}

