mbedtls.ripemd160
==

Example
=
```lua
local ripemd160 = require("mbedtls").ripemd160

local ctx = ripemd160.new()
ctx:starts()
ctx:update("test test")
local checksum = ctx:finish(true)

```

mbedtls.ripemd160(input, [hexify])
=

* *input* (string) input
* *hexify* (boolean) Return the result as hex-string (default: false)
* _returns_ (string) string/hex-string

mbedtls.ripemd160.new()
=
Create and initalize a new ripemd160 context instance.

ripemd160:starts()
=
Setup the ripemd160 context.

ripemd160:update(input)
=

Process ripemd160 buffer.

* *input* (string)

ripemd160:finish([hexify])
=

ripemd160 final digest.

* *hexify* (boolean) - Convert the result to hex-string
* _returns_ (string) - RIPEMD160 checksum result.

ripemd160:clone()
==

Clone the state of a ripemd160 context.

* _returns_ (ripemd160) - RIPEMD160 context


