#include <iostream>
using namespace std;

class MyQueue {
private:
  int capacity, front, back;
  int *queue;
  void DoubleCapacity();
public:
  MyQueue(): capacity(5), front(0), back(0) {
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
  int *newQueue = new int[capacity];

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

    back = (back + 1) % capacity;
    queue[back] = x;
}

void MyQueue::pop() {
  if(isEmpty())
    cout << "The queue is empty" << endl;
  else
    front = (front + 1) % capacity;
}

bool MyQueue::isEmpty() {
  return front == back;
}

bool MyQueue::isFull() {
  return (back + 1) % capacity == front;
}

int MyQueue::getFront() {
  if(isEmpty()) {
    cout << "The queue is empty" << endl;
    return -1;
  }
  else
    return queue[(front + 1) % capacity];
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
  if(front <= back)
    return back - front;
  else
    return capacity - (front - back);
}

int MyQueue::getCapacity() {
  return capacity;
}

void printQueue(MyQueue &queue) {
  cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
    << "capacity: " << queue.getCapacity() << "  size/number of elements: " << queue.getSize() << "\n\n";
}

int main() {
  MyQueue q;
  if (q.isEmpty()) {
    cout << "Queue is empty.\n\n";
  }
  q.push(24);
  cout << "After push 24: \n";
  printQueue(q);
  q.push(8);
  q.push(23);
  cout << "After push 8, 23: \n";
  printQueue(q);
  q.pop();
  cout << "After pop 24: \n";
  printQueue(q);
  q.push(13);
  cout << "After push 13: \n";
  printQueue(q);
  q.pop();
  cout << "After pop 8: \n";
  printQueue(q);
   q.push(35);
   cout << "After push 35: \n";
  printQueue(q);
   q.push(9);
   cout << "After push 9: \n";
  printQueue(q);

   return 0;
}
