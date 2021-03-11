#include <iostream>
#include <string>
using namespace std;

class Dict {
  string key;
  string value;

  Dict(): key(""), value("") {};
  Dict(string key, string val) key(key), value(val) {};

  friend class HashChain;
};

class HashChain {
private:
  int size, elements;

  vector<Dict> table;

  int quadraticProbing(int key, int i);
public:
  
};

int main() {
  return 0;
}
