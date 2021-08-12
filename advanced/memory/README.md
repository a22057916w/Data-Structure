[![hackmd-github-sync-badge](https://hackmd.io/eDLdyYl-S869xwHC3mwWJg/badge)](https://hackmd.io/eDLdyYl-S869xwHC3mwWJg)
# C 語言程式記憶體配置概念
下圖為典型的 C 語言程式在執行時的記憶體配置圖，記憶體的使用主要可分為 text、data、bss、stack、heap 與 system 這幾個部分。


<div align="center">
  <img src="https://i.imgur.com/VcIHLOp.png" width="50%" height="70%">
</div>


以下是各個區塊的說明。

### **text：程式碼**
文字區段（text segment）也稱為程式碼區段（code segment），這裡存放的是**可執行的 CPU 指令（instructions）**。

這個區段通常位於 heap 或 stack 之後，避免因 heap 或 stack 溢位而覆寫 CPU 指令。

通常文字區段的資料是**可以共用的**，當多個同樣的程式在執行時，在記憶體中只需要存有一份就夠了，而這個文字區段通常都是唯讀的，避免程式本身誤改了自己的 CPU 指令。

### **data：初始化靜態變數**
初始化資料區段（initialized data segment）儲存的是一些已經初始化的**靜態變數**，例如有經過初始化的 C 語言的**全域變數**（global variables）以及靜態變數（static variables）都是儲存於此處。

這個區段的變數又可分為唯讀區域（read-only area）以及可讀寫區域（read-write area），可讀寫區域用於存放一般變數，其資料會隨著程式的執行而改變，而唯讀區域則是存放固定的常數。

### **bss：未初始化靜態變數**
未初始化資料區段（uninitialized data segment）又稱為 **bss** 區段（這個名稱的起源來自於古老的組譯器，代表 block started by symbol）是儲存**尚未被初始化的靜態變數**，而這些變數在程式執行之前會被系統初始化為 0 或是 null。

### **stack：區域變數**
堆疊區段（stack segment）用於儲存**函數**的區域變數，以及各種函數呼叫時需要儲存的資訊（例如函數返回的記憶體位址還有呼叫者函數的狀態等），每一次的函數呼叫就會在堆疊區段建立一個 **stack frame**，儲存該次呼叫的所有變數與狀態，這樣一來同一個函數重複被呼叫時就會有不同的 stack frame，不會互相干擾，遞迴函數就是透過這樣的機制來執行的。

### **heap：動態配置變數**
heap 區段的記憶體空間用於儲存動態配置的變數，例如 C 語言的 **malloc** 以及 C++ 的 **new**

堆疊區段一般的狀況會從高記憶體位址往低記憶體位址成長，而 heap 剛好從對面以相反的方向成長。

### **system：命令列參數與環境變數**
system 區段用於儲存一些命令列參數與環境變數，這部分會跟系統有關。

## 實際範例
這是一個最簡單的 C 語言程式：

```
// main.cpp
#include <cstdio>
int main() {
  return 0;
}
```
編譯之後，可使用`size`查看它的內部記憶體配置：

![](https://github.com/a22057916w/Data-Structure/blob/main/.meta/main_func_size.png)

新增一個未初始化的全域靜態變數：
```
#include <cstdio>
double global[30];  // 儲存於 bss 的未初始化靜態變數
int main() {
  return 0;
}
```
查看內部記憶體配置：

![](https://github.com/a22057916w/Data-Structure/blob/main/.meta/global_var_size.png)

接著增加一個已初始化的靜態變數：
```
#include <cstdioh>
int main() {
  // 儲存於 data 的已初始化靜態變數
  static int x[5] = {1, 2, 3, 4, 5};
  return 0;
}
```
查看內部記憶體配置：

![](https://github.com/a22057916w/Data-Structure/blob/main/.meta/static_var_size.png)

有初始化的靜態變數或全域變數都會被放進 data 區段中。

儲存於 stack 與 heap 的變數在這裡看不到，以下是儲存於各種區段的變數：

```
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
```
![](https://github.com/a22057916w/Data-Structure/blob/main/.meta/all_sector_size.png)

### Reference
* [C 語言程式的記憶體配置概念教學 - G. T. Wang](https://blog.gtwang.org/programming/memory-layout-of-c-program/)
