#include "lmbedtls_aes.h"

int lmbedtls_aes_crypt_mode_values[] = {
  MBEDTLS_AES_ENCRYPT, MBEDTLS_AES_DECRYPT, -1
};

const char *const lmbedtls_aes_crypt_mode_keys[] = {
  "encrypt", "decrypt", NULL
};

mbedtls_aes_context *lmbedtls_aes_check(lua_State *L, int index) {
  mbedtls_aes_context *c = (mbedtls_aes_context *) luaL_checkudata(L, index, "aes.ctx");
  luaL_argcheck(L, c != NULL, index, "aes.ctx expected");
  return c;
}

LUALIB_API int lmbedtls_aes_new(lua_State *L) {
  mbedtls_aes_context *ctx = (mbedtls_aes_context *)
                                lua_newuserdata(L, sizeof(mbedtls_aes_context));
  mbedtls_aes_init(ctx);
  lmbedtls_setmeta(L, "aes.ctx");
  return 1;
}

LUALIB_API int lmbedtls_aes_setkey_enc(lua_State *L) {
  mbedtls_aes_context *ctx = lmbedtls_aes_check(L, 1);
  size_t keybits;
  const unsigned char *key = (unsigned char *) luaL_checklstring(L, 2, &keybits);
  int ret = mbedtls_aes_setkey_enc(ctx, key, keybits * 8);
  if(ret) {
    lmbedtls_error(L, "aes invalid key length");
  }
  return 1;
}

LUALIB_API int lmbedtls_aes_setkey_dec(lua_State *L) {
  mbedtls_aes_context *ctx = lmbedtls_aes_check(L, 1);
  size_t keybits;
  const unsigned char *key = (unsigned char *) luaL_checklstring(L, 2, &keybits);
  int ret = mbedtls_aes_setkey_dec(ctx, key, keybits * 8);
  if(ret) {
    lmbedtls_error(L, "aes invalid key length");
  }
  return 1;
}

LUALIB_API int lmbedtls_aes_crypt_cfb8(lua_State *L) {
  mbedtls_aes_context *ctx = lmbedtls_aes_check(L, 1);
  int mode = lmbedtls_checkoption(L, 2, "encrypt", lmbedtls_aes_crypt_mode_keys,
      lmbedtls_aes_crypt_mode_values);
  const char *iv = lua_tostring(L, 3);
  size_t length;
  const unsigned char *input = (unsigned char *) luaL_checklstring(L, 4, &length);
  unsigned char output[length];
  int ret = mbedtls_aes_crypt_cfb8(ctx, mode, length, (unsigned char *)iv, input, output);
  if(!ret) {
    lua_pushlstring(L, (const char *)output, length);
  }
  else {
    lua_pushnil(L);
  }
  return 1;
}

LUALIB_API int lmbedtls_aes_free(lua_State *L) {
  mbedtls_aes_context *ctx = lmbedtls_aes_check(L, 1);
  mbedtls_aes_free(ctx);
  return 0;
}

static luaL_Reg lmbedtls_aes_funcs[] = {
  { "new", lmbedtls_aes_new },
  { NULL, NULL }
};

static luaL_Reg lmbedtls_aes_methods[] = {
  { "free", lmbedtls_aes_free },
  { "setkey_enc", lmbedtls_aes_setkey_enc },
  { "setkey_dec", lmbedtls_aes_setkey_dec },
  { "crypt_cfb8", lmbedtls_aes_crypt_cfb8 },
  { "__gc", lmbedtls_aes_free },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_aes_open(lua_State *L) {
  lmbedtls_createmeta(L, "aes.ctx", lmbedtls_aes_methods);
  lmbedtls_createmeta(L, "aes", lmbedtls_aes_funcs);
  lmbedtls_setmeta(L, "aes");
  return 1;
}

