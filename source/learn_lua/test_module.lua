local m=require("module")

print(m.constant)

m.func3()

function load_func1()
local mc=require("mymodule")
print("sum of 1 2:", mc.MySum(1,2))
end
function load_func2()
local path="./mymodule.so"
local f = assert(package.loadlib(path, "l_hello"))
f()
print("done")
end

load_func1()

