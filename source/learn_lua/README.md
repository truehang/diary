# lua 引入模块

## 引入lua模块

见test_module.lua

运行

```bash
lua test_module.lua
```

## 引入C编译的so共享库

### 自己写的库

1. 编译C

```bash
# 依赖lua5.1
gcc -fPIC -shared -o my_module.so my_module.c -I/usr/include/lua5.1 -llua5.1 -g
```

    2. 引入该so库并调用其中的函数

```bash
# 在运行之前，要添加当前路径共享库到lua的查找路径中，两个分号代表LUA_CPATH原来的数值
export LUA_CPATH="./?.so;;"
lua test_my_module.lua
```

### 第三方库

lua要计算包含中文的字符串长度，需要支持utf-8的库。这里使用第三方的库，见luautf8下。

```bash
# 可以先阅读luautf8的说明
cd luautf8
gcc -fPIC -shared -o lutf8lib.so lutf8lib.c -I/usr/include/lua5.1 -llua5.1
cd ..
./hello_world.lua
```
