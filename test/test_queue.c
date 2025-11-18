#include "queue.h"
#include <stdio.h>
#include <assert.h>

void test_basic_push_pop() {
    Queue* q = queue_create();
    int a = 10, b = 20, c = 30;

    queue_push(q, &a);
    queue_push(q, &b);
    queue_push(q, &c);

    assert(*(int*)queue_front(q) == 10);
    assert(*(int*)queue_rear(q) == 30);
    assert(queue_size(q) == 3);

    queue_pop(q);
    assert(*(int*)queue_front(q) == 20);
    assert(queue_size(q) == 2);

    queue_pop(q);
    assert(*(int*)queue_front(q) == 30);
    assert(queue_size(q) == 1);

    queue_pop(q);
    assert(queue_isEmpty(q));

    queue_free(q);
}

void test_empty_pop() {
    Queue* q = queue_create();

    queue_pop(q);    // 應該不會 crash
    assert(queue_isEmpty(q));

    queue_free(q);
}

void test_push_front_rear() {
    Queue* q = queue_create();

    int x = 99;
    int y = 100;

    queue_push(q, &x);
    assert(*(int*)queue_front(q) == 99);
    assert(*(int*)queue_rear(q)  == 99);

    queue_push(q, &y);
    assert(*(int*)queue_front(q) == 99);
    assert(*(int*)queue_rear(q)  == 100);

    queue_free(q);
}

int main() {
    printf("Running Queue tests...\n");

    test_basic_push_pop();
    test_empty_pop();
    test_push_front_rear();

    printf("All Queue tests passed successfully!\n");
    return 0;
}