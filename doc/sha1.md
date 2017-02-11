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


