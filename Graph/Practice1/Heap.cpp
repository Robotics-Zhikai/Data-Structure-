#include "Heap.h"

template <class ElemenType>
ElemenType Default;
#define ElemenTypical Default


//不知道为啥，当把.h里的实现移到cpp里时，会出现error LNK2019: 无法解析的外部符号 "public:（就是类中的方法名字） 这样的错误
//当把这些实现全部移到heap.h时，就又没有错误了，不知为何


//C++primer上说 模板与非模板是不同的，为了生成一个实例化版本，编译器需要掌握函数模板或类模板成员函数的定义
//因此与非模板代码不同，模板的头文件通常既包括声明也包括定义；
//即 函数模板和类模板成员函数的定义通常放在头文件中



















