local aes = require("mbedtls").aes
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(aes ~= nil)
  assert(aes.class == "aes")
end)

spec:describe("encrypt/decrypt - crypt_cfb8", function()
  local enc, dec
  local e = aes.new()
  local d = aes.new()
  local iv = "abcdabcdabcdabcd"
  local plain = "test is a test"
  print(string.len("aaaabbbbccccdddd")*8)
  e:setkey_enc("aaaabbbbccccdddd")

  d:setkey_enc("aaaabbbbccccdddd")
 -- d:setkey_dec("aaaabbbbccccdddd")

  local encs = {}
  for i = 1, 10 do
    plain = string.rep("*", i)
    encs[#encs + 1] = e:crypt_cfb8("encrypt", iv, plain)
  end
  -- reset iv value
  local div = "abcda".."bcdabcdabcd"
  for i, enc in ipairs(encs) do
    plain = string.rep("*", i)
    dec = d:crypt_cfb8("decrypt", div, enc)
    assert(dec == plain)
  end
end)


spec:run()
collectgarbage()

