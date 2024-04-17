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

