#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

class Dict {
private:
    String key;
    String value;
public:
  Dict(): key(""), value("") {};
  Dict(string key, string value): key(key), value(value) {};

  friend class HashChain
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
};


int main() {
  return 0;
}
