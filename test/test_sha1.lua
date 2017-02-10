local sha1 = require("mbedtls").sha1
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(sha1 ~= nil)
  assert(sha1.class == "sha1")
end)

spec:describe("test hex sha1", function()
  local result = "a94a8fe5ccb19ba61c4c0873d391e987982fbbd3"
  assert(result == sha1("test", true))
end)

spec:describe("check instance class", function()
  local ctx = sha1.new()
  assert(ctx.class == "sha1.ctx")
end)

spec:describe("new, update, finish", function()
  local m = sha1.new()
  m:starts()
  m:update("test")
  assert("a94a8fe5ccb19ba61c4c0873d391e987982fbbd3" == m:finish(true))
end)

spec:describe("check clone", function()
  local s = sha1.new()
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == sha1("test1234", true))
  assert(dr == sha1("test5678", true))
end)

spec:run()
collectgarbage()

