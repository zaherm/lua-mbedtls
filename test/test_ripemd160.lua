local ripemd160 = require("mbedtls").ripemd160
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(ripemd160 ~= nil)
  assert(ripemd160.class == "ripemd160")
end)

spec:describe("test hex ripemd160", function()
  local result = "5e52fee47e6b070565f74372468cdc699de89107"
  assert(result == ripemd160("test", true))
end)

spec:describe("check instance class", function()
  local ctx = ripemd160.new()
  assert(ctx.class == "ripemd160.ctx")
end)

spec:describe("new, update, finish", function()
  local m = ripemd160.new()
  m:starts()
  m:update("test")
  assert("5e52fee47e6b070565f74372468cdc699de89107" == m:finish(true))
end)

spec:describe("check clone", function()
  local s = ripemd160.new()
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == ripemd160("test1234", true))
  assert(dr == ripemd160("test5678", true))
end)

spec:run()
collectgarbage()

