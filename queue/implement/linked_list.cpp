#include <iostream>
using namespace std;

class QueueNode {
private:
  int data;
  QueueNode *next;
public:
  QueueNode(): data(0), next(NULL) {};
  QueueNode(int x): data(x), next(NULL) {};

  friend class MyQueue;
};

class MyQueue {
private:
    QueueNode *front, *back;
    int size;
public:
    MyQueue(): front(NULL), back(NULL), size(0) {};

    void push(int x);
    void pop();
    bool isEmpty();
    int getFront();
    int getBack();
    int getSize();
};

void MyQueue::push(int x) {
    if(isEmpty()) {
      front = new QueueNode(x);
      back = front;
      size++;
      return ;
    }

    QueueNode *newNode = new QueueNode(x);
    back->next = newNode;
    back = newNode;
    size++;
}

void MyQueue::pop() {
  if(isEmpty())
    cout << "The queue is empty" << endl;
  else {
    QueueNode *delNode = front;
    front = front->next;
    delete delNode;
    delNode = NULL;
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
    return front->data;
}

int MyQueue::getBack() {
  if(isEmpty()) {
    cout << "The queue is empty" << endl;
    return -1;
  }
  else
    return back->data;
}

int MyQueue::getSize() {
  return size;
}

int main() {
  MyQueue q;
  if (q.isEmpty()) {
    cout << "Queue is empty.\n";
  }
  q.push(24);
  cout << "\nAfter push 24: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.push(8);
  cout << "\nAfter push 8: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.push(23);
  cout << "\nAfter push 23: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.push(13);
  cout << "\nAfter push 13: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.pop();
  cout << "\nAfter pop the front element: \n";
  cout << "front: " << q.getFront() << "     back: " << q.getBack() << "\n";

  q.push(35);
  cout << "\nAfter push 35: \n";
  cout << "front: " << q.getFront() << "     back: " << q.getBack() << "\n";

  q.pop();
  cout << "\nAfter pop the front element: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.pop();
  cout << "\nAfter pop the front element: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.pop();
  cout << "\nAfter pop the front element: \n";
  cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";

  q.pop();
  cout << "\nAfter pop the front element: \n";

  q.pop();

  return 0;
}
