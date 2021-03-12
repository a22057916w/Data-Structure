#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class Dict {
private:
  int key;
  string val;
public:
  Dict(): key(0), val("") {};
  Dict(int k, string s): key(k), val(s) {};

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

  // modifying functions
  void insert(int key, string val);
  void deleteKey(int key);

  // element access
  string search(int key);
  void display();

};

// ********************** imp of modifying func ***************************
void HashOpenAddress::insert(int key, string val) {

  for(int i = 0; i < table.size(); i++) {
    int index = quadraticProbing(key, i);

    if(table[index].val == "") {
      table[index].key = key;
      table[index].val = val;
      elements++;
      return;
    }
  }

  cout << "Hash Table Overflow" << endl;
}

void HashOpenAddress::deleteKey(int key) {
  for(int i = 0; i < table.size(); i++) {
    int index = quadraticProbing(key, i);

    if(table[index].key == key) {
      table[index].key = 0;
      table[index].val = "";
      elements--;
      return;
    }
  }
}

int HashOpenAddress::quadraticProbing(int key, int i) {
   int c1 = 0.5, c2 = 0.5;

   // key & size(m) == HashFunction by Division method
   return ((int)((key & table.size()) * c1*i + c2*i*i) % table.size());
}

// ********************** imp of element access **************************
string HashOpenAddress::search(int key) {

    for(int i = 0; i < table.size(); i++) {
      int index = quadraticProbing(key, i);

      if(table[index].key == key)
        return table[index].val;

    }

    return "...data not found\n";
}

void HashOpenAddress::display() {
  for(int i = 0; i < table.size(); i++)
    printf("slot#%d: ( %d,%s)\n", i, table[i].key, table[i].val().data());
  cout << endl;
}

int main() {

  HashOpenAddress hash(8);          // probing sequence:
  hash.insert(33, "blue");          // 1,2,4,7,3,0,6,5 -> 1
  hash.insert(10, "yellow");        // 2,3,5,0,4,1,7,6 -> 2
  hash.insert(77, "red");           // 5,6,0,3,7,4,2,1 -> 5
  hash.insert(2, "white");          // 2,3,5,0,4,1,7,6 -> 3
  hash.display();
  hash.insert(8, "black");          // 0,1,3,6,2,7,5,4 -> 0
  hash.insert(47, "gray");          // 7,0,2,5,1,6,4,3 -> 7
  hash.insert(90, "purple");        // 2,3,5,0,4,1,7,6 -> 4
  hash.insert(1, "deep purple");    // 4,5,7,2,6,3,1,0 -> 6
  hash.display();
  hash.insert(15, "green");         // hash table overflow

  cout << "number#90 is " << hash.search(90) << "\n\n";

  hash.deleteKey(90);
  cout << "after deleting (90,purple):\n";
  cout << "number#90 is " << hash.search(90) << "\n";

  hash.insert(12, "orange");        // 4,5,7,2,6,3,1,0 -> 4
  hash.display();

  return 0;
}
