#include <iostream>
using namespace std;

class QueueNode {
private:
    int data;
    QueueNode *prev, *next;
public:
    ListNode(): data(0), prev(NULL), next(NULL) {};
    ListNode(int x): data(0), prev(NULL), next(NULL) {};

    friend class MyDeque;
};

class MyDeque {
private:
    int size;
    QueueNode *front, *back;
public:
    MyDeque(): size(0), front(NULL), back(NULL) {};

    void push_front(int x);
    void push_back(int x);
    void pop_front();
    void pop_back();
    bool isEmpty();
    int getFront();
    int getBack();
    int getSize();
};

void MyDeque::push_front(int x) {
  if(isEmpty()) {
    front = new QueueNode(x);
    back = front;
    size++;
    return;
  }

  QueueNode *newFront = new QueueNode(x);
  newFront->next = front;
  front->prev = newFront;
  front = newFront;
  size++;
}

void MyDeque::push_back(int x) {
  if(isEmpty()) {
    front = new QueueNode(x);
    back = front;
    size++;
    return;
  }

  QueueNode *newBack = new QueueNode(x);
  newBack->prev = back;
  back->next = newBack;
  back = newBack;
  size++;
}

void NyDeque::pop_back() {
  if(isEmpty())
    cout << "The queue is empty." << endl;
  else {
    QueueNode *delNode = back;
    back = back->prev;

    if(back == NULL)
      front = back = NULL;
    else
      back->next = NULL;

    delete delNode;
    delNode = NULL;

    size--;
  }
}

void MyDeque::pop_front() {
  if(isEmpty())
    cout << "The queue is empty." << endl;
  else {
    QueueNode *delNode = front;
    front = front->next;

    if(front == NULL)
      front = back = NULL;
    else
      front->prev = NULL;

    delete delNode;
    delNode = NULL;

    size--;
  }
}

bool MyDeque::isEmpty() {
  return size == 0;
}

int MyDeque::getFront() {
  if(isEmpty()) {
    cout << "The queue is empty." << endl;
    return -1;
  }

  return front->data;
}

int MyDeque::getBack() {
  if(isEmpty()) {
    cout << "The queue is empty." << endl;
    return -1;
  }

  return back->data;
}

int MyDeque::getSize() {
  return size;
}
