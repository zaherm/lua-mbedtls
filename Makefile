UNAME := $(shell uname)
all-tests := $(basename $(wildcard test/test_*.lua))

LIB_PATH= /usr/lib64
INC_PATH= /usr/include
BIN_PATH= /usr/bin
LUA_LIB= -L$(LIB_PATH) -llua
LUA_INC= -I$(INC_PATH) -I$(INC_PATH)/lua
MBEDTLS_LIB= -lmbedtls
MBEDTLS_INC= -I$(INC_PATH)/mbedtls
EXTRACFLAGS= -std=c99 -undefined -fPIC

# change these based on your installation
ifeq ($(UNAME), Darwin)
	LIB_PATH= /usr/local/lib
	INC_PATH= /usr/local/include
	BIN_PATH= /usr/local/bin
	LUA_LIB= -L$(LIB_PATH) -llua5.1
	LUA_INC= -I$(INC_PATH) -I$(INC_PATH)/lua-5.1
	MBEDTLS_LIB= -lmbedtls
	MBEDTLS_INC= -I$(INC_PATH)/mbedtls
	EXTRACFLAGS= -std=c99 -undefined dynamic_lookup -fPIC
endif


INC= $(LUA_INC) $(MBEDTLS_INC)
LIB= $(LUA_LIB) $(MBEDTLS_LIB)
WARN= -Wall
CFLAGS= -O2 $(WARN) $(INC)

LIBNAME= mbedtls
T= $(LIBNAME).so
OBJS= src/l$(LIBNAME)_aux.o \
			src/l$(LIBNAME)_md5.o \
			src/l$(LIBNAME)_sha1.o \
			src/l$(LIBNAME).o

all: $T

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

$T:	$(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(EXTRACFLAGS) -o $@ -shared $(OBJS)

clean:
	rm -f $T $(OBJS)

clean-all:
	rm -f $T $(OBJS)

tests: $(all-tests)

test/test_%: $T
	lua $@.lua

test: clean all tests

install: $(TARGET)


