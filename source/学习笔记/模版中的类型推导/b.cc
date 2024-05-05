#include <iostream>
using namespace std;
// 不会有实参调用foo函数
#define DONOTCALL 1
void foo(int i){cout << "int i" <<endl;} // int类型传值，不会改变实参
  void foo(int& i){cout << "int &i" <<endl;} // int类型传引用，会改变实参

  void foo(const int& i){cout << "const &i" << endl;} // const的int类型传引用，不会改变实参
  void foo(int&& i){cout <<"int && i" <<endl;} // int类型传右值引用，无法修改实参

int main()
{
#if !DONOTCALL
	int i = 1; foo(i); // int i
	int &j = i; foo(j); // int &i 
	int const ci = 1; foo(ci); // const int i
	int const &cir = ci; foo(cir); // const &i
	foo(1); // int&& i
#endif
	return 0;
}
