#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
  public:
    MinStack(){};

    void Push(int x);
    void Pop();
    bool isEmpty();
    int Top();
    int getSize();
    int getMin();
};

void MinStack::Push(int x) {
  dataStack.push(x);
  if(minStack.empty() || x < minStack.top())
    minStack.push(x);
  else
    minStack.push(minStack.top());
}

void MinStack::Pop() {
  if(isEmpty())
    cout << "The stack is empty" << endl;
  else {
    dataStack.pop();
    minStack.pop();
  }
}

bool MinStack::isEmpty() {
  return dataStack.empty();
}

int MinStack::Top() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return -1;
  }
  else
    return dataStack.top();
}

int MinStack::getSize() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return -1;
  }
  else
    return dataStack.size();
}

int MinStack::getMin() {
  if(isEmpty()) {
    cout << "The stack is empty" << endl;
    return -1;
  }
  else
    return minStack.top();
}

int main() {
  MinStack s;
  s.Pop();
  s.Push(6);
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Push(13);
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Push(4);
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Push(9);
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Push(1);
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Pop();
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Pop();
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Pop();
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Pop();
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  s.Pop();
  cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

  return 0;
}
