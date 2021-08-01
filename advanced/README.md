# C/C++ 進階筆記
遇到的問題:對Class及Pointer的用法不熟悉。
接下針對下面的Code來做筆記。

![](https://i.imgur.com/UcXvzIg.png)

## Class 
**以下將釐清幾個不熟悉的點:** 
### **Constructor(建構函數)**
若不須宣告的話，編譯器會自行補上預設的建構函數。(我都會宣告)
### **Private**
成員只限同個類別的其他成員存取，因此也不能被**繼承**。不過，C++提供另一種方式讓**函數**或**其他類別**也可存取`private`成員，即在類別宣告`friend`成員函數或類別，舉例如下:

![](https://i.imgur.com/BEknIWS.png)

### **Protected**
跟`private`只限類別成員使用，但是可以被**繼承**。另外也可適用於`friend`。
### **Const** 
類別中宣告為`const`的成員函數不能修改成員變數的值，`const`會放在函數名稱後面，如下:
```
int get_sum() const {
    return a + b;
}
```
### **繼承** 
繼承的類別可以稱為**衍生類別(derived class)**，可以繼承**基礎類別(base class)**的`public`或`protected`成員，範例如下:
```
#include <iostream>
  
class Demo {
public:
    Demo() {
        a = 10;
        b = 33;
    }
    
protected:
    int a;
    int b;
};

class Demo2: Demo {
public:
    int do_something() {
        return a + b;
    }
};

int main() {
    Demo2 d;
    std::cout << d.do_something() << std::endl;
    
    return 0;
}
```
`output: 43`

如上範例，衍生類別(derived class)要繼承基礎類別(base class)時的語法是`: <base class>`。
### **Virtual 函數**
C++的`virtual`關鍵字分成**虛擬函式**(virtual function)與**純虛函式**(pure virtual function)兩種用法，以下將說明這兩種的差異與使用時機。

1. **虛擬函式 virtual function**
        不強制子類一定要實作，子類不實作的話會以父類的實作為主，子類實作的話會以子類的實作為主，另外子類在覆載override父類時，加上`override`關鍵字是個好習慣。
        
    **使用時機**：在子類不覆寫 override 時，有個預設實作(父類的實作)。
        ![](https://i.imgur.com/TgBFXOF.png)
    **輸出:**
        ![](https://i.imgur.com/QtIOfLv.png)


2. **純虛函式 pure virtual function**
        如下例子，Base的func1為純虛函式，純虛函式寫法為`virtual void func1() = 0;`，然後沒有實作，Base是**抽象類別**不能被實體化，強制子類一定要覆寫實作，在某種情況下有這種設計需求。子類實作的話當然就會以子類的實作為主，若子類沒實作則會收到編譯器**Error**。
        
     **使用時機**：設計一些介面interface時，強制別人一定要這樣實作。
        ![](https://i.imgur.com/DW9aHgC.png)


更多詳細資訊參見[C++ virtual 的兩種用法](https://shengyu7697.github.io/cpp-virtual/)

### **Destructor(解構函數)**
用來在程式結束執行銷毀物件，通常編譯器會提供預設的解構函數(**inline public member**)，但是成員有指標的時候，就要自己寫解構函數，以進行有效的記憶體管理。
```
#include <iostream>
  
class Demo {
public:
    Demo(int pa) {
        std::cout << "constructor" << std::endl;
        a_ptr = new int;
        *a_ptr = pa;
    }
    
    ~Demo() {
        std::cout << "destructor" << std::endl;
        delete a_ptr;
    }
    
    void do_something() {
        std::cout << *a_ptr << std::endl;
    }
    
private:
    int *a_ptr;
};

int main(void) {
    Demo d(2048);
    d.do_something();
    
    return 0;
}
```
宣告解構函數時用`~`符號表示，裡頭用`delete`刪除指標成員
```
output:
constructor
2048
destructor
```
### **繼承後的建構函式與解構函式**
1. 如果您使用衍生類別生成物件，則建構函式的執行順序會從基底類別的建構函式開始執行起(合理)
3. 在物件被消滅時，解構函式的執行順序則**正好相反**，是從衍生類別的解構函式開始執行，再來才是基礎類別的建構函式，因為若基底類別的解構函式如果先執行， 則衍生類別相依於基底類別的一些狀態也會被解構（例如指標），則此時再行衍生類別的解構函式，將存在著相依問題而造成錯誤。(合理)

下面這個簡單的程式可以告訴您建構函式與解構函式，在繼承之後的執行順序：
![](https://i.imgur.com/O664Iin.png)

**執行結果：**

![](https://i.imgur.com/gVTASfF.png)

<br><br>

## Base Class and Derived Class
以下用範例來澄清各種問題:
### [C++ | Inheritance | Question 4](https://www.geeksforgeeks.org/c-inheritance-question-4/)
```
#include<iostream>

using namespace std;
class P {
public:
void print() { cout <<" Inside P"; }
};

class Q : public P {
public:
void print() { cout <<" Inside Q"; }
};

class R: public Q { };

int main(void)
{
R r;
r.print();
return 0;
}
```
![](https://i.imgur.com/9iKGbKf.png)

**Explanation:** The idea is, if there is multilevel inheritance, then function is linearly searched up in the inheritance hierarchy until a matching function is found.

### [C++ | Inheritance | Question 6](https://www.geeksforgeeks.org/c-inheritance-question-6/)
```
#include<iostream>
using namespace std;

class Base {};

class Derived: public Base {};

int main()
{
	Base *bp = new Derived;
	Derived *dp = new Base;
}

```
![](https://i.imgur.com/GPORIn9.png)

**Explanation:** A Base class pointer/reference can point/refer to a derived class object, but the other way is not possible.

### [C++ | Inheritance | Question 7](https://www.geeksforgeeks.org/c-inheritance-question-7/)
```
#include<iostream>
using namespace std;

class Base
{
public:
	void show()
	{
		cout<<" In Base ";
	}
};

class Derived: public Base
{
public:
	int x;
	void show()
	{
		cout<<"In Derived ";
	}
	Derived()
	{
		x = 10;
	}
};

int main(void)
{
	Base *bp, b;
	Derived d;
	bp = &d;
	bp->show();
	cout << bp->x;	
	return 0;
}
```

![](https://i.imgur.com/4YXR3K8.png)

**Explanation:** A **base class pointer** can point to a derived class object, but we can only access base class member or **virtual functions** using the base class pointer because object slicing happens when a derived class object is assigned to a base class object. Additional attributes of a derived class object are sliced off to form the base class object.

### [C++ | Inheritance | Question 8](https://www.geeksforgeeks.org/c-inheritance-question-8/)
```
#include<iostream>
using namespace std;

class Base
{
public:
	int fun() { cout << "Base::fun() called"; }
	int fun(int i) { cout << "Base::fun(int i) called"; }
};

class Derived: public Base
{
public:
	int fun() { cout << "Derived::fun() called"; }
};

int main()
{
	Derived d;
	d.fun(5);
	return 0;
}
```

![](https://i.imgur.com/ldlV0HD.png)

**Explanation:** If a derived class writes its own method, then all functions of base class **with same name become hidden**, even if signaures of base class functions are different.

In the above question, when fun() is rewritten in Derived, it hides both fun() and fun(int) of base class.

### [C++ | Inheritance | Question 9](https://www.geeksforgeeks.org/c-inheritance-question-9/)
```
#include<iostream>
using namespace std;

class Base {
public:
	void fun()		 { cout << "Base::fun() called";	 }
	void fun(int i)	 { cout << "Base::fun(int i) called"; }
};

class Derived: public Base {
public:
	void fun() {	 cout << "Derived::fun() called"; }
};

int main() {
	Derived d;
	d.Base::fun(5);
	return 0;
}

```

![](https://i.imgur.com/itQJOa2.png)

**Explanation:** We can access base class functions using **scope resolution operator**`::` even if they are made hidden by a derived class function.







