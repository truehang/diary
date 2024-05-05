# C++ 类型推导

首先我们需要明白一个概念，引用折叠。

## 引用折叠

当我们对一个引用继续引用时，就会发生引用折叠。当然，我们不能主动对一个引用进行引用，但是在模版类型中，会出现引用的引用的情况。  
我们需要制定规则来解决这个问题。  
首先，左右值引用都是一次引用，尽管右值引用有两个`&`符号，但这不代表两层引用，只是为了区分左值引用。  
下面来看一些二层引用的引用折叠规则：    

* X& & -> X&
* X& && -> X&
* X&& & -> X&
* X&& && -> X&&  
  总而言之，就是右值引用的右值引用会折叠为右值引用，其他情况都会折叠为左值引用。X为普通类型或者const都是成立的。

## 类型推导例子

对下面每个调用，确定T和val的类型。

```cpp
template <typename T> void g(T&& val);
int i = 0; const int ci = i;
g(i); // 情况1
g(ci); // 情况2
g(i * ci); // 情况3
```

在推导之前我们还需要明白一个函数调用匹配的原则。

### 函数调用匹配

匹配首先是函数名匹配，然后是参数个数匹配，最后是参数类型匹配或者可以转换亦或者可以接收。  
关于形参可以接收的实参类型，const对象对const对象，非const对非const。  
引用折叠最后得到要么左值引用，要么右值引用，再组合const，那么实际上就是三种引用类型。     

```cpp
void g(int& val); // int类型传引用，会改变实参
void g(const int& val); // const的int类型传引用，不会改变实参
void g(int&& val); // int类型传右值引用，无法修改实参
```

我们回到类型推导的例子。  
首先i类型是int，那么g(i)最佳匹配是g(int val)，实际上**g(int val)可以接受int, int &, const int, const int&, int &&的任意实参，所以g(int val)也与其他三个函数在调用时发生匹配冲突**。下面将使用代码验证这一观点。

1. foo(int i)函数可以接受任意实参
   
   下面的代码，如果USENOREF为1，则输出5行均为"int i"，表明5种实参都调用了foo(int i)函数。如果USENOREF为0，则输出"int &i int &i const &i const &i int && i"(输出省略了换行)。

```cpp
#include <iostream>
using namespace std;
// 使用非引用类型
#define USENOREF 1
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
```

2. foo(int i)函数与其他引用类型的函数会发生匹配冲突
   
   下面的代码DONOTCALL为1时，可以通过编译，此时没有实参调用foo函数；而DONOTCALL为0时，有实参调用foo函数却会发生函数匹配的编译错误。
   
   ```cpp
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
   
   ```



3. 参数模板T&& + forward解决了转发匹配的问题
   
   下面代码中使用foo(forward( val))和foo(val)可以看到是否匹配到右值函数，同时证明了右值只能传递到一层函数（模板生成的函数），除非forward。
   
   ```cpp
   #include <iostream>
   using namespace std;
   //void foo(int i){cout << "int i" <<endl;} // int类型传值，不会改变实参
     void foo(int& i){cout << "int &i" <<endl;} // int类型传引用，会改变实参
   //  void foo(const int i){cout << "const int i" <<endl;} // const int类型，不会改变实参
   
     void foo(const int& i){cout << "const &i" << endl;} // const的int类型传引用，不会改变实参
     void foo(int&& i){cout <<"int && i" <<endl;} // int类型传右值引用，无法修改实参
   template <typename T> void g(T&& val){ 
   	foo(forward<T>( val));
   	// foo(val); // 不能匹配到右值函数
   } 
   int main()
   {
   	int i = 1; g(i); // int i
   	int &j = i; g(j); // int &i 
   	int const ci = 1; g(ci); // const int i
   	int const &cir = ci; g(cir); // const &i
   	foo(1); // int&& i
   	return 0;
   }
   
   ```
   
   

能从上面例子得到的编程建议就是**要么只使用foo(int)一种，要么完全不用foo(int)**。

现在我们再来看函数匹配，显然能匹配到的都是引用型的函数。基于此，我们进行类型推导。

首先i类型是int，只能匹配g(int& val), val类型为int&。再看引用折叠T && -> int&，T类型为int&。  
ci是const i，那么g(ci)最佳匹配是g(const int& val), val类型为const int&。再看引用折叠T && -> const int&，T类型为const int&。  
i * ci是右值，那么g(i * ci)最佳匹配是g(int&& val), val类型为int&&。再看T && -> int&&，T类型为int(理想状态下不需要引用折叠)。  

其实就是T的类型决定了foo的选择，T为int&或 const int&时，都完美匹配，而为int时，只能为它匹配int &了，而std::forward靠着修改下一层调用时的类型进行完美匹配。

我们看看std::forward的源码：

```cpp

  /**
   *  @brief  Forward an lvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    { return static_cast<_Tp&&>(__t); }

  /**
   *  @brief  Forward an rvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
		    " substituting _Tp is an lvalue reference type");
      return static_cast<_Tp&&>(__t);
    }


```





当T（源码为_Tp）为int& 或const int&时，走上面一种实现，引用折叠后返回的还是int& 或const int&类型，不发生任何改变，多一层折叠而以。当 T为int时，此时返回了int &&类型，所以在调用foo之前，int型变成了int&&，当然匹配到不同的函数。其实很简单，**多一层引用折叠就可以完美转发**。注意下面的代码：

```cpp
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

```
