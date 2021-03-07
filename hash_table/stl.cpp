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


int main() {
  return 0;
}
