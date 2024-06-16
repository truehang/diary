local clib = require "my_module"
--local clib = require "clib"

local s = clib.sum(3, 99)
print(s)

print("---------------------")

local str = "aaa,bbbb,cccc,dddd,eeee"
local arr = clib.split(str, ",")

for i = 1, #arr do
        print(arr[i])
end

print("---------------------")

local arr1 = {1, 2, 3, 10}
local sum = clib.array_sum(arr1)
print("sum=", sum)

print("---------------------")

local function double(num)
        return num * 2
end
local arr2 = {1, 2, 3, 4, 5}
local res = clib.array_map(arr2, double)

for i = 1, #res do
        print(res[i])
end
