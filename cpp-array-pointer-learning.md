# C++ 陣列（Array）與指標（Pointer）完整學習文件

**語言：** C++  
**難度：** 初學 → 進階  
**日期：** 2026-04-24  

---

## 目錄

1. [陣列（Array）](#1-陣列array)
2. [指標（Pointer）](#2-指標pointer)
3. [陣列與指標的關係](#3-陣列與指標的關係)
4. [指標進階應用](#4-指標進階應用)
5. [常見錯誤整理](#5-常見錯誤整理)
6. [練習題](#6-練習題)
7. [學習筆記摘要](#7-學習筆記摘要)

---

## 1. 陣列（Array）

### 概念說明（What）

**陣列（Array）** 是一種可以儲存多個相同型別資料的容器。  
就像一排有編號的置物櫃，每個格子（元素）有固定位置（索引），讓你可以一次宣告多個變數，並透過索引快速存取。

### 使用時機（When）

- 需要儲存一組相同型別的資料（例如：學生成績、月份溫度）
- 需要對資料進行批次處理（排序、搜尋）
- 已知資料數量且不會改變時
- 想以迴圈自動化處理大量資料

### 語法結構

```cpp
// 宣告語法
<型別> <陣列名稱>[<大小>];

// 宣告並初始化
<型別> <陣列名稱>[<大小>] = {<值1>, <值2>, ...};

// 存取元素（索引從 0 開始）
<陣列名稱>[<索引>]
```

### 最小可執行範例

```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[5] = {90, 85, 78, 92, 88};  // 宣告並初始化陣列

    for (int i = 0; i < 5; i++) {
        cout << "scores[" << i << "] = " << scores[i] << endl;
    }

    return 0;
}
```

**執行結果：**
```
scores[0] = 90
scores[1] = 85
scores[2] = 78
scores[3] = 92
scores[4] = 88
```

### 進階用法

#### 1. 計算陣列平均值

```cpp
#include <iostream>
using namespace std;

int main() {
    double temperatures[7] = {25.1, 27.3, 26.8, 28.0, 24.5, 23.9, 26.2};
    double sum = 0;

    for (int i = 0; i < 7; i++) {
        sum += temperatures[i];
    }

    double avg = sum / 7;
    cout << "本週平均氣溫：" << avg << "°C" << endl;

    return 0;
}
```

**執行結果：**
```
本週平均氣溫：25.9714°C
```

#### 2. 二維陣列（2D Array）—— 就像試算表格

```cpp
#include <iostream>
using namespace std;

int main() {
    // 3 列 4 行的矩陣
    int matrix[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            cout << matrix[row][col] << "\t";
        }
        cout << endl;
    }

    return 0;
}
```

**執行結果：**
```
1    2    3    4
5    6    7    8
9    10   11   12
```

#### 3. 使用 `sizeof` 取得陣列長度

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};  // 不指定大小，讓編譯器自動計算

    int length = sizeof(arr) / sizeof(arr[0]);  // 總位元組 / 單個元素位元組
    cout << "陣列長度：" << length << endl;

    return 0;
}
```

**執行結果：**
```
陣列長度：5
```

### 常見錯誤

```cpp
// ❌ 錯誤：索引超出範圍（Out of Bounds）
int arr[3] = {1, 2, 3};
cout << arr[3];  // 索引只有 0, 1, 2，arr[3] 會存取非法記憶體！

// ✅ 正確：確認索引範圍
for (int i = 0; i < 3; i++) {     // 條件用 < 3，而非 <= 3
    cout << arr[i] << endl;
}
```

```cpp
// ❌ 錯誤：宣告陣列後才給大小（非常數大小在 C++ 標準中不允許）
int n;
cin >> n;
int arr[n];  // 部分編譯器允許（VLA），但並非 C++ 標準，避免使用

// ✅ 正確：使用 vector（動態陣列）
#include <vector>
vector<int> arr(n);   // 安全的動態大小陣列
```

---

## 2. 指標（Pointer）

### 概念說明（What）

**指標（Pointer）** 是一個儲存「記憶體位址」的變數。  
就像一張地址便條紙，它本身不是房子，而是告訴你「那個房子在哪裡」。透過指標，你可以間接存取並修改其他變數的值。

### 使用時機（When）

- 需要在函式中修改原始變數的值（傳址呼叫）
- 處理動態記憶體配置（`new` / `delete`）
- 操作陣列與字串
- 實作資料結構（鏈結串列、樹）
- 提升大型資料傳遞的效能（避免複製）

### 語法結構

```cpp
// 宣告指標
<型別>* <指標名稱>;

// 取得變數的位址（address-of operator）
&<變數名稱>

// 透過指標存取值（dereference operator 解參考）
*<指標名稱>
```

### 最小可執行範例

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;       // 普通變數
    int* p = &x;      // 指標 p 儲存 x 的記憶體位址

    cout << "x 的值：" << x << endl;
    cout << "x 的位址：" << &x << endl;
    cout << "p 儲存的位址：" << p << endl;
    cout << "透過 p 讀取的值：" << *p << endl;  // 解參考（dereference）

    *p = 100;          // 透過指標修改 x 的值
    cout << "修改後 x 的值：" << x << endl;

    return 0;
}
```

**執行結果（位址每次執行可能不同）：**
```
x 的值：42
x 的位址：0x61ff08
p 儲存的位址：0x61ff08
透過 p 讀取的值：42
修改後 x 的值：100
```

### 進階用法

#### 1. 指標作為函式參數（傳址呼叫 Pass by Reference）

```cpp
#include <iostream>
using namespace std;

// 用指標傳遞，可以修改原始變數
void doubleValue(int* p) {
    *p = *p * 2;
}

int main() {
    int num = 10;
    cout << "呼叫前：" << num << endl;  // 10

    doubleValue(&num);  // 傳入 num 的位址
    cout << "呼叫後：" << num << endl;  // 20

    return 0;
}
```

**執行結果：**
```
呼叫前：10
呼叫後：20
```

#### 2. 動態記憶體配置（Dynamic Memory Allocation）

```cpp
#include <iostream>
using namespace std;

int main() {
    // new：在 heap（堆積）上配置記憶體
    int* p = new int(99);
    cout << "動態配置的值：" << *p << endl;

    // 動態陣列
    int size = 5;
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // delete：釋放記憶體（非常重要！）
    delete p;         // 釋放單一變數
    delete[] arr;     // 釋放動態陣列

    return 0;
}
```

**執行結果：**
```
動態配置的值：99
10 20 30 40 50
```

#### 3. `nullptr`：空指標（安全初始化）

```cpp
#include <iostream>
using namespace std;

int main() {
    int* p = nullptr;  // 初始化為空指標（推薦做法）

    if (p == nullptr) {
        cout << "指標尚未指向任何位址" << endl;
    }

    int x = 42;
    p = &x;  // 現在指向 x

    if (p != nullptr) {
        cout << "p 指向的值：" << *p << endl;
    }

    return 0;
}
```

**執行結果：**
```
指標尚未指向任何位址
p 指向的值：42
```

### 常見錯誤

```cpp
// ❌ 錯誤：未初始化的野指標（Dangling Pointer / Wild Pointer）
int* p;       // p 的值是垃圾位址
*p = 100;    // 未定義行為，可能造成程式崩潰！

// ✅ 正確：宣告時初始化
int* p = nullptr;
// 或直接指向一個變數
int x = 0;
int* p = &x;
```

```cpp
// ❌ 錯誤：記憶體洩漏（Memory Leak）
void leak() {
    int* p = new int(42);
    // 函式結束但沒有 delete，記憶體永遠無法回收
}

// ✅ 正確：每個 new 都要對應一個 delete
void noLeak() {
    int* p = new int(42);
    cout << *p << endl;
    delete p;  // 釋放記憶體
    p = nullptr;  // 設為 nullptr 防止再次使用
}
```

```cpp
// ❌ 錯誤：解參考空指標（Null Pointer Dereference）
int* p = nullptr;
cout << *p;  // 程式崩潰（Segmentation Fault）

// ✅ 正確：使用前檢查
if (p != nullptr) {
    cout << *p;
}
```

---

## 3. 陣列與指標的關係

### 概念說明

陣列名稱本身就是一個指向「第一個元素」的指標常數（const pointer）。  
這是 C/C++ 最重要的核心概念之一：**陣列名稱 ≈ 陣列第一個元素的位址**。

### 最小可執行範例

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;  // arr 本身就是 &arr[0]，不需要寫 &arr

    cout << "arr    = " << arr << endl;   // 陣列位址
    cout << "&arr[0]= " << &arr[0] << endl;   // 第一個元素位址（相同）
    cout << "p      = " << p << endl;    // 指標儲存的位址（相同）

    // 用指標走訪陣列（指標算術 Pointer Arithmetic）
    for (int i = 0; i < 5; i++) {
        cout << *(p + i) << " ";  // 等同於 arr[i]
    }
    cout << endl;

    return 0;
}
```

**執行結果：**
```
arr    = 0x61fef4
&arr[0]= 0x61fef4
p      = 0x61fef4
10 20 30 40 50
```

### 指標算術（Pointer Arithmetic）

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;

    cout << "p     指向：" << *p << endl;       // 10（arr[0]）
    cout << "p+1   指向：" << *(p + 1) << endl; // 20（arr[1]）
    cout << "p+2   指向：" << *(p + 2) << endl; // 30（arr[2]）

    // p++ 讓指標移動到下一個元素
    p++;
    cout << "p++ 後指向：" << *p << endl;       // 20（arr[1]）

    return 0;
}
```

> 💡 `p + 1` 不是位址加 1，而是加上「一個 int 的大小（4 bytes）」，  
> 這就是為何指標算術能正確走訪陣列。

### 陣列作為函式參數

```cpp
#include <iostream>
using namespace std;

// 陣列傳入函式時，自動退化（decay）為指標，需另外傳入長度
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int data[5] = {3, 1, 4, 1, 5};
    printArray(data, 5);  // data 自動轉為 int*

    return 0;
}
```

**執行結果：**
```
3 1 4 1 5
```

---

## 4. 指標進階應用

### 指向指標的指標（Pointer to Pointer）

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int* p = &x;    // p 指向 x
    int** pp = &p;  // pp 指向 p

    cout << "x   = " << x << endl;
    cout << "*p  = " << *p << endl;
    cout << "**pp= " << **pp << endl;  // 兩層解參考

    **pp = 99;  // 透過 pp 修改 x 的值
    cout << "修改後 x = " << x << endl;

    return 0;
}
```

**執行結果：**
```
x   = 10
*p  = 10
**pp= 10
修改後 x = 99
```

### 常數指標與指向常數的指標

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    // 1. 指向常數的指標（pointer to const）：不能透過指標修改值
    const int* p1 = &a;
    // *p1 = 99;  // ❌ 錯誤！不能修改指向的值
    p1 = &b;      // ✅ 可以改變指標指向的位址

    // 2. 常數指標（const pointer）：指標本身不能改變指向的位址
    int* const p2 = &a;
    *p2 = 99;     // ✅ 可以修改指向的值
    // p2 = &b;   // ❌ 錯誤！不能改變指標指向的位址

    // 3. 指向常數的常數指標（兩者皆不可改）
    const int* const p3 = &a;

    cout << "a = " << a << endl;  // 99（被 p2 修改過）

    return 0;
}
```

---

## 5. 常見錯誤整理

| 錯誤類型 | 原因 | 如何避免 |
|---------|------|---------|
| **陣列越界** | 存取 `arr[n]` 或更大的索引 | 迴圈條件用 `i < n` 而非 `i <= n` |
| **野指標** | 指標未初始化即使用 | 宣告時賦值 `nullptr` 或指向具體變數 |
| **記憶體洩漏** | `new` 後未 `delete` | 每個 `new` 對應一個 `delete`，建議使用智慧指標 |
| **解參考空指標** | 對 `nullptr` 執行 `*p` | 使用前先判斷 `if (p != nullptr)` |
| **懸空指標** | `delete` 後繼續使用指標 | `delete` 後立刻設 `p = nullptr` |
| **陣列大小遺失** | 陣列傳入函式後無法用 `sizeof` 取長度 | 明確傳入 `size` 參數 |

---

## 6. 練習題

### 練習題 1：陣列反轉

**難度：** `Easy`  
**語言：** C++  
**主題：** 陣列操作、迴圈

---

#### 題目說明

撰寫一個函式 `reverseArray`，接受一個整數陣列與其長度，將陣列「就地（in-place）」反轉，不使用額外陣列。

**函式簽名：**
```cpp
void reverseArray(int* arr, int size);
```

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `{1, 2, 3, 4, 5}` | `{5, 4, 3, 2, 1}` | 頭尾交換直到中間 |
| `{10, 20, 30}` | `{30, 20, 10}` | 奇數長度，中間元素不動 |

---

#### 提示

<details>
<summary>顯示提示 1</summary>

使用兩個指標（或索引），一個從頭、一個從尾，互相交換後向中間靠近。

</details>

<details>
<summary>顯示提示 2</summary>

交換兩個值可以使用暫存變數：`int temp = a; a = b; b = temp;`

</details>

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

void reverseArray(int* arr, int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    reverseArray(arr, size);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;  // 輸出：5 4 3 2 1

    return 0;
}
```

**解題思路：**

1. 設定 `left = 0`，`right = size - 1` 兩個索引
2. 當 `left < right` 時，交換 `arr[left]` 與 `arr[right]`
3. `left++`，`right--`，向中間移動
4. 直到兩個索引交叉為止

</details>

---

### 練習題 2：找出陣列中最大值與其位置

**難度：** `Easy`  
**語言：** C++  
**主題：** 陣列走訪、指標回傳

---

#### 題目說明

撰寫一個函式 `findMax`，使用指標接受整數陣列與長度，回傳指向最大值元素的指標。主程式透過該指標印出最大值及其索引。

**函式簽名：**
```cpp
int* findMax(int* arr, int size);
```

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `{3, 7, 1, 9, 4}` | `最大值：9，索引：3` | 回傳指向 9 的指標 |
| `{5, 5, 5}` | `最大值：5，索引：0` | 相同值取最先出現的 |

---

#### 提示

<details>
<summary>顯示提示</summary>

回傳指標後，使用 `maxPtr - arr` 可以計算該指標在陣列中的索引位置（指標相減即為距離）。

</details>

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int* findMax(int* arr, int size) {
    int* maxPtr = arr;  // 假設第一個元素最大

    for (int i = 1; i < size; i++) {
        if (arr[i] > *maxPtr) {
            maxPtr = &arr[i];  // 更新指標指向更大的元素
        }
    }

    return maxPtr;
}

int main() {
    int arr[] = {3, 7, 1, 9, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    int* maxPtr = findMax(arr, size);

    cout << "最大值：" << *maxPtr << endl;
    cout << "索引：" << (maxPtr - arr) << endl;  // 指標相減得到距離

    return 0;
}
```

**解題思路：**

1. 讓 `maxPtr` 從陣列第一個元素開始
2. 走訪每個元素，如果比 `*maxPtr` 大，就更新 `maxPtr`
3. 利用「指標相減（`maxPtr - arr`）」可以計算索引

</details>

---

### 練習題 3：動態配置成績管理

**難度：** `Medium`  
**語言：** C++  
**主題：** 動態記憶體配置、指標、陣列

---

#### 題目說明

撰寫一個程式，讓使用者輸入學生人數（`n`），動態配置一個整數陣列儲存成績，輸入完畢後計算並輸出平均成績，最後正確釋放記憶體。

---

#### 輸入 / 輸出範例

| 輸入 | 輸出 |
|------|------|
| `n=3, scores={80, 90, 70}` | `平均成績：80` |
| `n=4, scores={60, 70, 80, 90}` | `平均成績：75` |

---

#### 限制條件

- 必須使用 `new` 動態配置陣列
- 程式結束前必須使用 `delete[]` 釋放記憶體

---

#### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入學生人數：";
    cin >> n;

    // 動態配置陣列
    int* scores = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "輸入第 " << (i + 1) << " 位學生成績：";
        cin >> scores[i];
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }

    cout << "平均成績：" << sum / n << endl;

    // 釋放動態配置的記憶體
    delete[] scores;
    scores = nullptr;  // 防止懸空指標

    return 0;
}
```

**解題思路：**

1. 讀取 `n` 後，用 `new int[n]` 動態配置陣列
2. 用迴圈輸入每位學生成績
3. 計算總和再除以 `n` 得平均
4. 使用 `delete[]` 釋放（注意動態陣列要用 `delete[]` 而非 `delete`）
5. 設 `scores = nullptr` 避免懸空指標

</details>

---

## 7. 學習筆記摘要

### 學習筆記：C++ 陣列與指標

**語言：** C++  
**日期：** 2026-04-24  
**難度感受：** ⭐⭐⭐⭐

---

### 這段學習涵蓋了什麼？

C++ 的陣列提供固定大小的連續記憶體儲存空間，透過索引存取。指標則是儲存記憶體位址的變數，兩者密切相關——陣列名稱本身就是指向第一個元素的指標，可用指標算術走訪陣列。

---

### 關鍵概念

| 概念 | 說明 | 記憶口訣 |
|------|------|---------|
| 陣列（Array） | 固定大小、連續記憶體、同型別 | 「一排置物櫃，有編號」 |
| 指標（Pointer） | 儲存記憶體位址的變數 | 「地址便條紙，不是房子本身」 |
| `&` 取址運算子 | 取得變數的記憶體位址 | "address-of：告訴我在哪" |
| `*` 解參考運算子 | 透過指標存取該位址的值 | "dereference：給我那裡的東西" |
| 指標算術 | `p+1` 移動到下一個元素位址 | 「+ 1 跳一格，格子大小視型別而定」 |
| `new` / `delete` | 動態配置 / 釋放堆積記憶體 | 「借了記憶體，用完要還」 |
| `nullptr` | 空指標，代表不指向任何位址 | 「空地址，未初始化的安全預設值」 |

---

### 容易混淆的地方

- [ ] `int* p` 宣告時的 `*` 和解參考的 `*` 意義不同：前者是「宣告 p 是指標」，後者是「透過 p 取值」
- [ ] `arr` 和 `&arr[0]` 相同，但 `arr` 是指標常數，不能被賦值（`arr = p` 會錯誤）
- [ ] 動態陣列用 `delete[]`，單一變數用 `delete`（搞混會有未定義行為）

---

### 類似用法比較

| 寫法 | 意義 |
|------|------|
| `arr[i]` | 陣列索引存取 |
| `*(arr + i)` | 等同於 `arr[i]`，指標算術 |
| `*(p++)` | 讀取目前值後，指標移至下一個 |
| `*++p` | 指標先移至下一個，再讀取值 |

---

### 現在試試看 🚀

1. 宣告一個 `double` 型別的陣列，儲存 5 個溫度值，印出最高溫與最低溫
2. 寫一個函式，用指標交換（swap）兩個整數的值
3. 動態配置一個 `n x n` 的二維整數陣列，填入乘法表後印出，並正確釋放記憶體

---

### 總結一句話

> 陣列是連續記憶體的方便包裝，指標是直接操控記憶體的鑰匙；理解兩者的關係，是掌握 C++ 底層威力的第一步。
