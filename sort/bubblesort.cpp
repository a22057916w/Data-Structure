#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

// move the largest number to the last in each round of i
void bubblesort(vector<int> &v) {
  for(int i = 0; i < v.size(); i++)
    for(int j = 0; j < v.size() - 1; j++)
      if(v[j] > v[j + 1])
        std::swap(v[j], v[j+1]);
}

int main(int argc, char **argv) {
  vector<int> nums(10, 0);

  for(auto &e : nums)
    e = rand() % 10;

  for(auto e : nums)
    cout << e << " ";
  cout << endl;

  bubblesort(nums);

  for(auto e : nums)
    cout << e << " ";
  return 0;
}

/*
https://ithelp.ithome.com.tw/articles/10276184
*/
