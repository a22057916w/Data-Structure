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

    int PreHashing(string key_str);     // turn string_type_key to int_type_key
    int HashFunction(string key_str);   // using Division method
public:
  HashChain(){};
  HashChain(int m): size(m), count(0) {
    table.resize(size);
  }

  // element access functions
  string search(string key);
  void displayTable();

  // modifying function
  void insert(Dict data);
  void deleteKey(string key);
};


int main() {
  return 0;
}
