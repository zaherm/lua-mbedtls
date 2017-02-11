local sha512 = require("mbedtls").sha512
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(sha512 ~= nil)
  assert(sha512.class == "sha512")
end)

spec:describe("test hex sha512", function()
  local result = "ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff"
  assert(result == sha512("test", true))
end)

spec:describe("test hex sha384", function()
  local result = "768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9"
  assert(result == sha512("test", true, true))
end)

spec:describe("check instance class", function()
  local ctx = sha512.new()
  assert(ctx.class == "sha512.ctx")
end)

spec:describe("sha512: new, update, finish", function()
  local m = sha512.new()
  m:starts()
  m:update("test")
  assert("ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff" == m:finish(true))
end)

spec:describe("sha384: new, update, finish", function()
  local m = sha512.new()
  m:starts(true)
  m:update("test")
  assert("768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9" == m:finish(true))
end)

spec:describe("sha384: new(true), update, finish", function()
  local m = sha512.new(true)
  m:update("test")
  assert("768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9" == m:finish(true))
end)

spec:describe("sha512: check clone", function()
  local s = sha512.new()
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == sha512("test1234", true))
  assert(dr == sha512("test5678", true))
end)

spec:describe("sha384: check clone", function()
  local s = sha512.new(true) --sha384
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == sha512("test1234", true, true))
  assert(dr == sha512("test5678", true, true))
end)

spec:run()
collectgarbage()

