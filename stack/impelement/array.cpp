#include <iostream>
using namespace std;

class MyStack {
public:
  MyStack(): top(-1), capacity(1) {
    stack = new int[capacity];
  }

  void Push(int x);
  void Pop();
  bool isEmpty();
  int Top();
  int getSize();

private:
  int top;
  int capacity;
  int *stack;
  void DoubleCapacity();
};

void MyStack::DoubleCapacity() {
  capacity *= 2;
  int *newStack = new int[capacity];

  // copy the elements to newStack
  for(int i = 0; i < capacity; i++)
    newStack[i] = stack[i];

  delete[] stack;             // release the memory of stack;
  stack = newStack;           // redirect stack to newStack
}

bool MyStack::isEmpty() {
  return top == -1;
}

void MyStack::Push(int x) {
  if(top == capacity - 1)     // if the stack is full, double the capacity
    DoubleCapacity();
  stack[++top] = x;
}

void MyStack::Pop() {
  if(isEmpty()) {
    cout << "The stack is empty." << endl;
    return;
  }
  else
    top--;
}

int MyStack::Top() {
  if(isEmpty()) {
    cout << "The stack is empty." << endl;
    return -1;
  }
  else
    return stack[top];
}

int MyStack::getSize() {
  return top + 1;
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
