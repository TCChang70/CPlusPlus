# C++ Array 學習文件

## 目錄
1. [什麼是陣列 (Array)](#什麼是陣列)
2. [一維陣列](#一維陣列)
3. [陣列初始化](#陣列初始化)
4. [陣列與指標的關係](#陣列與指標的關係)
5. [陣列作為函數參數](#陣列作為函數參數)
6. [二維陣列](#二維陣列)
7. [常見操作範例](#常見操作範例)
8. [注意事項與最佳實踐](#注意事項與最佳實踐)

---

## 什麼是陣列

陣列 (Array) 是一種資料結構，用於儲存**相同資料型態**的多個元素。這些元素在記憶體中是**連續存放**的，可以透過索引 (index) 來存取。

### 陣列的特性
- 固定大小：陣列的大小在宣告時就必須確定
- 連續記憶體：元素在記憶體中連續排列
- 相同型態：所有元素必須是相同的資料型態
- 從 0 開始：索引從 0 開始計數

---

## 一維陣列

### 陣列宣告語法

```cpp
資料型態 陣列名稱[陣列大小];
```

### 範例

```cpp
#include <iostream>
using namespace std;

int main() {
    // 宣告一個可儲存 5 個整數的陣列
    int numbers[5];
    
    // 宣告並初始化
    int scores[5] = {60, 70, 80, 90, 100};
    
    // 存取陣列元素
    cout << "第一個分數: " << scores[0] << endl;  // 輸出: 60
    cout << "第三個分數: " << scores[2] << endl;  // 輸出: 80
    
    // 修改陣列元素
    scores[0] = 65;
    cout << "修改後第一個分數: " << scores[0] << endl;  // 輸出: 65
    
    return 0;
}
```

---

## 陣列初始化

### 1. 完整初始化

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

### 2. 部分初始化

```cpp
int arr[5] = {1, 2, 3};  // 未初始化的元素會自動設為 0
// arr = {1, 2, 3, 0, 0}
```

### 3. 自動推算大小

```cpp
int arr[] = {1, 2, 3, 4, 5};  // 編譯器自動推算大小為 5
```

### 4. 全部初始化為 0

```cpp
int arr[5] = {0};  // 所有元素都是 0
int arr[5] = {};   // C++11 以後也可以這樣寫
```

---

## 陣列與指標的關係

陣列名稱本身代表**陣列第一個元素的位址**。

```cpp
#include <iostream>
using namespace std;

int main() {
    int a[5] = {1, 3, 4, 5, 0};
    
    // 陣列名稱就是指向第一個元素的指標
    int *ptr = a;        // 等同於 int *ptr = &a[0];
    int *ptr2 = &a[0];   // 明確指定第一個元素的位址
    
    cout << "a[0] = " << a[0] << endl;           // 輸出: 1
    cout << "*ptr = " << *ptr << endl;           // 輸出: 1
    cout << "*(a + 2) = " << *(a + 2) << endl;   // 輸出: 4 (等同於 a[2])
    
    return 0;
}
```

### 指標運算存取陣列

```cpp
#include <iostream>
using namespace std;

int main() {
    int a[5] = {1, 3, 4, 5, 0};
    int *ptr = a;
    int size = sizeof(a) / sizeof(int);  // 計算陣列大小
    
    // 使用指標算術存取陣列元素
    for (int i = 0; i < size; i++) {
        cout << *(ptr + i) << " ";  // 等同於 a[i]
    }
    cout << endl;
    
    return 0;
}
```

### 記憶體位址示例

```cpp
#include <iostream>
using namespace std;

int main() {
    double arry[] = {5, 6, 7, 8, 9, 10};
    double *e1 = &arry[0];
    double *e2 = &arry[1];
    
    cout << "e1 位址: " << e1 << endl;
    cout << "e2 位址: " << e2 << endl;
    cout << "位址差: " << (e2 - e1) << endl;  // 差 1 (個 double)
    
    return 0;
}
```

---

## 陣列作為函數參數

當陣列作為函數參數時，實際上傳遞的是**指標**，而非整個陣列的複本。

### 重要觀念：sizeof 在函數內的行為

```cpp
#include <iostream>
using namespace std;

void func(int x[], int size) {
    // 在函數內，x 是指標，sizeof(x) 回傳指標的大小 (通常 4 或 8 bytes)
    cout << "函數內 sizeof(x): " << sizeof(x) << endl;  // 指標大小
}

int main() {
    int score[5] = {60, 70, 80, 90, 100};
    
    // 在 main 內，sizeof(score) 回傳整個陣列的大小
    cout << "main 內 sizeof(score): " << sizeof(score) << endl;  // 20 bytes (5*4)
    
    // 計算陣列元素個數
    int size = sizeof(score) / sizeof(int);
    cout << "陣列大小: " << size << endl;  // 5
    
    func(score, size);  // 必須同時傳遞陣列和大小
    
    return 0;
}
```

### 陣列參數的三種寫法

這三種寫法在函數參數中是**完全等價**的：

```cpp
void printArray(int arr[], int size);   // 方法 1：陣列語法
void printArray(int *arr, int size);    // 方法 2：指標語法
void printArray(int arr[10], int size); // 方法 3：指定大小（但會被忽略）
```

### 完整範例

```cpp
#include <iostream>
using namespace std;

// 列印陣列
void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// 計算陣列總和
int sum(int A[], int size) {
    int temp = 0;
    for (int i = 0; i < size; i++) {
        temp += A[i];
    }
    return temp;
}

int main() {
    int A[10] = {1, 3, 9, 2, 5, 8, 4, 9, 6, 7};
    int size = sizeof(A) / sizeof(int);
    
    cout << "陣列內容: ";
    printArray(A, size);
    
    cout << "總和: " << sum(A, size) << endl;
    
    return 0;
}
```

---

## 二維陣列

二維陣列可以想像成**表格**或**矩陣**，有行 (row) 和列 (column)。

### 宣告與初始化

```cpp
// 宣告 2 行 3 列的二維陣列
int arr[2][3];

// 初始化方式 1：分行初始化
int A[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

// 初始化方式 2：連續初始化（會自動換行）
int B[2][3] = {1, 2, 3, 4, 5, 6};

// 部分維度可以省略（但第二維必須指定）
int C[][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

### 二維陣列的存取

```cpp
#include <iostream>
using namespace std;

int main() {
    int A[][3] = {{1, 2, 3}, {4, 5, 6}};
    
    // 計算行數
    int rows = sizeof(A) / sizeof(A[0]);
    cout << "行數: " << rows << endl;  // 2
    
    // 雙層迴圈遍歷
    for (int i = 0; i < rows; i++) {
        int cols = sizeof(A[i]) / sizeof(int);
        for (int j = 0; j < cols; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

### 二維陣列與指標

```cpp
#include <iostream>
using namespace std;

int main() {
    int arry2d[2][3] = {
        {1, 2, 3}, 
        {4, 5, 6}
    };
    
    for (int row = 0; row < 2; row++) {
        int *a = arry2d[row];  // arry2d[row] 是指向該行第一個元素的指標
        
        for (int c = 0; c < 3; c++) {
            cout << "位址: " << a << "\t值: " << *a << endl;
            a++;  // 移動到下一個元素
        }
        cout << endl;
    }
    
    return 0;
}
```

---

## 常見操作範例

### 1. 尋找最大值

```cpp
#include <iostream>
using namespace std;

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int numbers[] = {5, 12, 3, 9, 15, 7};
    int size = sizeof(numbers) / sizeof(int);
    
    cout << "最大值: " << findMax(numbers, size) << endl;
    
    return 0;
}
```

### 2. 陣列反轉

```cpp
#include <iostream>
using namespace std;

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(int);
    
    cout << "原始陣列: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    
    reverseArray(arr, size);
    
    cout << "反轉後: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}
```

### 3. 陣列複製

```cpp
#include <iostream>
using namespace std;

void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int source[] = {1, 2, 3, 4, 5};
    int size = sizeof(source) / sizeof(int);
    int dest[5];
    
    copyArray(source, dest, size);
    
    cout << "目標陣列: ";
    for (int i = 0; i < size; i++) cout << dest[i] << " ";
    cout << endl;
    
    return 0;
}
```

### 4. 搜尋元素

```cpp
#include <iostream>
using namespace std;

int search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // 回傳找到的索引
        }
    }
    return -1;  // 找不到回傳 -1
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(int);
    
    int target = 30;
    int index = search(numbers, size, target);
    
    if (index != -1) {
        cout << "找到 " << target << "，位於索引 " << index << endl;
    } else {
        cout << "找不到 " << target << endl;
    }
    
    return 0;
}
```

---

## 注意事項與最佳實踐

### ⚠️ 常見錯誤

#### 1. 陣列索引超出範圍
```cpp
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[5] << endl;  // ❌ 錯誤！索引範圍是 0-4
cout << arr[10] << endl; // ❌ 嚴重錯誤！可能造成程式崩潰
```

#### 2. 未初始化陣列
```cpp
int arr[5];
cout << arr[0] << endl;  // ❌ 未初始化，值是不確定的（垃圾值）
```

#### 3. 在函數內使用 sizeof 計算陣列大小
```cpp
void func(int arr[]) {
    int size = sizeof(arr) / sizeof(int);  // ❌ 錯誤！這會得到指標大小
}
```

#### 4. 回傳區域陣列
```cpp
int* func() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // ❌ 危險！回傳局部陣列的位址
}
```

### ✅ 最佳實踐

#### 1. 總是檢查索引範圍
```cpp
if (index >= 0 && index < size) {
    cout << arr[index] << endl;
}
```

#### 2. 初始化陣列
```cpp
int arr[5] = {0};  // ✅ 全部初始化為 0
```

#### 3. 傳遞陣列時同時傳遞大小
```cpp
void processArray(int arr[], int size) {  // ✅ 同時傳遞大小
    // ...
}
```

#### 4. 使用常數定義陣列大小
```cpp
const int SIZE = 10;
int arr[SIZE];

for (int i = 0; i < SIZE; i++) {
    // 如果需要修改大小，只需改 SIZE
}
```

#### 5. 考慮使用 std::array 或 std::vector (C++11)
```cpp
#include <array>
#include <vector>

std::array<int, 5> arr1 = {1, 2, 3, 4, 5};  // 固定大小
std::vector<int> arr2 = {1, 2, 3, 4, 5};    // 動態大小
```

---

## 記憶體配置概念

### 一維陣列在記憶體中的樣子

```
int arr[5] = {10, 20, 30, 40, 50};

記憶體位址:  0x1000  0x1004  0x1008  0x100C  0x1010
            ┌──────┬──────┬──────┬──────┬──────┐
值:         │  10  │  20  │  30  │  40  │  50  │
            └──────┴──────┴──────┴──────┴──────┘
索引:          [0]    [1]    [2]    [3]    [4]
```

- 每個 int 佔 4 bytes
- 陣列元素在記憶體中連續存放
- 位址間隔 = sizeof(資料型態)

### 二維陣列在記憶體中的樣子

```cpp
int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
```

雖然我們想像成 2x3 的表格：
```
1  2  3
4  5  6
```

但在記憶體中實際是連續存放的：
```
記憶體:  [1][2][3][4][5][6]
```

---

## 練習題

### 基礎題
1. 宣告一個包含 10 個整數的陣列，並將所有元素初始化為 0
2. 撰寫程式計算陣列的平均值
3. 找出陣列中的最小值及其索引

### 進階題
1. 撰寫函數將兩個陣列合併成一個新陣列
2. 實作氣泡排序法對陣列進行排序
3. 撰寫程式計算二維陣列的轉置矩陣

### 挑戰題
1. 實作二分搜尋法（前提：陣列已排序）
2. 撰寫程式找出陣列中的重複元素
3. 實作動態規劃解決最大子陣列和問題

---

## 總結

### 重點回顧
- 陣列是儲存**相同型態**資料的容器
- 陣列大小在宣告時必須確定，且**無法改變**
- 陣列索引從 **0** 開始
- 陣列名稱代表**第一個元素的位址**
- 傳遞陣列給函數時，實際傳遞的是**指標**
- 必須自行管理陣列邊界，避免**索引超出範圍**

### 下一步學習
- **指標進階應用**：深入理解指標與陣列的關係
- **動態記憶體配置**：使用 `new` 和 `delete` 建立動態陣列
- **STL 容器**：學習 `std::vector`、`std::array` 等現代 C++ 容器
- **字串處理**：字元陣列與 `std::string`

---

## 參考資源

- C++ Reference: https://en.cppreference.com/
- C++ 程式設計教學
- 演算法與資料結構

---

**最後更新日期：2026-01-09**

**祝學習順利！** 🚀
