#ifndef LMBEDTLS_H
#define LMBEDTLS_H

#include "lmbedtls_aux.h"
#include "lmbedtls_md5.h"
#include "lmbedtls_sha1.h"
#include "lmbedtls_sha256.h"
#include "lmbedtls_sha512.h"
#include "lmbedtls_ripemd160.h"
#include "lmbedtls_base64.h"
#include "lmbedtls_aes.h"

#define LMBEDTLS_VERSION "lua-mbedtls 0.0.1"
#define LMBEDTLS_COPYRIGHT "Copyright (c) 2017, Zaher Marzuq"
#define LMBEDTLS_DESCRIPTION "mbedtls binding for Lua"

static const luaL_Reg lmbedtls_mods[] = {
  { "md5", lmbedtls_md5_open },
  { "sha1", lmbedtls_sha1_open },
  { "sha256", lmbedtls_sha256_open },
  { "sha512", lmbedtls_sha512_open },
  { "ripemd160", lmbedtls_ripemd160_open },
  { "base64", lmbedtls_base64_open },
  { "aes", lmbedtls_aes_open },
  { NULL, NULL }
};

static const luaL_Reg lmbedtls_funcs[] = {
  { NULL, NULL }
};

#endif

