local md5 = require("mbedtls").md5
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(md5 ~= nil)
  assert(md5.class == "md5")
end)

spec:describe("test hex md5", function()
  local result = "098f6bcd4621d373cade4e832627b4f6"
  assert(result == md5("test", true))
end)

spec:describe("check instance class", function()
  local ctx = md5.new()
  assert(ctx.class == "md5.ctx")
end)

spec:describe("new, update, finish", function()
  local m = md5.new()
  m:starts()
  m:update("test")
  assert("098f6bcd4621d373cade4e832627b4f6" == m:finish(true))
end)

spec:describe("check clone", function()
  local s = md5.new()
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == md5("test1234", true))
  assert(dr == md5("test5678", true))
end)

spec:run()
collectgarbage()

