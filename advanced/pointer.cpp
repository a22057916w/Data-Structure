#include <stdio.h>
void main()
{
	int arr[]={1,2,3,4,5};
	int *ptr=arr;

  // value of index 0 +=1
  // index(*ptr) goes to 1 after the following line
	*(ptr++)+=1;

  cout << *ptr << endl;
	for(int i = 0; i < 5; i++)
    cout << arr[i] << " ";

  return 0;
}
