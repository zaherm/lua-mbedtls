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
  local stats = { failed = 0, passed = 0 }
  for i, s in ipairs(self.tests) do
    ok, _ = pcall(s.func)
    results[i] = { desc = s.desc, result = ok and "pass" or "fail", err = _ }
    if not ok then
      stats.failed = stats.failed + 1
    else
      stats.passed = stats.passed + 1
    end
  end
  print(string.format("> spec results: passed = %d, failed = %d", stats.passed, stats.failed))
  for i, res in ipairs(results) do
    print("\t- spec["..tostring(i).."] "..tostring(res.desc).." result='"..res.result.."', err='"..tostring(res.err).."'")
  end
end

return M
