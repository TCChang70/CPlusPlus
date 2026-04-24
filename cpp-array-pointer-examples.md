# C++ 陣列與指標：5 題經典程式範例

**語言：** C++  
**對應文件：** [cpp-array-pointer-learning.md](./cpp-array-pointer-learning.md)  
**日期：** 2026-04-24  

---

## 範例 1：氣泡排序法（Bubble Sort）

**對應主題：** 陣列走訪、元素交換

```cpp
#include <iostream>
using namespace std;

void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j]   = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, size);

    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    // 輸出：11 12 22 25 34 64 90
}
```

> 重點：陣列傳入函式後退化為指標，搭配 `size` 參數才能正確走訪。

---

## 範例 2：用指標實作 Swap（交換兩數）

**對應主題：** 傳址呼叫（Pass by Reference via Pointer）

```cpp
#include <iostream>
using namespace std;

void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    cout << "交換前：x=" << x << ", y=" << y << endl;

    swapByPointer(&x, &y);  // 傳入位址，函式內可修改原始值

    cout << "交換後：x=" << x << ", y=" << y << endl;
    // 輸出：x=20, y=10
}
```

> 重點：若用傳值（Pass by Value），函式內的修改不影響外部。只有傳址才能真正交換。

---

## 範例 3：用指標算術走訪字串

**對應主題：** 指標算術（Pointer Arithmetic）、陣列名稱即位址

```cpp
#include <iostream>
using namespace std;

int strLength(const char* s) {
    const char* p = s;
    while (*p != '\0')  // C 字串以 '\0' 結尾
        p++;
    return p - s;  // 指標相減 = 字元數
}

int main() {
    const char* word = "Hello";
    cout << "字串：" << word << endl;
    cout << "長度：" << strLength(word) << endl;  // 5

    // 用指標逐字元印出
    const char* p = word;
    while (*p != '\0') {
        cout << *p << " ";
        p++;
    }
    // 輸出：H e l l o
}
```

> 重點：`p - s` 是指標相減，結果為兩個位址之間的元素個數，這是計算長度的經典技巧。

---

## 範例 4：動態配置二維陣列（乘法表）

**對應主題：** `new` / `delete[]`、指向指標的指標（`int**`）

```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 4;

    // 動態配置 n x n 的二維陣列
    int** table = new int*[n];
    for (int i = 0; i < n; i++)
        table[i] = new int[n];

    // 填入乘法表
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = (i + 1) * (j + 1);

    // 印出
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << table[i][j] << "\t";
        cout << endl;
    }

    // 釋放記憶體（順序：先 delete[] 每一列，再 delete[] 整個指標陣列）
    for (int i = 0; i < n; i++)
        delete[] table[i];
    delete[] table;
    table = nullptr;
}
```

**執行結果：**
```
1    2    3    4
2    4    6    8
3    6    9    12
4    8    12   16
```

> 重點：二維動態陣列要**逐列釋放**，順序不能反，否則會造成記憶體錯誤。

---

## 範例 5：二分搜尋法（Binary Search）回傳指標

**對應主題：** 陣列 + 指標回傳值、指標相減求索引

```cpp
#include <iostream>
using namespace std;

// 在已排序陣列中搜尋 target，找到回傳指向該元素的指標，找不到回傳 nullptr
int* binarySearch(int* arr, int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // 避免 (left+right) 整數溢位

        if (arr[mid] == target)  return &arr[mid];
        else if (arr[mid] < target) left = mid + 1;
        else                        right = mid - 1;
    }
    return nullptr;
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);

    int target = 23;
    int* result = binarySearch(arr, size, target);

    if (result != nullptr)
        cout << "找到 " << target << "，索引：" << (result - arr) << endl;
    else
        cout << "找不到 " << target << endl;
    // 輸出：找到 23，索引：5
}
```

> 重點：回傳指標而非索引，讓呼叫端可以直接修改該元素；`result - arr` 利用指標相減換算出索引。

---

## 5 題重點對照

| # | 範例 | 核心概念 |
|---|------|---------|
| 1 | 氣泡排序 | 陣列走訪、元素交換、陣列退化為指標 |
| 2 | 指標 Swap | 傳址呼叫、`&` 取址、`*` 解參考 |
| 3 | 指標走訪字串 | 指標算術、`*p++`、指標相減求長度 |
| 4 | 動態二維陣列 | `int**`、`new[]` / `delete[]`、記憶體管理 |
| 5 | 二分搜尋 | 指標回傳值、`nullptr` 判斷、指標相減求索引 |
