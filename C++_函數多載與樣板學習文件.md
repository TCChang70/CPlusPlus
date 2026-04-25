# C++ 函數多載與樣板學習文件

> 參考來源：https://cplusplus.com/doc/tutorial/functions2/

## 目錄

1. [什麼是函數多載](#什麼是函數多載)
2. [函數多載的規則](#函數多載的規則)
3. [函數樣板](#函數樣板)
4. [樣板型別自動推導](#樣板型別自動推導)
5. [多個樣板型別參數](#多個樣板型別參數)
6. [非型別樣板參數](#非型別樣板參數)
7. [多載 vs 樣板的選擇](#多載-vs-樣板的選擇)
8. [常見錯誤與最佳實踐](#常見錯誤與最佳實踐)
9. [學習重點摘要](#學習重點摘要)

---

## 什麼是函數多載

**函數多載（Function Overloading）**允許在同一個程式中定義**多個同名函數**，只要它們的參數列不同即可。編譯器會根據呼叫時傳入的引數型別或數量，自動選擇正確的版本執行。

### 為什麼需要多載？

```
沒有多載的情況（C 風格）：
  add_int(int a, int b)
  add_double(double a, double b)
  add_float(float a, float b)   ← 名稱爆炸，難以記憶

有多載的情況（C++ 風格）：
  add(int a, int b)
  add(double a, double b)
  add(float a, float b)         ← 同一個名稱，更直覺
```

---

## 函數多載的規則

### 語法結構

```cpp
// 同名函數，但參數型別不同
返回型別 函數名 (型別1 參數1, 型別2 參數2) { ... }
返回型別 函數名 (型別3 參數1, 型別4 參數2) { ... }
```

### 範例一：依型別選擇不同行為

```cpp
#include <iostream>
using namespace std;

// int 版本：做乘法
int operate(int a, int b) {
    return a * b;
}

// double 版本：做除法
double operate(double a, double b) {
    return a / b;
}

int main() {
    int x = 5, y = 2;
    double n = 5.0, m = 2.0;

    cout << operate(x, y) << endl;   // 呼叫 int 版本，輸出：10
    cout << operate(n, m) << endl;   // 呼叫 double 版本，輸出：2.5

    return 0;
}
```

編譯器選擇函數的判斷流程：
```
operate(x, y) 被呼叫
  → x 是 int，y 是 int
  → 找到 int operate(int, int)
  → 呼叫 int 版本
```

### 範例二：依參數數量多載

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {   // 參數數量不同
    return a + b + c;
}

int main() {
    cout << add(3, 4)       << endl;   // 輸出：7
    cout << add(1, 2, 3)    << endl;   // 輸出：6
    return 0;
}
```

### 多載的判斷規則

| 可以多載的條件 | 說明 |
|--------------|------|
| 參數型別不同 | `(int)` vs `(double)` |
| 參數數量不同 | `(int, int)` vs `(int, int, int)` |
| 參數順序不同 | `(int, double)` vs `(double, int)` |

| 不能多載的條件 | 說明 |
|--------------|------|
| 僅回傳型別不同 | 編譯器無法從呼叫語法分辨 |

```cpp
// ❌ 錯誤：僅回傳型別不同，無法多載
int    getValue() { return 1; }
double getValue() { return 1.0; }  // 編譯錯誤！
```

---

## 函數樣板

當多個多載函數的**程式碼邏輯完全相同**，只有型別不同時，可以用**函數樣板（Function Template）**統一撰寫，讓編譯器自動為每種型別生成對應的函數。

### 概念比較

```
多載方式（重複程式碼）：
  int    sum(int a,    int b)    { return a + b; }
  double sum(double a, double b) { return a + b; }
  float  sum(float a,  float b)  { return a + b; }

樣板方式（一次定義）：
  template <class T>
  T sum(T a, T b) { return a + b; }
  ← 編譯器自動為 int、double、float 各產生一份
```

### 語法結構

```
template <class T>
T 函數名 (T 參數1, T 參數2) {
    // T 代表任意型別，編譯時由引數決定
}
```

> `class` 和 `typename` 在此完全等效，可互換使用：
> ```cpp
> template <class T>    // 兩種寫法
> template <typename T> // 效果完全相同
> ```

### 範例一：泛型加法樣板

```cpp
#include <iostream>
using namespace std;

template <class T>
T sum(T a, T b) {
    T result;       // T 也可以用來宣告區域變數
    result = a + b;
    return result;
}

int main() {
    int    i = 5,   j = 6;
    double f = 2.0, g = 0.5;

    // 明確指定型別
    cout << sum<int>(i, j)       << endl;  // 輸出：11
    cout << sum<double>(f, g)    << endl;  // 輸出：2.5

    return 0;
}
```

### 樣板的實體化（Instantiation）

呼叫 `sum<int>(i, j)` 時，編譯器實際上會產生：

```cpp
// 編譯器自動生成（等同於手寫這個函數）
int sum(int a, int b) {
    int result;
    result = a + b;
    return result;
}
```

```
template <class T>   →  sum<int>    →  int    版本
T sum(T a, T b)      →  sum<double> →  double 版本
                     →  sum<float>  →  float  版本
                     （呼叫幾種型別，就產生幾個版本）
```

---

## 樣板型別自動推導

呼叫樣板函數時，若引數型別**明確無歧義**，可以省略角括號中的型別，讓編譯器自動推導：

```cpp
template <class T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    int    i = 5, j = 6;
    double f = 2.0, g = 0.5;

    // 明確指定型別
    cout << sum<int>(i, j)    << endl;

    // 自動推導型別（引數都是 int，T 自動推導為 int）
    cout << sum(i, j)         << endl;  // 等同 sum<int>(i, j)
    cout << sum(f, g)         << endl;  // 等同 sum<double>(f, g)

    return 0;
}
```

> ⚠️ 若兩個引數型別不同，編譯器無法推導，必須明確指定：
> ```cpp
> sum(5, 2.5)        // ❌ int 和 double 混用，T 無法推導
> sum<double>(5, 2.5) // ✅ 明確告知 T = double
> ```

---

## 多個樣板型別參數

樣板可以有**多個型別參數**，以逗號分隔：

```cpp
template <class T, class U>
返回型別 函數名(T 參數1, U 參數2) { ... }
```

### 範例：比較兩個不同型別的值是否相等

```cpp
#include <iostream>
using namespace std;

template <class T, class U>
bool are_equal(T a, U b) {
    return (a == b);
}

int main() {
    // T=int, U=double，編譯器自動推導
    if (are_equal(10, 10.0))
        cout << "x and y are equal" << endl;
    else
        cout << "x and y are not equal" << endl;

    return 0;
}
```

**輸出：** `x and y are equal`

呼叫 `are_equal(10, 10.0)` 等同於 `are_equal<int, double>(10, 10.0)`。

### 數值字面量的型別規則

編譯器自動推導時，數值字面量（literal）的型別是固定的：

| 字面量 | 型別 |
|--------|------|
| `10` | `int` |
| `10.0` | `double` |
| `10L` | `long` |
| `10.0f` | `float` |
| `10U` | `unsigned int` |

---

## 非型別樣板參數

樣板參數除了型別之外，還可以是**特定型別的常數值（Non-type Template Arguments）**：

### 語法結構

```cpp
template <class T, int N>   // N 是編譯期常數，不是型別
T 函數名(T 參數) {
    // 可以直接使用 N
}
```

### 範例：固定倍數乘法

```cpp
#include <iostream>
using namespace std;

template <class T, int N>
T fixed_multiply(T val) {
    return val * N;   // N 在編譯期就已確定
}

int main() {
    cout << fixed_multiply<int, 2>(10) << endl;  // 輸出：20（乘以2）
    cout << fixed_multiply<int, 3>(10) << endl;  // 輸出：30（乘以3）

    return 0;
}
```

### 非型別參數 vs 一般函數參數

| 比較 | 非型別樣板參數 | 一般函數參數 |
|------|--------------|------------|
| 決定時機 | **編譯期** | 執行期 |
| 傳入方式 | 角括號 `<int, 2>` | 圓括號 `(val, n)` |
| 可否為變數 | ❌ 必須是常數 | ✅ 可以是變數 |
| 效能 | 可被最佳化為常數 | 執行期查找 |

```cpp
int n = 2;

// ❌ 錯誤：非型別樣板參數必須是編譯期常數
fixed_multiply<int, n>(10);   // n 是變數，編譯錯誤！

// ✅ 正確：使用常數
fixed_multiply<int, 2>(10);
```

---

## 多載 vs 樣板的選擇

| 情境 | 建議方式 |
|------|---------|
| 不同型別，**邏輯相同** | 使用**函數樣板** |
| 不同型別，**邏輯不同** | 使用**函數多載** |
| 特定型別需要**特殊處理** | 樣板 + 明確特化（Template Specialization） |

### 範例對比

```cpp
// ✅ 邏輯相同 → 用樣板
template <class T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// ✅ 邏輯不同 → 用多載
string operate(string a, string b) {
    return a + b;         // 字串：做串接
}
int operate(int a, int b) {
    return a * b;         // 整數：做乘法
}
```

---

## 常見錯誤與最佳實踐

### ❌ 常見錯誤

#### 1. 試圖只用回傳型別多載

```cpp
// ❌ 編譯錯誤：回傳型別不同無法多載
int    getValue() { return 1; }
double getValue() { return 1.0; }
// 呼叫 getValue() 時，編譯器不知道選哪個！
```

#### 2. 樣板呼叫時型別歧義

```cpp
template <class T>
T sum(T a, T b) { return a + b; }

// ❌ 錯誤：a 是 int，b 是 double，T 無法唯一決定
auto result = sum(5, 2.5);

// ✅ 方法一：明確指定型別
auto result = sum<double>(5, 2.5);

// ✅ 方法二：統一引數型別
auto result = sum(5.0, 2.5);
```

#### 3. 非型別樣板參數傳入變數

```cpp
int n = 5;

// ❌ 錯誤：非型別樣板參數必須是編譯期常數
fixed_multiply<int, n>(10);

// ✅ 正確
fixed_multiply<int, 5>(10);

// ✅ 或使用 constexpr
constexpr int n = 5;
fixed_multiply<int, n>(10);  // constexpr 是編譯期常數，可以用
```

#### 4. 多載函數行為不一致（設計問題）

```cpp
// ⚠️ 不好的設計：同名函數行為差異太大
int operate(int a, int b)       { return a * b; }  // 乘法
double operate(double a, double b) { return a / b; }  // 除法
// 呼叫者無法從函數名預測行為，容易造成混淆
```

### ✅ 最佳實踐

| 原則 | 說明 |
|------|------|
| 同名函數語意一致 | 多載函數應做「相似」的事 |
| 樣板型別用有意義的名稱 | `T`、`U` 通用，`KeyType`、`ValueType` 更具說明性 |
| 善用型別推導 | 引數明確時省略角括號，程式碼更簡潔 |
| 樣板放在標頭檔 | 樣板需要在使用前看到完整定義，通常放在 `.h` 中 |
| 多載 vs 樣板的選擇 | 邏輯一樣用樣板，邏輯不同用多載 |

---

## 學習重點摘要

```
函數多載與樣板核心概念：

┌──────────────────────────────────────────────┐
│              函數多載（Overloading）            │
│                                              │
│  相同名稱，不同參數列（型別 / 數量 / 順序）      │
│  編譯器在「編譯期」根據呼叫自動選擇版本          │
│  ⚠️ 不能只靠回傳型別區分                       │
└──────────────────────────────────────────────┘

┌──────────────────────────────────────────────┐
│              函數樣板（Function Template）      │
│                                              │
│  template <class T>                          │
│  T sum(T a, T b) { return a + b; }           │
│                                              │
│  ・T 是佔位符，呼叫時替換為實際型別            │
│  ・可以有多個型別參數 <class T, class U>      │
│  ・可以有非型別參數 <class T, int N>          │
│  ・型別可自動推導（引數無歧義時）              │
└──────────────────────────────────────────────┘

選擇原則：
  邏輯相同，型別不同  →  樣板
  邏輯不同，型別不同  →  多載
```

---

## 現在試試看

1. **初級**：撰寫一個多載函數 `print`，分別接受 `int`、`double`、`string` 型別的參數並印出，觀察編譯器如何選擇版本。

2. **中級**：撰寫一個函數樣板 `maximum`，接受兩個相同型別的參數並回傳較大的值。測試 `int`、`double`、`char` 三種型別。

3. **進階**：撰寫一個函數樣板 `swap_values`，接受兩個相同型別的參數（用參考傳遞），交換它們的值。再加入一個非型別樣板參數 `N`，讓函數重複交換 `N` 次（奇數次 = 交換，偶數次 = 還原）。

---

*資料來源：[cplusplus.com - Overloads and templates](https://cplusplus.com/doc/tutorial/functions2/)*
