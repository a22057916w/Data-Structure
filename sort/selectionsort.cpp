#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void selectionsort(vector<int> &v) {
  for(int i = 0; i < v.size(); i++)
    for(int j = i + 1; j < v.size(); j++)
      if(v[i] > v[j])
        swap(v[i], v[j]);
}

int main(int argc, char **argv) {
  vector<int> nums(10, 0);

  for(auto &e : nums)
    e = rand() % 10;

  for(auto e : nums)
    cout << e << " ";
  cout << endl;

  selectionsort(nums);

  for(auto e : nums)
    cout << e << " ";
  return 0;
}
