#include <cstdio>
#include <cstdlib>
const int global_x = 1;  // 儲存於 data 區段(唯讀區域)
int global_y = 2;        // 儲存於 data 區段(可讀寫區域)
int global_z;            // 儲存於 bss 區段
int main() {
  const static int x = 1; // 儲存於 data 區段（唯讀區域）
  static int y = 1;       // 儲存於 data 區段（可讀寫區域）
  static int z;           // 儲存於 bss 區段
  int w = 1;              // 儲存於 stack 區段

  // 儲存於 heap 區段
  char *buf = (char*) malloc(sizeof(char) * 100);
  // ...
  free(buf);

  return 0;
}
