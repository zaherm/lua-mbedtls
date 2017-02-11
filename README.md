lua-mbedtls
===
Lua binding for [mbedtls](https://github.com/ARMmbed/mbedtls).


Doc
===
*mbedtls*


mbedtls.md5
==

Example
=
```lua
local md5 = require("mbedtls").md5

local ctx = md5.new()
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)

```

mbedtls.md5(input, [hexify])
=

* *input* (string) input
* *hexify* (boolean) Return the result as hex-string (default: false)
* _returns_ (string) string/hex-string

mbedtls.md5.new()
=
Create and initalize a new MD5 context instance.

md5:starts()
=
Setup the MD5 context.

md5:update(input)
=

Process MD5 buffer.

* *input* (string)

md5:finish([hexify])
=

MD5 final digest.

* *hexify* (boolean) - Convert the result to hex-string
* _returns_ (string) - MD5 checksum result.

md5:clone()
==

Clone the state of an MD5 context.

* _returns_ (md5) - MD5 context


mbedtls.sha1
==

Example
=
```lua
local sha1 = require("mbedtls").sha1

local ctx = sha1.new()
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)

```

mbedtls.sha1(input, [hexify])
=

* *input* (string) input
* *hexify* (boolean) Return the result as hex-string (default: false)
* _returns_ (string) string/hex-string

mbedtls.sha1.new()
=
Create and initalize a new SHA1 context instance.

sha1:starts()
=
Setup the SHA1 context.

sha1:update(input)
=

Process SHA1 buffer.

* *input* (string)

sha1:finish([hexify])
=

SHA1 final digest.

* *hexify* (boolean) - Convert the result to hex-string
* _returns_ (string) - SHA1 checksum result.

sha1:clone()
==

Clone the state of an SHA1 context.

* _returns_ (sha1) - SHA1 context

mbedtls.sha256
==

Example
=
```lua
local sha256 = require("mbedtls").sha256
-- sha256
local ctx = sha256.new()
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)

-- sha224
local ctx = sha256.new(true)
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)
```

mbedtls.sha256(input, [hexify], [is224])
=

* *input* (string) input
* *hexify* (boolean) Return the result as hex-string (default: false)
* *is224* (boolean) Use SHA224 (default: false)
* _returns_ (string) string/hex-string

mbedtls.sha256.new(is224)
=
Create and initalize a new SHA256 context instance.

* *is224* (boolean) Use SHA224

sha256:starts(is224)
=
Setup the SHA256 context.

* *is224* (boolean) Use SHA224

sha256:update(input)
=

Process SHA256 buffer.

* *input* (string)

sha256:finish([hexify])
=

SHA256 final digest.

* *hexify* (boolean) - Convert the result to hex-string
* _returns_ (string) - SHA256 checksum result.

sha256:clone()
==

Clone the state of an SHA256 context.

* _returns_ (sha256) - SHA256 context


mbedtls.sha512
==

Example
=
```lua
local sha512 = require("mbedtls").sha512
-- sha512
local ctx = sha512.new()
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)

-- sha385
local ctx = sha512.new(true)
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)
```

mbedtls.sha512(input, [hexify], [is384])
=

* *input* (string) input
* *hexify* (boolean) Return the result as hex-string (default: false)
* *is384* (boolean) Use SHA384 (default: false)
* _returns_ (string) string/hex-string

mbedtls.sha512.new([is384])
=
Create and initalize a new SHA384 context instance.

* *is384* (boolean - optional) Use SHA384

sha512:starts(is384)
=
Setup the SHA512 context.

* *is384* (boolean - optional) Use SHA384

sha512:update(input)
=

Process SHA512 buffer.

* *input* (string)

sha512:finish([hexify])
=

SHA512 final digest.

* *hexify* (boolean) - Convert the result to hex-string
* _returns_ (string) - SHA512 checksum result.

sha512:clone()
==

Clone the state of an SHA512 context.

* _returns_ (sha512) - SHA512 context

