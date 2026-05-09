# 第 1 週 程式碼解析：陣列與記憶體配置

> 對應練習檔：`week1_array_practice.cpp`  
> 對應學習文件：[DS_Week1_Array_Memory.md](DS_Week1_Array_Memory.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔共包含 **4 個範例函式** 與 **4 道練習題**，涵蓋三大核心主題：

| 編號 | 函式 | 主題 |
|------|------|------|
| 範例 1 | `example1_address()` | 一維陣列位址驗證 |
| 範例 2 | `example2_2d_array()` | 二維陣列 Row-major 走訪 |
| 範例 3 & 4 | `example3_binary_search()` | Binary Search 遞迴版 + 迭代版 |
| 練習 1 | `practice1_address_calc()` | 位址公式驗算 |
| 練習 2 | `practice2_count_comparisons()` | 計算 Binary Search 比較次數 |
| 練習 3 | `practice3_column_major()` | Column-major 位址計算 |
| 練習 4 | `practice4_compare_search()` | Linear vs Binary 效率比較 |

---

## 範例 1：一維陣列位址驗證

### 程式碼

```cpp
int arr[5] = {10, 20, 30, 40, 50};

for (int i = 0; i < 5; i++) {
    cout << "arr[" << i << "] = " << arr[i]
         << "\t位址 = " << &arr[i] << endl;
}

long long diff = (long long)&arr[1] - (long long)&arr[0];
cout << "相鄰元素位址差 = " << diff << " bytes" << endl;
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `int arr[5] = {10, 20, 30, 40, 50}` | 宣告 5 個 int 的陣列，佔連續的 $5 \times 4 = 20$ bytes |
| `&arr[i]` | 取得第 i 個元素的**記憶體位址 (memory address)**，`&` 為取址運算子 |
| `(long long)&arr[1] - (long long)&arr[0]` | 計算兩個指標的差值，需轉型為整數才能做減法 |

### 關鍵概念

位址公式：
$$\text{Address}(A[i]) = A + i \times d$$

其中 $A$ = 基底位址，$d$ = `sizeof(int)` = 4 bytes。  
因此相鄰元素位址差必定為 **4 bytes**。

### 常見陷阱

- `&arr[i]` 是指標型別，不能直接相減後存入 `int`，應使用 `long long` 或 `ptrdiff_t`。
- `sizeof(arr)` 回傳整個陣列的 bytes 數；`sizeof(arr[0])` 才是單一元素大小。

---

## 範例 2：二維陣列 Row-major 走訪

### 程式碼

```cpp
int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
// n = 欄數 = 3, d = sizeof(int) = 4

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
        cout << "A[" << i << "][" << j << "] = " << A[i][j]
             << "\t位址 = " << &A[i][j] << endl;
    }
}
```

### 逐行解析

C++ 二維陣列以 **Row-major（列主序）** 儲存：先存完第 0 列，再存第 1 列…

```
記憶體排列：A[0][0] A[0][1] A[0][2] A[1][0] A[1][1] A[1][2]
             1000    1004    1008    1012    1016    1020
