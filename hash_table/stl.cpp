#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// self-defined dictionary
class Dict {
private:
    String key;        // key for Name (eg:Jordan)
    String value;      // value for Team (eg:Bulls)
public:
  Dict(): key(""), value("") {};
  Dict(string key, string value): key(key), value(value) {};

  friend class HashChain;
};

class HashChain {
private:
    int size;     // size of table
    int count;    // number of data

    // Hash table with linked list. vector for array, list for linked list chaining
    vector<list<Dict> > table;

    // modifying function
    int PreHashing(string key_str);     // turn string_type_key to int_type_key
    int HashFunction(string key_str);   // using Division method

public:
  HashChain(){};
  HashChain(int m): size(m), count(0) {
    table.resize(size);                 // allocate memory for each slot
  }

  // element access functions
  string search(string key);
  void displayTable();

  // modifying function
  void insert(Dict data);
  void deleteKey(string key);
};

// ******************** imp of modifying function *********************
void HashChain::deleteKey(string key_str) {
  // two steps: 1. get index from hash function
  //            2. traversal in linked list
  int index = HashFunction(key_str);
  for(const auto& it : table[index])
    if(it->key == key_str)
      return it->value;
}

void HashChain:insert(Dict data) {
  // two steps: 1. get index from hash function
  //            2. insert data at the front of linked list
  int index = HashFunction(data->key);
  table[index].push_front(data);
}

int HashChain::HashFunction(string key_str) {
  return (PreHashing(key_str) % this->size);    // Division method
}

int HashChain::PreHashing(string key_str) {
  // if   key_str = Jordan, exp = 9
  // then key_int = ASCII(J)*9^5+ASCII(o)*9^4+ASCII(r)*9^3
  //               +ASCII(d)*9^2+ASCII(a)*9^1+ASCII(n)*9^0

  int exp = 9, p = 1;     // choose randomly
  int key_int = 0;

  for(int i = 0; i < key_str.length(); i++) {
    key_int += key_str[i] * p;
    p *= exp;
  }

  return key_int;
}

int main() {
  return 0;
}
