#include <iostream>
#include <string>
using namespace std;

class Dict {
private:
  int key;
  string val;
public:
  Dict(): key(0), value("") {};
  Dict(int k, string s) key(k), val(s) {};

  friend class HashOpenAddress;
};

class HashOpenAddress {
private:
  int size, elements;

  vector<Dict> table;

  int quadraticProbing(int key, int i);
public:
  HashOpenAddress(): size(0), elements(0), table(0) {};
  HashOpenAddress(int m): size(m), elements(0) {
    table.resize(this->size);
  }

  string serch(int key);
  void display();

  void insert(int key, string val);
  void deleteKey(int key);

};

int main() {
  return 0;
}
