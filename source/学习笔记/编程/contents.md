# `-fsanitize`参数
`-fsanitize`参数是`g++`编译器的一个参数，用于检查运行时错误。`-fsanitize`参数有以下几种：
- `-fsanitize=undefined`：检查运行时未定义行为
- `-fsanitize=address`：检查内存泄漏

## `-fsanitize=undefined`参数
`g++`编译时使用`-fsanitize=undefined`参数，可以检查运行时未定义行为，譬如数组越界、空指针引用、整数溢出等。如下代码会报错：
### 数组越界
```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v;
    v[0] = 1;
    cout << v[0] << endl;
    return 0;
}
```
输出：
```
/usr/include/c++/11/bits/stl_vector.h:1046:34: runtime error: reference binding to null pointer of type 'value_type'
a1.cc:6:12: runtime error: store to null pointer of type 'value_type'
段错误 (核心已转储)

```
### 空指针引用
```cpp
#include <iostream>
using namespace std;
int main() {
    int *p = nullptr;
    cout << *p << endl;
    return 0;
}
```
输出：
```
a2.cc:5:12: runtime error: load of null pointer of type 'int'
段错误 (核心已转储)
```
### 整数溢出
```cpp
#include <iostream>
using namespace std;
int main() {
    int a = 0x7fffffff;
    cout << a + 1 << endl;
    return 0;
}
```
输出：
```
a3.cc:5:12: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
2147483648
```
## `-fsanitize=address`参数
`g++`编译时使用`-fsanitize=address`参数，可以检查运行时内存泄漏。如下代码会报错：
```cpp
#include <iostream>
using namespace std;
int main() {
    int *p = new int;
    return 0;
}
```
输出：
```

=================================================================
==385048==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x749ca78b61e7 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:99
    #1 0x58360fdc225e in main (/home/zhouhang/Code/doc/source/学习笔记/编程/a.out+0x125e)
    #2 0x749ca7029d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```
