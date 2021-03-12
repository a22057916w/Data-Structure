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

// ********************** imp of modifying func ***************************
void HashOpenAddress::insert(int key string val) {

  for(int i = 0; i < table.size(); i++) {
    int index = quadraticProbing(key, i);

    if(table[index].val == "") {
      table[index].key = key;
      table[index].val = val;
      element++;
      return;
    }
  }

  cout << "Hash Table Overflow" << endl;
}

int HashOpenAddress::quadraticProbing(int key, int i) {
   int c1 = 0.5, c2 = 0.5;
   
   // key & size(m) == HashFunction by Division method
   return ((int)((key & table.size()) * c1*i + c2*i*i) % table.size());
}

int main() {
  return 0;
}
