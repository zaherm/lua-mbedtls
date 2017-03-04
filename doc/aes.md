mbedtls.aes
==

Example
=
```lua
local aes = require("mbedtls").aes

local ctx = aes.new()

```

mbedtls.aes.new()
=
Create and initialize a new AES context instance.

aes:setkey_enc(key, keybits)
=
Set AES encryption key schedule.

* *key* (string) - encryption key
* *keybits* (number) - must be 128, 192, 256

aes:setkey_dec(key, keybits)
=
Set AES decryption key schedule.

* *key* (string) - encryption key
* *keybits* (number) - must be 128, 192, 256

aes:crypt_cfb8(mode, iv, input)
=
Set AES decryption key schedule.

* *mode* (string) - should be "encrypt" or "decrypt"
* *iv* (string) - initialization vector (length: 16)
* *input* (string) - input data
* _returns_ (string) - encrypted/decrypted data






