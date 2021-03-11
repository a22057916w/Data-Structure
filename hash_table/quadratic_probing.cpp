#include <iostream>
#include <string>
using namespace std;

class Dict {
  string key;
  string value;

  Dict(): key(""), value("") {};
  Dict(string key, string val) key(key), value(val) {};

  friend class HashChain;
}

int main() {
  return 0;
}
