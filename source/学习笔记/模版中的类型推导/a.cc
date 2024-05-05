#include <iostream>
using namespace std;
// 使用非引用类型
#define USENOREF 0
#if USENOREF 
  void foo(int i){cout << "int i" <<endl;} // int类型传值，不会改变实参
#else
  void foo(int& i){cout << "int &i" <<endl;} // int类型传引用，会改变实参

  void foo(const int& i){cout << "const &i" << endl;} // const的int类型传引用，不会改变实参
  void foo(int&& i){cout <<"int && i" <<endl;} // int类型传右值引用，无法修改实参
#endif

int main()
{
	int i = 1; foo(i); // int i
	int &j = i; foo(j); // int &i 
	int const ci = 1; foo(ci); // const int i
	int const &cir = ci; foo(cir); // const &i
	foo(1); // int&& i
	return 0;
}
