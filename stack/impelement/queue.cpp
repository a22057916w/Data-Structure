#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
  queue<int> data, buffer;
  int size;
public:
  MyStack(): size(0) {};

  void push(int x);
  void pop();
  bool isEmpty();
  int Top();
  int getSize();
};

void MyStack::push(int x) {

  // push x first to buffer
  buffer.push(x);

  while(!data.empty()) {
    buffer.push(data.front());
    data.pop();
  }

  // after while loop, buffer is acting like stack and data is empty
  // so swaps the two names
  queue<int> tmp = data;
  data = buffer;
  buffer = tmp;

  size++;
}


void MyStack::pop() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return;
  }
  else {
    data.pop();
    size--;
  }

}

bool MyStack::isEmpty() {
  return size == 0;
}

int MyStack::top() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return -1;
  }
  else
    return data.front();
}

int MyStack::getSize() {
  return size;
}
