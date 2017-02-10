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



	