```

Row-major 位址公式：
$$\text{Address}(A[i][j]) = A + (i \times n + j) \times d$$

其中 $n$ = 每列的欄數（columns），本例 $n = 3$。

### 常見陷阱

- 雙層迴圈走訪時，**外迴圈走列 (row)、內迴圈走欄 (column)** 才符合 Row-major 的記憶體順序，快取命中率 (cache hit rate) 較高。
- 若外迴圈走欄、內迴圈走列（Column-major 走法），在大型陣列上效能會明顯下降。

---

## 範例 3 & 4：Binary Search（二元搜尋法）

### 遞迴版 `binarySearch`

```cpp
int binarySearch(int arr[], int left, int right, int target) {
    if (left > right)                      // 基底條件：搜尋範圍為空
        return -1;

    int mid = left + (right - left) / 2;   // 安全計算中間索引

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return binarySearch(arr, left, mid - 1, target);  // 搜左半
    else
        return binarySearch(arr, mid + 1, right, target); // 搜右半
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `if (left > right) return -1` | 基底條件 (base case)：搜尋區間已空，表示找不到 |
| `mid = left + (right - left) / 2` | 避免 `(left + right) / 2` 在 left + right 超過 `INT_MAX` 時溢位 (overflow) |
| `arr[mid] > target` | 目標值在左半，縮小右邊界 |
| `arr[mid] < target` | 目標值在右半，縮小左邊界 |

### 迭代版 `binarySearchIter`

```cpp
int binarySearchIter(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)  return mid;
        else if (arr[mid] < target) left  = mid + 1;
        else                        right = mid - 1;
    }
    return -1;
}
```

迭代版與遞迴版邏輯相同，但**不使用 Call Stack**，空間複雜度為 $O(1)$（遞迴版為 $O(\log n)$）。

### 時間複雜度分析

| 操作 | 複雜度 |
|------|--------|
| 最佳（目標在正中間） | $O(1)$ |
| 平均 / 最壞 | $O(\log n)$ |

每次迭代將搜尋範圍**砍半**，最多 $\lceil \log_2 n \rceil$ 次。

### 前提條件

> **Binary Search 只能用在已排序 (sorted) 的陣列上！**

---

## 練習題 1：位址公式驗算

```cpp
int B[3][4] = {};
long long base = (long long)&B[0][0];
int d = sizeof(int);    // = 4
int n_cols = 4;
long long calc = base + (2 * n_cols + 3) * d;
```

套用公式 $\text{Address}(B[2][3]) = \text{base} + (2 \times 4 + 3) \times 4$，並與 `&B[2][3]` 的實際值比對，驗證公式正確性。

---

## 練習題 2：計算 Binary Search 比較次數

```cpp
int binarySearchCount(int arr[], int n, int target, int& count) {
    int left = 0, right = n - 1;
    count = 0;
    while (left <= right) {
        count++;                            // 每次進迴圈算一次比較
        int mid = left + (right - left) / 2;
        ...
    }
}
```

- `count` 以**傳參考 (pass by reference)** 傳入，函式內的修改會直接反映到呼叫端。
- 對 $n = 1024$ 的陣列，最多比較 $\log_2 1024 = 10$ 次。

---

## 練習題 3：Column-major 位址計算

Column-major（行主序）公式：
$$\text{Address}(A[i][j]) = A + (j \times m + i) \times d$$

其中 $m$ = 列數（rows）。

```cpp
long long addr = base + (j * m + i) * d;  // Column-major
long long addr_row = base + (i * n_cols + j) * d;  // Row-major（對比）
```

> C++ 本身是 Row-major，Column-major 常見於 Fortran / MATLAB。

---

## 練習題 4：Linear vs Binary Search 效率比較

```cpp
linearSearch(arr, N, testVal, cLinear);
binarySearchCount(arr, N, testVal, cBinary);
cout << "效率差距：約 " << cLinear / (float)cBinary << " 倍" << endl;
```

對 $N = 1000$ 的陣列搜尋接近末端的值：
- Linear Search (線性搜尋)：接近 $N = 1000$ 次比較，$O(n)$
- Binary Search：最多 $\lceil \log_2 1000 \rceil = 10$ 次，$O(\log n)$
- 效率差距約 **100 倍**

---

## 學習筆記摘要

```
【Week 1 重點整理】

✅ 位址公式
   一維：Address(A[i])    = A + i × d
   二維 Row-major：        = A + (i×n + j) × d
   二維 Column-major：     = A + (j×m + i) × d

✅ Binary Search 前提
   陣列必須已排序 (sorted)，否則結果不可預測

✅ 中間索引安全寫法
   mid = left + (right - left) / 2   ← 避免溢位
   不用：mid = (left + right) / 2    ← 可能溢位

✅ 遞迴 vs 迭代 Binary Search
   遞迴版：空間 O(log n)（Call Stack）
   迭代版：空間 O(1)，實務上更優先

⚠️ 常見陷阱
   1. 指標相減需轉型為 long long / ptrdiff_t
   2. sizeof(arr) ≠ sizeof(arr[0])
   3. 二維走訪：外列內欄 = 效能最佳（快取友善）
```

---

> 現在試試看：修改 `practice2_count_comparisons`，改為搜尋**陣列第一個元素**，觀察最佳情況下只需幾次比較。
