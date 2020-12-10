#include <iostream>
using namespace std;

class MyQueue {
private:
  int capacity, front, back;
  int *queue;
  void DoubleCapacity();
public:
  MyQueue(): capacity(1), front(-1), back(-1) {
    queue = new int[capacity];
  };

  void push(int x);
  void pop();
  bool isEmpty();
  bool isFull();
  int getFront();
  int getBack();
  int getSize();        // return the number of elements
  int getCapacity();    // return the capacity of the queue

};

void MyQueue::DoubleCapacity() {
  capacity *= 2;
  int newQueue = new int[capacity];

  // re-initialize the queue by re-ping front and back
  for(int i = 0, j = front + 1; i < capacity / 2 && j <= back; i++, j++)
    newQueue[i] = queue[j];
  back = back - (front + 1);
  front = -1;
  delete[] queue;
  queue = newQueue;
}

void MyQueue::push(int x) {
    if(isFull())
      DoubleCapacity();
    queue[++back] = x;
}

void MyQueue::pop() {
  if(isEmpty)
    cout << "The queue is empty" << endl;
  else
    front++;
}

bool MyQueue::isEmpty() {
  return front == back;
}

bool MyQueue::isFull() {
  return back + 1 == capacity;
}

int MyQueue::getFront() {
  if(isEmpty()) {
    cout << "The queue is empty" << endl;
    return -1;
  }
  else
    return queue[front + 1];
}

int MyQueue::getBack() {
  if(isEmpty()) {
    cout << "The queue is empty" << endl;
    return -1;
  }
  else
    return queue[back];
}

int MyQueue::getSize() {
  return back - front;
}

int MyQueue::getCapacity() {
  return capacity;
}

int main() {
  return 0;
}
