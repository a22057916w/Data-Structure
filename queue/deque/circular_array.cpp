#include <iostream>
using namespace std;

class MyDeque {
private:
    int capacity, front, rear;
    int *queue;
    void DoubleCapacity();
public:
    MyDeque(): capacity(2), front(0), back(0) {};

    void push_front(int x);
    void push_back(int x);
    void pop_front();
    void pop_back();
    bool isEmpty();
    bool isFull();
    int getFront();
    int getBack();
    int getCapacity();
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

void MyDeque::pop_back() {
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

int main()
{
    MyDeque dq;
    cout << "Insert element '5' at rear end\n";
    dq.push_back(5);

    cout << "Insert element '10' at rear end\n";
    dq.push_back(10);

    cout << "Rear end element: "
        << dq.getBack() << endl;

    dq.pop_back();
    cout << "After deleting rear element new rear"
        << " is: " << dq.getBack() << endl;

    cout << "Inserting element '15' at front end \n";
    dq.push_front(15);

    cout << "Front end element: "
        << dq.getFront() << endl;

    cout << "Number of elements in Deque: "
        << dq.getSize() << endl;

    dq.pop_front();
    cout << "After deleting front element new "
        << "front is: " << dq.getFront() << endl;

    return 0;
}