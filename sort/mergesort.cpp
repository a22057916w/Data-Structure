#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// merge the two array, 比較左陣列跟右陣列的元素, 依據大小順序塞回原array
void merge(vector<int> &arr, int front, int mid, int end) {
  vector<int> leftSub(arr.begin() + front, arr.begin() + mid + 1);
  vector<int> rightSub(arr.begin() + (mid + 1), arr.begin() + end + 1);

  leftSub.push_back(INT_MAX / 2);   // for comparison convinience
  rightSub.push_back(INT_MAX / 2);

  int left_idx = 0, right_idx = 0;  // index for the two subarray

  // if the element in right subarray is greater than that in left subarray,
  //  fill the right subarry element, and right_idx++.
  // else
  //  do the reverse
  for(int i = front; i <= end; i++) {
    if(rightSub[right_idx] < leftSub[left_idx])
      arr[i] = rightSub[right_idx++];
    else
      arr[i] = leftSub[left_idx++];
  }
}

// 每次切半, 切到剩一個元素在合併, divide and conquer
void MergeSort(vector<int> &arr, int front, int end) {
  if(front < end) {
    int mid = (front + end) >> 1;
    MergeSort(arr, front, mid);
    MergeSort(arr, mid + 1, end);
    merge(arr, front, mid, end);
  }
}

void Printarr(vector<int> &arr){
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
  vector<int> arr = {5,3,8,6,2,7,1,4};

  cout << "original:\n";
  Printarr(arr);

  MergeSort(arr, 0, 7);
  cout << "sorted:\n";
  Printarr(arr);
  return 0;
}

/*
reference:
  http://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
*/
