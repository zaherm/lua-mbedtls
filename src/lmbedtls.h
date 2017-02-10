#ifndef LMBEDTLS_H
#define LMBEDTLS_H

#include "lmbedtls_aux.h"
#include "lmbedtls_md5.h"

#define LMBEDTLS_VERSION "lua-mbedtls 0.0.1"
#define LMBEDTLS_COPYRIGHT "Copyright (c) 2017, Zaher Marzuq"
#define LMBEDTLS_DESCRIPTION "mbedtls binding for Lua"

static const luaL_Reg lmbedtls_mods[] = {
  { "md5", lmbedtls_md5_open },
  { NULL, NULL }
};

static const luaL_Reg lmbedtls_funcs[] = {
  { NULL, NULL }
};

#endif

