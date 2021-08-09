## Q1
* **Please see below code and answer questions**
```
#include <stdio.h>
void main()
{
	int arr[]={1,2,3,4,5};
	int *ptr=arr;
	*(ptr++)+=1;
}
```
(1) What is the result of *ptr? <br>
(2) What is the result of *(++ptr)? <br>
(3) What is the result of arr array?

## Q2
* **What is the output of this program?**
```
#include <iostream>
   using namespace std;
   class X
   {
      public:
      int a;
	 void f(int b) {
		cout<< b << endl; }
   };
   int main()
   {
       int X::*ptiptr = &X::a;
       void (X::*ptfptr)(int) = &X::f;
       X xobject;
       xobject.*ptiptr = 10;
       cout << xobject.*ptiptr << endl;
       (xobject.*ptfptr) (20);
   }
```

## Q3
* **Please write down the output of the following codes.**
```
#include "stdafx.h"
#include <iostream>;
using namespace std;
class BaseObject {
public:
	BaseObject() { cout << "BaseObject constructor." << endl;}
	virtual ~BaseObject(){ cout << "BaseObject destructor." << endl;}
};
class DeriveObject : public BaseObject {
public:
	DeriveObject() { cout << "DeriveObject constructor." << endl;}
	~DeriveObject() { cout << "DeriveObject destructor." << endl;}
};
int _tmain(int argc, _TCHAR* argv[])
{
	DeriveObject testobject;
	return 0;
}
```

## Q4
* **Please explain the (1) meaning & benefit of virtual function (2) benefit of virtual destructor**

## Q5
* **Please (1) explain the meaning of forward declaration (reduce dependency about header file) (2) Please rewrite the sample code with forward declaration.**

## Q6
* **Given an array A[1~n], please write code to find the smallest and largest element with function template form efficiently.** <br><br>
Please refer to the `function_temp.cpp` and `class_temp.cpp` for code example, also [TEMPLATE.md](https://github.com/a22057916w/Data-Structure/blob/main/advanced/TEMPLATE.md) for further explanation.

## Q7
* **What’s the difference between a stack and a heap? How is memory allocated on the stack and heap? How do threads interact with the stack and the heap?** <br><br>
	Through the video [Stack vs Heap Memory | Stack And Heap In C | C Tutorial For Beginners | Simplilearn](https://www.youtube.com/watch?v=gRwfHzeS-GM), you will learn:
		* Understanding how memory stack operates
		* Stack overflow error in program
		* How memory heap operates

	And refer to the [Data-Structure/advanced/memory/README.md](https://github.com/a22057916w/Data-Structure/tree/main/advanced/memory)

#### Reference
* [Stack vs Heap Memory | Stack And Heap In C | C Tutorial For Beginners | Simplilearn](https://www.youtube.com/watch?v=gRwfHzeS-GM)
* [Six Important .NET Concepts: Stack, Heap, Value Types, Reference Types, Boxing, and Unboxing - CodeProject](https://www.codeproject.com/Articles/76153/Six-important-NET-concepts-Stack-heap-value-types#Stack%20and%20Heap)
* [[探索 5 分鐘] stack 與 heap 的底層概念](https://nwpie.blogspot.com/2017/05/5-stack-heap.html)
* [作業系統筆記(二)：利用處理程序、執行緒來多工處理](https://noob.tw/operating-system-multitasking/)
* [執行緒使用共享堆而非私有堆的原因分析](https://www.itread01.com/content/1546786658.html)
