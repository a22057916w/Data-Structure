#include <iostream>
using namespace std;

int main() {
    int num = 5;
    int *ptr = &num;
    cout << "Value of num: " << num << endl;
    cout << "Value via pointer: " << *ptr << endl;
    cout << "Memory address of num: " << &num << endl;
    cout << "Memory address via pointer: " << ptr << endl;
    cout << "Memory address of pointer itself: " << &ptr << endl;
    return 0;
}