//#include "stdafx.h"
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

int main(int argc, char* argv[])
{
	DeriveObject testobject;
	return 0;
}

/* output:
BaseObject constructor.
DeriveObject constructor.
DeriveObject destructor.
BaseObject destructor.
*/
