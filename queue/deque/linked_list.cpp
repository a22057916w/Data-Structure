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

void MyDeque:push_front(int x) {

}
