#include <iostream>
#include <string>
using namespace std;

class Dict {
private:
  string key;
  string value;
public:
  Dict(): key(""), value("") {};
  Dict(string key, string val) key(key), value(val) {};

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
