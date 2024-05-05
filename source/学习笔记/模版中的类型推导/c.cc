#include <iostream>
using namespace std;
// void foo(int i){cout << "int i" <<endl;} // int类型传值，不会改变实参
void foo(int &i) { cout << "int &i" << endl; } // int类型传引用，会改变实参
//  void foo(const int i){cout << "const int i" <<endl;} // const
//  int类型，不会改变实参

void foo(const int &i) {
  cout << "const &i" << endl;
} // const的int类型传引用，不会改变实参
void foo(int &&i) {
  cout << "int && i" << endl;
} // int类型传右值引用，无法修改实参
template <typename T> void g(T &&val) {
  //	foo(forward<T>( val));
  // foo(val); // 不能传递右值引用
  foo(static_cast<T &&>(val)); // 传递右值引用， 和forward效果一样
}
int main() {
  int i = 1;
  g(i); // int i
  int &j = i;
  g(j); // int &i
  int const ci = 1;
  g(ci); // const int i
  int const &cir = ci;
  g(cir); // const &i
  g(1);   // int&& i
  return 0;
}
