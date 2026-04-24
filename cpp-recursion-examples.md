# C++ 遞迴（Recursion）5 題經典程式範例

**語言：** C++  
**主題：** 遞迴演算法（Recursion Algorithms）  
**難度：** Easy → Medium  
**日期：** 2026-04-24  

---

## 什麼是遞迴（Recursion）？

**遞迴（Recursion）** 是函式自己呼叫自己的寫法。  
就像把一個大問題拆成「和原本很像、但規模更小」的小問題，直到縮小到一個可以直接回答的情況。

遞迴通常包含兩個核心：

- **終止條件（Base Case）**：什麼時候停止遞迴
- **遞迴步驟（Recursive Case）**：如何把大問題縮小成小問題

### 遞迴基本骨架

```cpp
returnType functionName(parameters) {
    if (終止條件) {
        return 直接答案;
    }

    return functionName(規模更小的參數);
}
```

### 常見陷阱

- 沒有寫 **終止條件（Base Case）**，會造成無限遞迴
- 問題規模沒有真的變小，程式也會卡住
- 某些遞迴問題會重複計算，效能很差

---

## 練習題 1：階乘（Factorial）

**難度：** `Easy`  
**語言：** C++  
**主題：** 遞迴、終止條件

---

### 題目說明

撰寫一個遞迴函式 `factorial`，計算整數 `n` 的階乘。

階乘定義：

- `0! = 1`
- `1! = 1`
- `n! = n × (n - 1)!`

**函式簽名（Function Signature）：**

```cpp
int factorial(int n);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `5` | `120` | `5 × 4 × 3 × 2 × 1` |
| `0` | `1` | 依照定義，`0! = 1` |

---

### 限制條件

- [ ] 輸入範圍：`0 ≤ n ≤ 12`
- [ ] 必須使用遞迴

---

### 提示

<details>
<summary>顯示提示</summary>

當 `n` 是 `0` 或 `1` 時，可以直接回傳 `1`。其他情況就回傳 `n * factorial(n - 1)`。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    cout << factorial(5) << endl;
    return 0;
}
```

**解題思路：**

1. 把 `0!` 和 `1!` 當成終止條件
2. 其他情況用 `n * factorial(n - 1)` 繼續往下拆
3. 等最底層回傳後，再一層一層乘回來

**時間複雜度分析：** `O(n)`  
**空間複雜度分析：** `O(n)`  

**延伸挑戰：** 改寫成迴圈版本，比較遞迴與迴圈差異。

</details>

---

## 練習題 2：費波那契數列（Fibonacci）

**難度：** `Easy`  
**語言：** C++  
**主題：** 雙分支遞迴

---

### 題目說明

撰寫一個遞迴函式 `fib`，回傳第 `n` 個費波那契數。

數列定義：

- `fib(0) = 0`
- `fib(1) = 1`
- `fib(n) = fib(n - 1) + fib(n - 2)`

**函式簽名（Function Signature）：**

```cpp
int fib(int n);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `6` | `8` | 數列為 `0 1 1 2 3 5 8` |
| `1` | `1` | 基本情況 |

---

### 限制條件

- [ ] 輸入範圍：`0 ≤ n ≤ 20`
- [ ] 必須使用遞迴

---

### 提示

<details>
<summary>顯示提示</summary>

當 `n <= 1` 時直接回傳 `n`。其他情況回傳前兩項的和。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    cout << fib(6) << endl;
    return 0;
}
```

**解題思路：**

1. `fib(0)` 和 `fib(1)` 直接知道答案
2. 第 `n` 項等於前兩項相加
3. 用遞迴很直觀，但會重複計算很多次

**時間複雜度分析：** `O(2^n)`  
**空間複雜度分析：** `O(n)`  

**延伸挑戰：** 加入記憶化（Memoization），把效率優化到 `O(n)`。

</details>

---

## 練習題 3：陣列總和（Recursive Array Sum）

**難度：** `Easy`  
**語言：** C++  
**主題：** 陣列遞迴、縮小問題規模

---

### 題目說明

撰寫一個遞迴函式 `sumArray`，計算整數陣列前 `n` 個元素的總和。

**函式簽名（Function Signature）：**

```cpp
int sumArray(int arr[], int n);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `{1, 2, 3, 4}, n = 4` | `10` | `1 + 2 + 3 + 4` |
| `{5}, n = 1` | `5` | 只有一個元素 |

---

### 限制條件

- [ ] `n >= 1`
- [ ] 必須使用遞迴

---

### 提示

<details>
<summary>顯示提示</summary>

可以把問題想成：前 `n` 個元素總和 = 第 `n` 個元素 + 前 `n-1` 個元素總和。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int sumArray(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }
    return arr[n - 1] + sumArray(arr, n - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4};
    cout << sumArray(arr, 4) << endl;
    return 0;
}
```

**解題思路：**

1. 如果只剩 1 個元素，就直接回傳它
2. 否則取出最後一個元素 `arr[n - 1]`
3. 再加上前 `n - 1` 個元素的總和

**時間複雜度分析：** `O(n)`  
**空間複雜度分析：** `O(n)`  

**延伸挑戰：** 改寫成找陣列最大值的遞迴版本。

</details>

---

## 練習題 4：字串反轉輸出（Reverse String Print）

**難度：** `Easy`  
**語言：** C++  
**主題：** 字串遞迴、遞迴呼叫順序

---

### 題目說明

撰寫一個遞迴函式 `printReverse`，把字串內容反向輸出。

例如輸入 `hello`，輸出 `olleh`。

**函式簽名（Function Signature）：**

```cpp
void printReverse(string s, int index);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `"hello"` | `olleh` | 先遞迴到底，再回頭輸出 |
| `"a"` | `a` | 單一字元 |

---

### 限制條件

- [ ] 不使用內建 `reverse`
- [ ] 必須使用遞迴

---

### 提示

<details>
<summary>顯示提示</summary>

如果你先呼叫下一層，再輸出目前字元，就會得到反向順序。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
#include <string>
using namespace std;

void printReverse(string s, int index) {
    if (index == s.length()) {
        return;
    }

    printReverse(s, index + 1);
    cout << s[index];
}

int main() {
    printReverse("hello", 0);
    cout << endl;
    return 0;
}
```

**解題思路：**

1. 當索引走到字串尾端時停止
2. 先遞迴到下一個字元
3. 回來時再印出目前字元，就會形成倒序

**時間複雜度分析：** `O(n)`  
**空間複雜度分析：** `O(n)`  

**延伸挑戰：** 改成回傳反轉後的新字串，而不是直接印出。

</details>

---


## 4 題重點整理

| 題號 | 題目 | 核心觀念 |
|------|------|---------|
| 1 | 階乘 | 最基本的單一路徑遞迴 |
| 2 | 費波那契 | 雙分支遞迴與重複計算 |
| 3 | 陣列總和 | 把陣列問題逐步縮小 |
| 4 | 字串反轉輸出 | 利用遞迴返回順序處理資料 |

---

## 學習建議

建議學習順序：

1. 先理解 **階乘**，熟悉 Base Case 與 Recursive Case
2. 再練 **陣列總和** 與 **字串反轉**，理解「問題縮小」
3. 接著看 **費波那契**，理解重複子問題

### 現在試試看

- 把 `factorial` 改成印出每一層呼叫的 `n`
- 把 `fib` 改成記憶化版本
- 自己寫一題「遞迴找陣列最大值」

