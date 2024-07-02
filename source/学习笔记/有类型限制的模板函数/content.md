# 有类型限制的模板函数
一般的模板函数，不会对类型进行限定，但是有的时候我们的函数处理过程中，只能处理部分的类型，此时需要对模板的类进行限定。
这里的一个应用场景就是我们在lua c编码中，获取一个数组。不管是从栈中读取，还是写入到栈中，数组元素的类型都是固定的几种，bool，整型，浮点型。
这里我们就可以用到有类型限制的模板函数。  
代码的枝干如下：
```cpp
template <typename T, typename = typename std::enable_if<支持的类型,
                                                         void>::type>
int func(T && a) {
    // 根据T的类型进行不同的处理
    return 1;
}

```

实际函数：
```cpp
// 支持整形（包括bool）和浮点型
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value,
                                                         void>::type>
int setVectorToStack(lua_State *lua, const std::vector<T> &vector) {
    if (vector.empty()) return 0;
    lua_createtable(lua, vector.size(), 0);
    for (int i = 0; i < vector.size(); i++) {
        if (std::is_same<T, int>::value) {
            lua_pushinteger(lua, vector[i]);
        } else if (std::is_same<T, bool>::value) {
            lua_pushboolean(lua, vector[i]);
        } else if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            lua_pushnumber(lua, vector[i]);
        }
        lua_rawseti(lua, -2, i + 1);
    }
    return 1;
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value,
                                                         void>::type>
int getVectorFromStack(lua_State *lua, std::vector<T> &vector, int index) {
    // 确保栈顶是一个表（数组）
    luaL_checktype(lua, index, LUA_TTABLE);
    int szArr = luaL_len(lua, index);
    vector.clear();

    for (int i = 1; i <= szArr; i++) {
        // 使用lua_geti获取下标的元素，推送到栈顶
        lua_geti(lua, index, i);
        if (lua_isinteger(lua, -1)) {
            vector.push_back(static_cast<T>(lua_tointeger(lua, -1)));
        } else if (lua_isboolean(lua, -1)) {
            vector.push_back(static_cast<T>(lua_toboolean(lua, -1)));
        } else if (lua_isnumber(lua, -1)) {
            vector.push_back(static_cast<T>(lua_tonumber(lua, -1)));
        }
        lua_pop(lua, 1);
    }
    return 1;
}
```