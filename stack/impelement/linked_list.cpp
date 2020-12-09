#include <iostream>
using namespace std;

class MyStack;

class StackNode {
private:
  int data;
  StackNode *next;
public:
  StackNode(): data(0) {
      next = NULL;
  }
  StackNode(int x): data(x) {
    next = NULL;
  }
  friend class MyStack;
};

class MyStack {
private:
  StackNode *top;
  int size;
public:
  MyStack(): size(0) {
    top = NULL;
  }

  void Push(int x);
  void Pop();
  bool isEmpty();
  int Top();
  int getSize();
};

void MyStack::Push(int x) {
  if(isEmpty()) {
    top = new StackNode(x);
    size++;
    return;
  }
  else {
    StackNode *newNode = new StackNode(x);
    newNode->next = top;
    top = newNode;
    size++;
  }
}

void MyStack::Pop() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return;
  }
  else {
    StackNode *delNode = top;
    top = top->next;
    delete delNode;
    delNode = NULL;
    size--;
  }
}

bool MyStack::isEmpty() {
  return size == 0;
}

int MyStack::Top() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return -1;
  }
  else
    return top->data;
}

int MyStack::getSize() {
  return size;
}


int main() {
  MyStack s;

  s.Pop();
  s.Push(14);
  s.Push(9);
  cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
  s.Push(7);
  std::cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
  s.Pop();
  s.Pop();
  cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
  s.Pop();
  cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;

  return 0;
}
