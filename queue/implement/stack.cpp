#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> data, buffer;
    int size;
public:
    MyQueue(): size(0) {};

    void push(int x);
    void pop();
    bool isEmpty();
    int getFront();
    int getSize();
};

void MyQueue::push(int x) {
  while(!data.empty()) {
    buffer.push(data.top());
    data.pop();
  }

  data.push(x);
  while(!buffer.empty()) {
      data.push(buffer.top());
      buffer.pop();
  }
  size++;
}

void MyQueue::pop() {
  if(isEmpty())
    cout << "The queue is empty" << endl;
  else {
    data.pop();
    size--;
  }
}

bool MyQueue::isEmpty() {
  return size == 0;
}

int MyQueue::getFront() {
  if(isEmpty()) {
    cout << "The queue is empty" << endl;
    return -1;
  }
  else
    return data.top();
}

int MyQueue::getSize() {
  return size;
}
