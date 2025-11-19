#include "heap.h"
#include <stdio.h>
#include <assert.h>

void test_basic_insert_extract() {
    MaxHeap* h = heap_create(20);

    int a = 10, b = 5, c = 30, d = 20;

    heap_insert(h, a);
    heap_insert(h, b);
    heap_insert(h, c);
    heap_insert(h, d);

    int out;

    // 最大值應該是 30
    assert(heap_peak(h, &out) == true);
    assert(out == 30);

    // extract 順序：30, 20, 10, 5
    assert(heap_extract(h, &out) == true);
    assert(out == 30);

    assert(heap_extract(h, &out) == true);
    assert(out == 20);

    assert(heap_extract(h, &out) == true);
    assert(out == 10);

    assert(heap_extract(h, &out) == true);
    assert(out == 5);

    // 已經空了
    assert(heap_extract(h, &out) == false);
    assert(heap_peak(h, &out) == false);

    assert(heap_is_empty(h));

    heap_free(h);
}


void test_insert_array() {
    MaxHeap* h = heap_create(20);

    int vals[] = {4, 1, 7, 3, 9, 2};
    int n = sizeof(vals)/sizeof(vals[0]);

    for (int i = 0; i < n; i++)
        heap_insert(h, vals[i]);

    int out;
    heap_peak(h, &out);
    assert(out == 9);     // 最大值應該永遠是 9

    // 逐步 extract 應該由大到小
    int last = 9999;
    while (heap_extract(h, &out)) {
        assert(out <= last);
        last = out;
    }

    assert(heap_is_empty(h));

    heap_free(h);
}

void test_capacity_limit() {
    MaxHeap* h = heap_create(3);

    int a = 10, b = 20, c = 30, d = 40;

    heap_insert(h, a);
    heap_insert(h, b);
    heap_insert(h, c);

    // 第四個會 overflow，但你的 API 是打印訊息然後忽略
    heap_insert(h, d);

    int out;
    heap_peak(h, &out);
    assert(out == 30);

    heap_free(h);
}

int main() {
    printf("Running Heap tests...\n");

    test_basic_insert_extract();
    test_insert_array();
    test_capacity_limit();

    printf("All Heap tests passed successfully!\n");
    return 0;
}
