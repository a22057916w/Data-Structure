#include <iostream>
using namespace std;

class QueueNode {
private:
  int data;
  QueueNode *next;
public:
  QueueNode(): data(0), next(NULL) {};
  QueueNode(int x): data(x), next(NULL) {};
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
