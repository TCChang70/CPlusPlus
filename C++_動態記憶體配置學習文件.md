# C++ 動態記憶體配置學習文件

> 參考來源：https://cplusplus.com/doc/tutorial/dynamic/

## 目錄

1. [為什麼需要動態記憶體配置](#為什麼需要動態記憶體配置)
2. [靜態配置 vs 動態配置](#靜態配置-vs-動態配置)
3. [運算子 new 與 new\[\]](#運算子-new-與-new)
4. [運算子 delete 與 delete\[\]](#運算子-delete-與-delete)
5. [配置失敗的處理](#配置失敗的處理)
6. [完整範例：動態陣列輸入](#完整範例動態陣列輸入)
7. [C 語言的動態記憶體函式](#c-語言的動態記憶體函式)
8. [常見錯誤與最佳實踐](#常見錯誤與最佳實踐)
9. [學習重點摘要](#學習重點摘要)

---

## 為什麼需要動態記憶體配置

在先前學過的程式中，所有變數和陣列的記憶體需求都必須在**編譯時期 (compile time)** 就決定好。但現實情境中，程式所需的記憶體大小往往只有在**執行期 (runtime)** 才能知道。

### 舉例說明

```
情境：使用者想輸入 N 個數字，但 N 由使用者決定

❌ 靜態方式（有限制）：
   int arr[100];   // 最多只能 100 個，太死板

✅ 動態方式（彈性）：
   int n;
   cin >> n;
   int* arr = new int[n];  // 執行時才決定大小
```

---

## 靜態配置 vs 動態配置

| 比較項目 | 靜態配置 Static | 動態配置 Dynamic |
|----------|----------------|-----------------|
| 大小決定時機 | 編譯時期 | 執行時期 |
| 存放位置 | 堆疊（Stack） | 堆積（Heap） |
| 生命週期 | 自動（離開範圍即釋放） | 手動（需呼叫 `delete`） |
| 宣告方式 | `int arr[10];` | `int* arr = new int[10];` |
| 大小可否為變數 | ❌ 必須是常數 | ✅ 可以是變數 |

### 記憶體區域示意圖

```
程式記憶體配置：
┌────────────────────┐  ← 高位址
│      Stack（堆疊）  │  ← 區域變數、函式呼叫
│         ↓          │
│                    │
│         ↑          │
│      Heap（堆積）   │  ← new 配置的記憶體
├────────────────────┤
│   靜態/全域資料區   │
├────────────────────┤
│      程式碼區       │
└────────────────────┘  ← 低位址
```

---

## 運算子 new 與 new[]

### 語法結構

```cpp
// 配置單一元素
pointer = new type;

// 配置陣列（多個元素）
pointer = new type [number_of_elements];
```

### 範例一：配置單一整數

```cpp
#include <iostream>
using namespace std;

int main() {
    int* p;
    p = new int;      // 在 Heap 上配置一個 int 的空間
    *p = 42;          // 透過指標存入值
    cout << *p << endl;  // 輸出：42
    delete p;         // 使用完畢後釋放
    return 0;
}
```

### 範例二：配置整數陣列

```cpp
#include <iostream>
using namespace std;

int main() {
    int* foo;
    foo = new int[5];  // 在 Heap 上配置 5 個 int 的連續空間

    // 存取方式和一般陣列相同
    foo[0] = 10;
    foo[1] = 20;
    // 也可用指標算術：*(foo+2) = 30;

    for (int i = 0; i < 5; i++) {
        cout << foo[i] << " ";
    }

    delete[] foo;  // 釋放陣列（注意是 delete[]）
    return 0;
}
```

### 記憶體配置示意圖

```
foo = new int[5]; 執行後：

foo ──→ ┌──────┬──────┬──────┬──────┬──────┐
        │ [0]  │ [1]  │ [2]  │ [3]  │ [4]  │
        │  10  │  20  │  ?   │  ?   │  ?   │
        └──────┴──────┴──────┴──────┴──────┘
          ↑
          foo 指向第一個元素
```

---

## 運算子 delete 與 delete[]

配置的動態記憶體在不需要時**必須手動釋放**，否則會造成**記憶體洩漏 (memory leak)**。

### 語法結構

```cpp
delete pointer;     // 釋放單一元素
delete[] pointer;   // 釋放陣列
```

### 對應規則（非常重要！）

```
new      ↔  delete
new[]    ↔  delete[]
```

> ⚠️ 用 `new` 配置的記憶體用 `delete[]` 釋放（反之亦然）是**未定義行為 (undefined behavior)**！

### 範例：正確的配置與釋放

```cpp
#include <iostream>
using namespace std;

int main() {
    // 單一元素
    int* a = new int(100);  // 配置並初始化為 100
    cout << *a << endl;
    delete a;               // ✅ 用 delete
    a = nullptr;            // 良好習慣：釋放後設為 nullptr

    // 陣列
    double* arr = new double[3];
    arr[0] = 1.1; arr[1] = 2.2; arr[2] = 3.3;
    delete[] arr;           // ✅ 用 delete[]
    arr = nullptr;

    return 0;
}
```

---

## 配置失敗的處理

動態記憶體來自系統的 **Heap（堆積）**，當系統記憶體不足時，配置可能會失敗。C++ 提供兩種處理方式：

### 方式一：例外處理（預設行為）

```cpp
// 配置失敗時，拋出 bad_alloc 例外
int* p = new int[1000000000];  // 嘗試配置約 4GB
// 若失敗，程式會拋出 std::bad_alloc
```

使用 `try-catch` 捕捉：

```cpp
#include <iostream>
#include <new>       // bad_alloc 定義在此
using namespace std;

int main() {
    try {
        int* p = new int[1000000000];
        // ... 使用 p
        delete[] p;
    } catch (bad_alloc& e) {
        cout << "記憶體配置失敗：" << e.what() << endl;
    }
    return 0;
}
```

### 方式二：nothrow（不拋出例外，回傳 nullptr）

```cpp
#include <iostream>
#include <new>       // nothrow 定義在此
using namespace std;

int main() {
    int* foo = new (nothrow) int[5];  // 失敗時回傳 nullptr，不拋出例外

    if (foo == nullptr) {
        cout << "Error: 記憶體無法配置" << endl;
    } else {
        // 正常使用
        foo[0] = 10;
        delete[] foo;
    }
    return 0;
}
```

### 兩種方式比較

| 比較 | 例外（預設） | nothrow |
|------|------------|---------|
| 失敗時 | 拋出 `bad_alloc` | 回傳 `nullptr` |
| 效能 | 較高 | 較低（每次需檢查） |
| 適用場景 | 一般情況（推薦） | 需要細粒度控制時 |

---

## 完整範例：動態陣列輸入

以下程式示範根據使用者輸入的數量，動態配置陣列後存入並印出：

```cpp
// rememb-o-matic：動態記憶使用者輸入的數字
#include <iostream>
#include <new>
using namespace std;

int main() {
    int i, n;
    int* p;

    cout << "How many numbers would you like to type? ";
    cin >> i;

    p = new (nothrow) int[i];  // 依使用者輸入動態配置陣列

    if (p == nullptr) {
        cout << "Error: memory could not be allocated" << endl;
    } else {
        for (n = 0; n < i; n++) {
            cout << "Enter number: ";
            cin >> p[n];
        }

        cout << "You have entered: ";
        for (n = 0; n < i; n++) {
            cout << p[n] << ", ";
        }
        cout << endl;

        delete[] p;  // 釋放動態配置的陣列
    }

    return 0;
}
```

**執行結果範例：**
```
How many numbers would you like to type? 5
Enter number: 75
Enter number: 436
Enter number: 1067
Enter number: 8
Enter number: 32
You have entered: 75, 436, 1067, 8, 32,
```

**程式重點說明：**
- `new (nothrow) int[i]`：`i` 是執行期才知道的變數，這是動態配置的關鍵優勢
- `if (p == nullptr)`：使用 nothrow 時務必檢查配置是否成功
- `delete[] p`：陣列用 `new[]` 配置，所以用 `delete[]` 釋放

---

## C 語言的動態記憶體函式

C++ 向下相容 C，所以也可以使用 C 語言的動態記憶體函式（定義在 `<cstdlib>`）：

| 函式 | 功能 |
|------|------|
| `malloc(size)` | 配置 `size` bytes，不初始化 |
| `calloc(n, size)` | 配置 `n` 個 `size` bytes，初始化為 0 |
| `realloc(ptr, size)` | 重新調整已配置記憶體大小 |
| `free(ptr)` | 釋放記憶體 |

```cpp
#include <cstdlib>
using namespace std;

int main() {
    // C 風格配置（在 C++ 中不推薦）
    int* p = (int*)malloc(5 * sizeof(int));
    if (p != nullptr) {
        p[0] = 10;
        free(p);  // 對應 malloc 使用 free，不是 delete
    }
    return 0;
}
```

> ⚠️ **重要警告**：`new`/`delete` 與 `malloc`/`free` **不可混用**！
> - `new` 配置的記憶體只能用 `delete` 釋放
> - `malloc` 配置的記憶體只能用 `free` 釋放

**在 C++ 中建議優先使用 `new`/`delete`**，因為它們會自動呼叫建構子與解構子。

---

## 常見錯誤與最佳實踐

### ❌ 常見錯誤

#### 1. 記憶體洩漏 (Memory Leak)

```cpp
// ❌ 錯誤：忘記釋放
void bad_function() {
    int* p = new int[100];
    // ... 使用 p
    // 忘記 delete[] p！
    // 函式結束後 p 變數消失，但 Heap 上的記憶體永遠無法回收
}
```

#### 2. 懸空指標 (Dangling Pointer)

```cpp
// ❌ 錯誤：釋放後仍使用
int* p = new int(10);
delete p;
cout << *p;  // 未定義行為！p 指向已釋放的記憶體
```

#### 3. 重複釋放 (Double Free)

```cpp
// ❌ 錯誤：釋放兩次
int* p = new int(10);
delete p;
delete p;  // 未定義行為！
```

#### 4. 錯誤的 delete 類型

```cpp
// ❌ 錯誤：用 delete 釋放陣列
int* arr = new int[10];
delete arr;   // 應該是 delete[] arr
```

### ✅ 最佳實踐

```cpp
// ✅ 良好習慣示範
int* p = new int[10];

// ... 使用 p

delete[] p;      // 正確釋放
p = nullptr;     // 釋放後設為 nullptr，防止懸空指標

// 此後對 nullptr 的 delete 不會造成問題
delete[] p;      // delete nullptr 是安全的（無作用）
```

### 最佳實踐總結

| 規則 | 說明 |
|------|------|
| `new` 對應 `delete` | 一對一配對，不可混用 |
| `new[]` 對應 `delete[]` | 陣列必須用 `delete[]` |
| 釋放後設 `nullptr` | 避免懸空指標問題 |
| 考慮使用智慧指標 | C++11 的 `unique_ptr`/`shared_ptr` 可自動管理 |
| 每次配置後檢查 | 使用 nothrow 時必須檢查是否為 nullptr |

---

## 學習重點摘要

```
動態記憶體配置核心概念：

1. 配置（Allocation）
   new type          → 配置單一元素
   new type[n]       → 配置 n 個元素的陣列

2. 使用（Usage）
   與一般指標 / 陣列相同方式存取

3. 釋放（Deallocation）
   delete p          → 釋放單一元素
   delete[] p        → 釋放陣列
   p = nullptr       → 良好習慣

4. 失敗處理
   預設：拋出 bad_alloc 例外
   nothrow：回傳 nullptr，需手動檢查

5. 避免的問題
   - 記憶體洩漏 Memory Leak
   - 懸空指標 Dangling Pointer
   - 重複釋放 Double Free
   - 混用 new/delete 與 malloc/free
```

---

## 現在試試看

完成以下練習來鞏固學習：

1. **初級**：宣告一個動態整數指標，存入你的年齡，印出後正確釋放。
2. **中級**：讓使用者輸入 N，動態配置 N 個 `double` 陣列，輸入 N 個成績後計算平均值，最後正確釋放陣列。
3. **進階**：動態配置一個 M×N 的二維整數陣列（使用 `int**`），填入數值後印出，並完整釋放所有記憶體。

---

*資料來源：[cplusplus.com - Dynamic memory](https://cplusplus.com/doc/tutorial/dynamic/)*
