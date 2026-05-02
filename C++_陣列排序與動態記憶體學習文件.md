# C++ 陣列排序與動態記憶體學習文件

> 對應程式：`cpp0501/arraysort.cpp`
> 主題：動態陣列（Dynamic Array）、泡泡排序（Bubble Sort）、亂數產生（Random Number Generation）

---

## 整體功能說明

此程式示範三件事：
1. 用 `new` 動態配置一個整數陣列，並以亂數填入 1–100 的值
2. 對陣列執行泡泡排序（由小到大）
3. 印出排序結果後，用 `delete[]` 釋放記憶體

---

## 逐區塊解析

### 1. 引入標頭檔

```cpp
#include <iostream>
#include <ctime>
using namespace std;
```

| 標頭 | 用途 |
|------|------|
| `<iostream>` | 標準輸入／輸出（`cout`） |
| `<ctime>` | 提供 `time()` 函式，用於設定亂數種子 |

---

### 2. `create()` — 建立並填入亂數陣列

```cpp
int* create(int size) {
    int* arr = new int[size];   // 在 Heap（堆積）配置 size 個 int
    srand(time(0));             // 以當前時間設定亂數種子，確保每次執行不同
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1; // 產生 1~100 的亂數
        cout << arr[i] << " ";
    }
    cout << endl;
    return arr;                 // 回傳指標（呼叫端需負責 delete[]）
}
```

**重點概念：**

- `new int[size]`：在 **Heap** 上配置陣列，不會在函式結束時自動釋放
- `srand(time(0))`：**亂數種子（seed）**，`time(0)` 回傳 Unix 時間戳，讓每次執行產生不同序列
- `rand() % 100 + 1`：`rand()` 產生 0~RAND_MAX 的整數，`% 100` 限制在 0–99，`+1` 平移至 1–100
- 函式回傳 `int*`（指標），記憶體擁有權轉移給呼叫端

---

### 3. `mysort()` — 泡泡排序

```cpp
void mysort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {          // 外層：共需 size-1 輪
        for (int j = 0; j < size - i - 1; j++) {  // 內層：每輪比較範圍縮小
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);           // 相鄰互換
            }
        }
    }
}
```

**泡泡排序（Bubble Sort）原理：**

每一輪將目前未排序區間中的「最大值」像泡泡一樣浮到最右端。

```
初始：  [64, 34, 25, 12, 22]
第1輪：  34  25  12  22  [64]   ← 64 就定位
第2輪：  25  12  22  [34][64]   ← 34 就定位
...
最終：  [12, 22, 25, 34, 64]
```

- **時間複雜度（Time Complexity）**：最壞 O(n²)，最好 O(n)（若加提前結束旗標）
- **空間複雜度（Space Complexity）**：O(1)（原地排序）
- `swap(a, b)`：C++ 標準函式，交換兩變數的值（定義在 `<algorithm>`，`using namespace std` 後可直接用）

---

### 4. `main()` — 主程式

```cpp
int main() {
    int* arr = create(10);    // 建立 10 個亂數元素的陣列
    mysort(arr, 10);          // 排序
    cout << "Sorted array: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;             // 釋放動態配置的記憶體，避免記憶體洩漏
    return 0;
}
```

**`delete[]` 規則：**
- 用 `new[]` 配置的陣列 → 必須用 `delete[]` 釋放
- 用 `new` 配置的單一物件 → 用 `delete` 釋放
- 忘記釋放 → **記憶體洩漏（Memory Leak）**

---

## 執行範例

```
產生亂數：47 82 13 95 6 61 28 74 39 50
Sorted array: 6 13 28 39 47 50 61 74 82 95
```

---

## 常見陷阱

| 問題 | 說明 |
|------|------|
| 忘記 `delete[]` | 造成 Memory Leak，長時間執行會耗盡記憶體 |
| 用 `delete` 而非 `delete[]` | 未定義行為（Undefined Behavior），可能崩潰 |
| `srand()` 放在迴圈內 | 若每次呼叫時間戳相同，會產生相同亂數序列 |
| `rand() % 100` | 範圍是 0–99；要 1–100 需 `+1` |
| 陣列越界（Out-of-bounds） | `size - i - 1` 確保內層不超出已排序區域 |

---

## 學習筆記摘要

```
動態陣列：  new int[n]  →  使用完後  delete[] arr
亂數：      srand(time(0)) 設種子；rand() % N + offset 取值
泡泡排序：  外層 n-1 輪，內層每輪縮減，相鄰比較互換
指標回傳：  函式可回傳 new 出的指標，呼叫端負責 delete[]
```

---

## 現在試試看

1. **修改範圍**：把亂數改為 50–150（`rand() % 101 + 50`），觀察輸出
2. **加入提前結束**：在泡泡排序加入 `bool swapped` 旗標，若某輪沒有交換就提早結束
3. **改為由大到小**：將 `arr[j] > arr[j+1]` 改為 `arr[j] < arr[j+1]`
4. **計算比較次數**：在 `if` 判斷前加計數器，觀察不同輸入下的比較次數

---

## 關聯知識點

- [C++\_動態記憶體配置學習文件.md](./C++_動態記憶體配置學習文件.md)
- [C++\_Array學習文件.md](./C++_Array學習文件.md)
- [C++\_Pointer學習文件.md](./C++_Pointer學習文件.md)
