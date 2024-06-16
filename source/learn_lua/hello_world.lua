#!/usr/bin/lua
package.cpath = package.cpath .. ";./luautf8/?.so"
local utf8 = require 'lutf8lib'

print("Hello World!")
print("www.runoob.com")
html = [[
<html>
<head></head>
<body>
    <a href="http://www.runoob.com/">菜鸟教程</a>
</body>
</html>
]]
print(html)
function testFun(tab,fun)
        for k ,v in pairs(tab) do
                print(fun(k,v));
        end
end


tab={key1="val1",key2="val2"};
testFun(tab,
function(key,val)--匿名函数
        return key.."="..val;
end
);
function add(...)
local s = 0
  for i, v in ipairs{...} do   --> {...} 表示一个由所有变长参数构成的数组
    s = s + v
  end
  return s
end
print(add(3,4,5,6,7))  --->25
function average(...)
   result = 0
   local arg={...}    --> arg 为一个表，局部变量
   for i,v in ipairs(arg) do
      result = result + v
   end
   print("总共传入 " .. #arg .. " 个数")
   return result/#arg
end

print("平均值为",average(10,5,3,4,5,6))
local myString = "Hello, 世界!"

-- 计算字符串的长度（字符个数）
local length1 = utf8.len(myString)
print(length1) -- 输出 10
-- string.len 函数会导致结果不准确
local length2 = string.len(myString)
print(length2) -- 输出 14

local myArray = {1, 2, 3, 4, 5}
local lengtharr = #myArray
print(lengtharr) -- 输出 5

for i = 1, #myArray do
    print(myArray[i])
end

array = {"Google", "Runoob"}
for key,value in ipairs(array) do
    print(key, value)
end

fruits = {"banana", "orange", "apple"}
-- 返回 table 连接后的字符串
print("连接后的字符串 ", table.concat(fruits))
-- 指定连接字符
print("连接后的字符串 ", table.concat(fruits, ", "))
-- 指定索引来连接 table
print("连接后的字符串 ", table.concat(fruits, ", ", 2, 3))
-- 插入元素
table.insert(fruits, "mango")
print("索引为 4 的元素为 ", fruits[4])
-- 在索引 2 的位置插入
table.insert(fruits, 2, "grapes")
print("索引为 2 的元素为 ", fruits[2])
print("移除后的元素 ", fruits[5])
-- 移除元素
print("移除的元素为 ", table.remove(fruits))
-- 输出移除后的元素
print("移除后的元素 ", fruits[5])
