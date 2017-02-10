local M = {}
M.__index = M

function M.new()
  local m = {}
  setmetatable(m, M)
  m.tests = {}
  return m
end

function M:describe(desc, func)
  self.tests[#self.tests + 1] = {
    desc = desc,
    func = func
  }
end

function M:run()
  local ok
  local results = {}
  for i, s in ipairs(self.tests) do
    ok, _ = pcall(s.func)
    results[i] = { desc = s.desc, result = ok and "pass" or "fail" }
  end
  print("> spec results: ")
  for i, res in ipairs(results) do
    print("\t- spec["..tostring(i).."] "..tostring(res.desc).." result='"..res.result.."'")
  end
end

return M
