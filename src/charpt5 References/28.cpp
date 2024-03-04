#include<iostream>

/*

理解引用折叠:
1.Widget widgetFactory();  // 返回右值的函数
2.Widget w;                // 变量(左值)
3.func(w);                 // 调用func并传入左值: T的推导结果型别为Widget&
4.func(widgetFactory());   // 调用func并传入右值: T的推导结果型别为Widget

在C++中"引用的引用"是非法的,但是折叠引用是合法的.

template<typename T>
void func(T&& param)            // 同前

func(w)                         // 调用 func 并传入左值: T的推导结果型别为Widget&

即: void func(Widget& && param);   
折叠引用得出: void func(Widget& param);

引用推到:
如果任一引用为左值引用，则结果为左值引用。否则（即两个皆为右值引用），结果为右值引用。

引用折叠:
左+左 = 左
左+右 = 左
右+左 = 左
右+右 = 右   --> 引用折叠

*/


int main()
{

    


    return 0;
}