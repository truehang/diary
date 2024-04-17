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

