#include <iostream>
using namespace std;
class X
{
    public:
    int a;
    void f(int b) {
        cout << b << endl; }
};
int main()
{
    // declare pointer to data membe
    int X::*ptiptr = &X::a;

    // declare a pointer to member function
    void (X::*ptfptr)(int) = &X::f;

    // create an object of class type X
    X xobject;

    // initialize data member
    xobject.*ptiptr = 10;

    cout << xobject.*ptiptr << endl;

    // call member function
    (xobject.*ptfptr) (20);

    return 0;
}
