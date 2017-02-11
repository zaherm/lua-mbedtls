#include "lmbedtls_base64.h"

/*
 * int mbedtls_base64_encode( unsigned char *dst, size_t dlen, size_t *olen,
const unsigned char *src, size_t slen );
*/
LUALIB_API int lmbedtls_base64_encode(lua_State *L) {
  size_t slen, olen, dlen;
  const unsigned char *src = (unsigned char *) luaL_checklstring(L, 1, &slen);
  /* obtain the expected length */
  mbedtls_base64_encode(NULL, 0, &dlen, src, slen);
  unsigned char dst[dlen];
  mbedtls_base64_encode(dst, dlen, &olen, src, slen);
  lua_pushlstring(L, (const char *)dst, olen);
  return 1;
}

/* int mbedtls_base64_decode( unsigned char *dst, size_t dlen, size_t *olen,
const unsigned char *src, size_t slen );*/

LUALIB_API int lmbedtls_base64_decode(lua_State *L) {
  size_t slen, olen, dlen;
  const unsigned char *src = (unsigned char *) luaL_checklstring(L, 1, &slen);
  /* obtain the expected length */
  mbedtls_base64_decode(NULL, 0, &dlen, src, slen);
  unsigned char dst[dlen];
  mbedtls_base64_decode(dst, dlen, &olen, src, slen);
  lua_pushlstring(L, (const char *)dst, olen);
  return 1;
}

static luaL_Reg lmbedtls_base64_funcs[] = {
  { "encode", lmbedtls_base64_encode },
  { "decode", lmbedtls_base64_decode },
  { NULL, NULL }
};

LUALIB_API int lmbedtls_base64_open(lua_State *L) {
  lmbedtls_createmeta(L, "base64", lmbedtls_base64_funcs);
  lmbedtls_setmeta(L, "base64");
  return 1;
}

