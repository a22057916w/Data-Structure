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

## Q5

## Q6

## Q7
