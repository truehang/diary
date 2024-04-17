# C++输出中文字符

## 如何表示中文： 使用`L"可以有汉字"`的形式

首先我们知道中文肯定不能用char 数组来表示，那么如何表示呢，使用宽字符类型wchar_t数组来表示。

通常我们在双（或者单）引号前面加上一些前缀就可以指示双（或者单）引号中的字符是哪种类型的字符。

| 前缀  | 含义                       | 类型       |
| --- | ------------------------ | -------- |
| u   | Unicode 16 字符            | char16_t |
| U   | Unicode 32 字符            | char32_t |
| L   | 宽字符                      | wchar_t  |
| u8  | utf-8(只能在字符串前面加，不能单独字符加) | char     |

对于我们想要的中文输出来说，使用wchar_t即可，[wchar_t在windows下是UCS-2（16位），wchar_t在非windows平台是UTF-32（32位）](https://en.cppreference.com/w/cpp/locale/wbuffer_convert)。

假如我们有一个中文字符串`L"你好"`，那我们应该如何输出到屏幕上。

## 如何输出：使用`wcout`输出

cout不能应付wchar_t的字符串，只能输出char的字符串（utf-8），我们使用与wchar_t匹配的wcout进行输出，这样输出：`wcout << L"哈哈";`

Linux下我们测得char32_t和wchar_t长度相同，都是4字节，直接让wcout输出char32_t字符串却不行`wcout << U"哈哈不可以";`。另外说一句wcout可以直接输出char 数组，因为可以从char *构造wstring对象。

另外需要注意，一开始要本地化设置（zh_CN.UTF-8）才能输出中文，而且cout和wcout不能混用，只能用一个。

以下就是一些测试的程序。

```cpp
#include <iostream>
#include <locale> // 包含头文件以使用 setlocale 函数
#include <string>
#include <codecvt> // 包含头文件以使用 std::wstring_convert 和 std::codecvt_utf8
#include <iomanip> // 包含头文件以使用 std::hex 和 std::setw
int main() {
    // 设置程序的本地化环境为系统默认设置
    setlocale(LC_ALL, "");
    const wchar_t* str = L"Hello, 世界";

    // 遍历字符串并输出每个字符的UTF编码值
    for (size_t i = 0; str[i] != L'\0'; ++i) {
        std::wcout << "Character '" << str[i] << "' has encoding value: U+" \
		<< std::setw(4) << std::setfill<wchar_t>('0') << std::hex << static_cast<int>(str[i]) << std::endl;
    }

    // 获取当前本地化名称并转换为 std::string
    std::string localeName = std::locale("").name();
    
    // 我们先用cout输出，因为string类型是一个普通字符串，每个元素类型为char
    std::cout << "From cout, current locale: " << localeName << std::endl;

    // 事后我们知道，cout这里没有输出，因为wcout已经输出过了，cout不能和wcout混用

    // 接着我们使用wcout输出本地化名称，顺便输出一些中文
    // 首先我们使用 std::codecvt 进行字符转换
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wstr = conv.from_bytes(localeName);
    // 输出宽字符
    std::wcout << L"来自 wcout，当前的本地化名称：" << wstr << std::endl;
    // 下面这种方式不行，wcout不能输出string对象
    // std::wcout << L"来自 wcout，当前的本地化名称：" << localeName << std::endl;
    // 下面这种方式是可行的，因为会为char *字符串生成一个std::wstring对象，当然前面的wchar_t *字符串也是如此
    std::wcout << L"来自 wcout，当前的本地化名称(c_str方式)：" << localeName.c_str() << std::endl;

    // char32_t 和wchar_t的大小
    std::wcout << "sizeof(char32_t): " << sizeof(char32_t) << ", sizeof(wchar_t): " << sizeof(wchar_t) << std::endl;
    // 尽管我们发现在linux平台下二者的大小相等，但是我们依然不能把char32_t 的字符串直接通过wcout输出，所以还是老实地用wstring
    std::wcout << U"你好！" << std::endl;

    return 0;
}

```

如果先用wcout再用cout，那么cout会没有输出；如果先用cout再用wcout，那么wcout会输出乱码，以下是先用cout再用wcout。

```cpp
#include <iostream>
#include <locale> // 包含头文件以使用 setlocale 函数
#include <string>
#include <codecvt> // 包含头文件以使用 std::wstring_convert 和 std::codecvt_utf8
#include <iomanip> // 包含头文件以使用 std::hex 和 std::setw
int main() {
	// 设置程序的本地化环境为系统默认设置
    setlocale(LC_ALL, "");
   // 获取当前本地化名称并转换为 std::string
    std::string localeName = std::locale("").name();
    
    // 我们先用cout输出，因为string类型是一个普通字符串，每个元素类型为char
    std::cout << "From cout, current locale: " << localeName << std::endl;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wstr = conv.from_bytes(localeName);
    // 输出宽字符
    std::wcout << L"来自 wcout，当前的本地化名称：" << wstr << std::endl;
    return 0;
}

```

## 其他问题

当然，你的系统需要支持中文显示（安装过中文字体）才行，我没有在纯英文环境下做测试，猜测应该是不行的，运行`locale`命令应该要看到zh_CN.UTF-8才行。
