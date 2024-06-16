#include <lauxlib.h>
#include <lua.h>

// 定义 l_sum 函数
static int l_sum(lua_State *L) {
    int a = lua_tointeger(L, 1); // 获取第一个参数
    int b = lua_tointeger(L, 2); // 获取第二个参数
    lua_pushinteger(L, a + b);   // 将结果压入栈中
    return 1;                    // 返回结果数量
}

// 定义 l_split 函数
static int l_split(lua_State *L) {
    size_t len;
    const char *str = lua_tolstring(L, 1, &len); // 获取第一个参数（字符串）
    const char *sep = lua_tostring(L, 2);        // 获取第二个参数（分隔符）
    int lastpos = -1, i = 0, key = 1;

    lua_newtable(L); // 创建一个新的表
    for (; i < len; i++) {
        if (str[i] == *sep) {
            lua_pushlstring(L, str + lastpos + 1, i - lastpos - 1); // 将子串压入栈中
            lua_rawseti(L, -2, key); // 将子串插入表中
            lastpos = i;
            key++;
        }
    }
    // 处理最后一个子串
    lua_pushlstring(L, str + lastpos + 1, len - lastpos - 1);
    lua_rawseti(L, -2, key);
    return 1; // 返回表
}

// 定义 l_array_sum 函数
static int l_array_sum(lua_State *L) {
    if (!lua_istable(L, 1)) { // 检查参数是否为表
        lua_pushnil(L);
        return 1;
    }
    int sum = 0;
    int len = lua_objlen(L, 1); // 获取表的长度

    for (int i = 1; i <= len; i++) {
        lua_rawgeti(L, 1, i);
        sum += lua_tointeger(L, -1);
    }

    lua_pushinteger(L, sum);
    float aver = (float)sum / len;
    lua_pushnumber(L, aver);

    return 2; // 返回两个值：总和和平均值
}

// 定义 l_array_map 函数
static int l_array_map(lua_State *L) {
    if (!lua_istable(L, 1) || !lua_isfunction(L, 2)) { // 检查参数类型
        lua_pushnil(L);
        return 1;
    }
    int len = lua_objlen(L, 1);

    for (int i = 1; i <= len; i++) {
        lua_pushvalue(L, 2);
        lua_rawgeti(L, 1, i);
        lua_call(L, 1, 1);
        lua_rawseti(L, 1, i);
    }
    lua_pushvalue(L, 1);
    return 1;
}

// 声明一个 luaL_Reg 结构体数组
static const struct luaL_Reg funcs[] = {
    {"sum", l_sum},
    {"split", l_split},
    {"array_sum", l_array_sum},
    {"array_map", l_array_map},
    {NULL, NULL} // 数组结束标记
};

// 模块初始化函数
int luaopen_my_module(lua_State *L) {
    luaL_register(L, "my_module", funcs); // 第二个参数要和你的模块名一致
    return 1;
}

