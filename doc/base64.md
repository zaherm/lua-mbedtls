mbedtls.base64
==

Example
=
```lua
local base64 = require("mbedtls").base64

local encoded = base64.encode("test")
local decode = base64.decode("dGVzdA==")
```

base64.encode(input)
=

* *input* (string) input
* _returns_ (string) base64-encoded string

base64.decode(input)
=

* *input* (string) base64-encoded input
* _returns_ (string) string


