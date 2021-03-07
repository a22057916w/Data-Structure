#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// self-defined dictionary
class Dict {
private:
    string key;        // key for Name (eg:Jordan)
    string value;      // value for Team (eg:Bulls)
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
  for(auto it = table[index].begin(); it != table[index].end(); it++)
    if(it->key == key_str)
      it = table[index].erase(it);
}

void HashChain::insert(Dict data) {
  // two steps: 1. get index from hash function
  //            2. insert data at the front of linked list
  int index = HashFunction(data.key);
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

// ******************** imp of modifying function *********************
string HashChain::search(string key_str) {
  // two steps: 1. get index from hash function
  //            2. traversal in linked list
  int index = HashFunction(key_str);
  for(const auto& it : table[index])
    if(it.key == key_str)
      return it.value;

  return "...\nno such data.";
}

void HashChain::displayTable() {
  for(int i = 0; i < table.size(); i++) {
    cout << "slot#" << i << ": ";
    for(const auto& it: table[i])
       cout << "(" << it.key << "," << it.value << ") ";
    cout << endl;
  }
  cout << endl;
}

int main() {

  HashChain hash(5);
  hash.insert(Dict("T-Mac","Magic"));
  hash.insert(Dict("Bryant","Lakers"));
  hash.insert(Dict("Webber","Kings"));
  hash.insert(Dict("Arenas", "Wizards"));
  hash.insert(Dict("Davis","Clippers"));
  hash.insert(Dict("Kidd","Nets"));
  hash.displayTable();

  cout << "T-Mac is in " << hash.search("T-Mac") << ". " << endl;
  cout << "Arenas is in " << hash.search("Arenas") << ". " << endl;

  hash.deleteKey("Kidd");
  hash.deleteKey("T-Mac");
  cout << "\nAfter deleing Kidd and T-Mac:\n";
  hash.displayTable();

  return 0;
}
