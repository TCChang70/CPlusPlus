# 第 1 週：陣列與記憶體配置基礎

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、什麼是陣列？ (What is an Array?)

陣列是「**在記憶體中，連續排列的同型別資料集合**」。  
就像一排有編號的信箱：每格大小相同、編號連續，你只要知道第一格的位置與格子編號，就能立刻找到任何一格。

```
索引：   [0]   [1]   [2]   [3]   [4]
值：      10    20    30    40    50
位址：  1000  1004  1008  1012  1016   ← int 每個佔 4 bytes
```

**為什麼重要？**
- 記憶體中連續存放 → 存取速度快（O(1) 隨機存取）
- 所有資料結構的根基（鏈結串列、堆疊、樹都從陣列概念延伸）

---

## 二、一維陣列的記憶體位址計算

若陣列基底位址為 $A$，每個元素佔 $d$ bytes，則：

$$\text{Address}(A[i]) = A + i \times d$$

**範例：** `int arr[5]` 基底位址 = 1000，`int` 佔 4 bytes
- `arr[0]` → $1000 + 0 \times 4 = 1000$
- `arr[3]` → $1000 + 3 \times 4 = 1012$

---

## 三、二維陣列：Row-major vs Column-major

### 3.1 以列為主（Row-major）— C++ 預設

先放第 0 列所有元素，再放第 1 列…

$$\text{Address}(A[i][j]) = A + (i \times n + j) \times d$$

其中 $n$ = 每列的欄數（columns）

```
int A[2][3] =   [0][0] [0][1] [0][2] [1][0] [1][1] [1][2]
記憶體順序：      1000   1004   1008   1012   1016   1020
```

### 3.2 以行為主（Column-major）— Fortran / MATLAB 使用

先放第 0 行所有元素，再放第 1 行…

$$\text{Address}(A[i][j]) = A + (j \times m + i) \times d$$

其中 $m$ = 每行的列數（rows）

> **記憶訣竅**：C++ (C for Column last → Row-major) ；Fortran (F → Column-major)

---

## 四、最小可執行範例

### 4.1 一維陣列宣告與走訪

```cpp
#include <iostream>
using namespace std;

int main() {
    // 宣告並初始化
    int arr[5] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);  // 取得長度 = 5

    // 走訪陣列
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}
```

**輸出：**
```
arr[0] = 10
arr[1] = 20
arr[2] = 30
arr[3] = 40
arr[4] = 50
```

### 4.2 查看實際記憶體位址

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[3] = {100, 200, 300};

    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] 的位址: " << &arr[i]
             << "，值: " << arr[i] << endl;
    }
    // 驗證：相鄰元素位址差 = sizeof(int) = 4
    cout << "位址差: " << (long long)&arr[1] - (long long)&arr[0] << " bytes" << endl;

    return 0;
}
```

### 4.3 二維陣列走訪（Row-major 示範）

```cpp
#include <iostream>
using namespace std;

int main() {
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};

    cout << "二維陣列走訪：" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "A[" << i << "][" << j << "] = " << A[i][j]
                 << "\t位址: " << &A[i][j] << endl;
        }
    }
    return 0;
}
```

---

## 五、二元搜尋法 (Binary Search)

### 5.1 概念說明

在**已排序**的陣列中，每次將搜尋範圍對半縮小：
1. 取中間元素 `mid`
2. 若目標 == `arr[mid]`：找到，回傳
3. 若目標 < `arr[mid]`：往左半搜
4. 若目標 > `arr[mid]`：往右半搜

時間複雜度：$O(\log n)$（比線性搜尋的 $O(n)$ 快得多）

### 5.2 遞迴實作

```cpp
#include <iostream>
using namespace std;

// 遞迴版二元搜尋
// arr[]：已排序陣列，low/high：搜尋範圍，target：目標值
// 回傳：找到的索引，找不到回傳 -1
int binarySearch(int arr[], int low, int high, int target) {
    if (low > high) return -1;  // 基底條件：範圍為空

    int mid = low + (high - low) / 2;  // 避免 (low+high) 整數溢位

    if (arr[mid] == target) return mid;          // 找到
    if (arr[mid] > target)  return binarySearch(arr, low, mid - 1, target);  // 往左
    else                    return binarySearch(arr, mid + 1, high, target); // 往右
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    int result = binarySearch(arr, 0, n - 1, target);

    if (result != -1)
        cout << "找到 " << target << "，索引為: " << result << endl;
    else
        cout << target << " 不在陣列中" << endl;

    return 0;
}
```

**輸出：**
```
找到 23，索引為: 5
```

### 5.3 遞迴呼叫過程視覺化

```
binarySearch(arr, 0, 9, 23)
  mid = 4 → arr[4] = 16 < 23 → 往右
  binarySearch(arr, 5, 9, 23)
    mid = 7 → arr[7] = 56 > 23 → 往左
    binarySearch(arr, 5, 6, 23)
      mid = 5 → arr[5] = 23 == 23 → 找到！回傳 5
```

每次呼叫範圍縮半：$10 \to 5 \to 2 \to 1$，共 3 次，對應 $\lceil \log_2 10 \rceil = 4$

---

## 六、進階應用：陣列作為函式參數

```cpp
#include <iostream>
using namespace std;

// 陣列傳入函式時退化為指標，必須另傳長度 n
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 找陣列中的最大值
int findMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal) maxVal = arr[i];
    return maxVal;
}

int main() {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = sizeof(data) / sizeof(data[0]);

    printArray(data, n);
    cout << "最大值: " << findMax(data, n) << endl;

    return 0;
}
```

---

## 七、常見錯誤與注意事項

| 錯誤類型 | 錯誤範例 | 正確做法 |
|---------|---------|---------|
| 陣列越界 (Out of Bounds) | `int arr[3]; arr[3] = 10;` | 最大合法索引為 `n-1` |
| 用 `sizeof` 取長度失敗 | `void f(int arr[]) { sizeof(arr); }` | 函式內 arr 已是指標，另傳 n |
| 未初始化就使用 | `int arr[5]; cout << arr[0];` | 宣告時初始化，或用 `{0}` 清零 |
| 二元搜尋用於未排序陣列 | 結果不正確 | 使用前必須先排序 |
| mid 整數溢位 | `mid = (low + high) / 2` | 改用 `mid = low + (high - low) / 2` |

---

## 八、學習筆記摘要

```
本週關鍵概念：
┌─────────────────────────────────────────────┐
│ ✦ 陣列元素在記憶體中「連續存放」             │
│ ✦ 位址公式：A + i × d （一維）              │
│ ✦ C++ 預設 Row-major 二維展開順序           │
│ ✦ Binary Search 需先排序，效率 O(log n)     │
│ ✦ 陣列傳函式會退化為指標，需另傳長度 n      │
└─────────────────────────────────────────────┘
```

**現在試試看：**
> 修改 `binarySearch` 改為**迭代（while 迴圈）**版本，不使用遞迴，驗證結果相同。
