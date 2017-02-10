local sha256 = require("mbedtls").sha256
local spec = require("test.spec").new()

spec:describe("check class", function()
  assert(sha256 ~= nil)
  assert(sha256.class == "sha256")
end)

spec:describe("test hex sha256", function()
  local result = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"
  assert(result == sha256("test", true))
end)

spec:describe("test hex sha224", function()
  local result = "90a3ed9e32b2aaf4c61c410eb925426119e1a9dc53d4286ade99a809"
  assert(result == sha256("test", true, true))
end)

spec:describe("check instance class", function()
  local ctx = sha256.new()
  assert(ctx.class == "sha256.ctx")
end)

spec:describe("sha256: new, update, finish", function()
  local m = sha256.new()
  m:starts()
  m:update("test")
  assert("9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08" == m:finish(true))
end)

spec:describe("sha224: new, update, finish", function()
  local m = sha256.new()
  m:starts(true)
  m:update("test")
  assert("90a3ed9e32b2aaf4c61c410eb925426119e1a9dc53d4286ade99a809" == m:finish(true))
end)

spec:describe("sha224: new(true), update, finish", function()
  local m = sha256.new(true)
  m:update("test")
  assert("90a3ed9e32b2aaf4c61c410eb925426119e1a9dc53d4286ade99a809" == m:finish(true))
end)

spec:describe("sha256: check clone", function()
  local s = sha256.new()
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == sha256("test1234", true))
  assert(dr == sha256("test5678", true))
end)

spec:describe("sha224: check clone", function()
  local s = sha256.new(true) --sha224
  s:update("test")
  local d = s:clone()
  s:update("5678")
  d:update("1234")
  local sr = d:finish(true)
  local dr = s:finish(true)
  assert(sr == sha256("test1234", true, true))
  assert(dr == sha256("test5678", true, true))
end)

spec:run()
collectgarbage()

