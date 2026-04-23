# C++ 函數 (Function) 完整學習文件

> 適用程度：初學 → 進階｜語言：C++

---

## 一、什麼是函數？ (What is a Function?)

函數是一段**有名字、可重複呼叫**的程式碼區塊。  
就像一台「機器」：你丟入原料（參數 Parameter），它處理後吐出結果（回傳值 Return Value）。

```
輸入（引數）→ [ 函數內部處理 ] → 輸出（回傳值）
```

**為什麼需要函數？**
- 避免重複程式碼（DRY 原則：Don't Repeat Yourself）
- 讓程式更容易閱讀與維護
- 每個函數只做一件事（單一職責）

---

## 二、語法結構 (Syntax Structure)

```cpp
回傳型別 函數名稱(參數型別 參數名稱, ...) {
    // 函數本體
    return 回傳值;  // 若回傳型別為 void 則省略
}
```

**關鍵組成：**

| 元素 | 說明 | 範例 |
|------|------|------|
| 回傳型別 (Return Type) | 函數執行後回傳的資料型別 | `int`, `double`, `string`, `void` |
| 函數名稱 (Function Name) | 呼叫函數時使用的名字 | `add`, `printHello` |
| 參數列表 (Parameter List) | 函數接收的輸入資料 | `(int a, int b)` |
| 函數本體 (Body) | `{}` 內的實際執行程式碼 | `return a + b;` |
| `return` 陳述式 | 回傳結果給呼叫者 | `return result;` |

---

## 三、最簡單的範例 (Basic Examples)

### 3.1 無參數、無回傳值（void）

```cpp
#include <iostream>
using namespace std;

// 定義函數
void sayHello() {
    cout << "Hello, C++!" << endl;
}

int main() {
    sayHello();  // 呼叫函數
    sayHello();  // 可重複呼叫
    return 0;
}
```
**輸出：**
```
Hello, C++!
Hello, C++!
```

---

### 3.2 有參數、有回傳值

```cpp
#include <iostream>
using namespace std;

// 定義：接收兩個整數，回傳它們的總和
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 5);       // 呼叫函數，傳入引數 3 和 5
    cout << "3 + 5 = " << result << endl;  // 輸出：3 + 5 = 8
    return 0;
}
```

---

### 3.3 搭配字串參數

```cpp
#include <iostream>
#include <string>
using namespace std;

string greet(string name) {
    return "你好，" + name + "！";
}

int main() {
    cout << greet("小明") << endl;  // 輸出：你好，小明！
    cout << greet("小華") << endl;  // 輸出：你好，小華！
    return 0;
}
```

---

## 四、函數宣告 vs 定義 (Declaration vs Definition)

若函數定義在 `main()` 之後，必須先做**前向宣告 (Forward Declaration)**：

```cpp
#include <iostream>
using namespace std;

// 前向宣告（只寫簽名，不寫本體）
int multiply(int a, int b);

int main() {
    cout << multiply(4, 6) << endl;  // 輸出：24
    return 0;
}

// 實際定義（可放在 main 之後）
int multiply(int a, int b) {
    return a * b;
}
```

> **最佳實務**：在 `.h` 標頭檔中宣告，在 `.cpp` 檔中定義。

---

## 五、傳值 vs 傳參考 (Pass by Value vs Pass by Reference)

這是 C++ 函數最重要的概念之一！

### 5.1 傳值（Pass by Value）— 複製一份，不影響原始變數

```cpp
#include <iostream>
using namespace std;

void doubleIt(int x) {   // x 是原始值的「副本」
    x = x * 2;
    cout << "函數內 x = " << x << endl;
}

int main() {
    int num = 10;
    doubleIt(num);
    cout << "函數外 num = " << num << endl;  // num 不變！
    return 0;
}
```
**輸出：**
```
函數內 x = 20
函數外 num = 10   ← 原始值未被修改
```

---

### 5.2 傳參考（Pass by Reference）— 直接操作原始變數

使用 `&` 符號：

```cpp
#include <iostream>
using namespace std;

void doubleIt(int& x) {  // & 表示參考，直接操作原始變數
    x = x * 2;
}

int main() {
    int num = 10;
    doubleIt(num);
    cout << "num = " << num << endl;  // 輸出：num = 20
    return 0;
}
```

---

### 5.3 傳指標（Pass by Pointer）

```cpp
#include <iostream>
using namespace std;

void doubleIt(int* ptr) {  // 傳入變數的記憶體位址
    *ptr = *ptr * 2;       // 透過指標修改原始值
}

int main() {
    int num = 10;
    doubleIt(&num);          // 傳入 num 的位址
    cout << "num = " << num << endl;  // 輸出：num = 20
    return 0;
}
```

**三種方式比較：**

| 方式 | 語法 | 能修改原始值？ | 常用時機 |
|------|------|--------------|---------|
| 傳值 | `void f(int x)` | 否 | 只需讀取，資料量小 |
| 傳參考 | `void f(int& x)` | 是 | 需要修改或避免複製大物件 |
| 傳指標 | `void f(int* x)` | 是 | 需要傳入 `nullptr` 的情況 |

---

## 六、預設參數 (Default Parameters)

```cpp
#include <iostream>
using namespace std;

// 預設參數必須放在參數列表的最右邊
void printInfo(string name, int age = 18, string city = "台北") {
    cout << name << "，" << age << " 歲，住在" << city << endl;
}

int main() {
    printInfo("小明");                    // 使用全部預設值
    printInfo("小華", 25);               // 覆蓋 age
    printInfo("小李", 30, "台中");       // 全部自訂
    return 0;
}
```
**輸出：**
```
小明，18 歲，住在台北
小華，25 歲，住在台北
小李，30 歲，住在台中
```

---

## 七、函數多載 (Function Overloading)

同名函數、不同參數列表 — C++ 自動選擇正確版本：

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

string add(string a, string b) {
    return a + b;
}

int main() {
    cout << add(3, 5)          << endl;  // 呼叫整數版：8
    cout << add(1.5, 2.3)      << endl;  // 呼叫 double 版：3.8
    cout << add("Hello", " World") << endl;  // 呼叫字串版：Hello World
    return 0;
}
```

> **注意**：函數多載以**參數型別或數量**區分，**不能只靠回傳型別**區分。

---

## 八、遞迴函數 (Recursive Function)

函數呼叫自己本身：

```cpp
#include <iostream>
using namespace std;

// 計算 n 的階乘：n! = n × (n-1) × ... × 1
int factorial(int n) {
    if (n <= 1) return 1;         // 基本情況（Base Case）：停止條件
    return n * factorial(n - 1);  // 遞迴呼叫（Recursive Call）
}

int main() {
    cout << "5! = " << factorial(5) << endl;  // 輸出：5! = 120
    cout << "0! = " << factorial(0) << endl;  // 輸出：0! = 1
    return 0;
}
```

**遞迴執行流程（n=3）：**
```
factorial(3)
  → 3 × factorial(2)
        → 2 × factorial(1)
                → 1          （基本情況，停止）
        → 2 × 1 = 2
  → 3 × 2 = 6
```

> **重要**：遞迴必須有「停止條件」，否則會無限迴圈 → Stack Overflow！

---

## 九、Inline 函數 (Inline Function)

對於非常短小的函數，使用 `inline` 可減少函數呼叫的額外負擔（Overhead）：

```cpp
#include <iostream>
using namespace std;

inline int square(int x) {
    return x * x;
}

int main() {
    cout << square(5) << endl;  // 編譯器直接展開為：5 * 5
    return 0;
}
```

> `inline` 是對編譯器的「建議」，編譯器可選擇忽略。適用於 1-3 行的簡單函數。

---

## 十、`const` 參數 (Const Parameters)

保護傳入的資料不被修改：

```cpp
#include <iostream>
#include <string>
using namespace std;

// const & 最佳實務：傳大型物件時避免複製，且禁止修改
void printName(const string& name) {
    // name = "其他名字";  // ❌ 編譯錯誤！const 保護
    cout << "姓名：" << name << endl;
}

int main() {
    string myName = "王小明";
    printName(myName);
    return 0;
}
```

---

## 十一、常見錯誤與陷阱 ⚠️

### 錯誤 1：忘記 `return` 陳述式

```cpp
// ❌ 錯誤：有回傳型別但沒有 return
int add(int a, int b) {
    int result = a + b;
    // 忘記 return result; → 未定義行為！
}

// ✅ 正確
int add(int a, int b) {
    return a + b;
}
```

---

### 錯誤 2：傳值卻期望修改原始變數

```cpp
// ❌ 錯誤：swap 無效
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // a、b 只是副本，原本的變數不受影響
}

// ✅ 正確：使用傳參考
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

---

### 錯誤 3：預設參數順序錯誤

```cpp
// ❌ 錯誤：有預設值的參數不能放在無預設值參數之前
void test(int a = 10, int b) { }  // 編譯錯誤！

// ✅ 正確：有預設值的全部放最右邊
void test(int b, int a = 10) { }
```

---

### 錯誤 4：遞迴缺少停止條件

```cpp
// ❌ 危險：無限遞迴 → Stack Overflow
int infiniteRecursion(int n) {
    return n + infiniteRecursion(n - 1);  // 永遠不會停止！
}

// ✅ 正確：一定要有 Base Case
int safeRecursion(int n) {
    if (n <= 0) return 0;  // 停止條件
    return n + safeRecursion(n - 1);
}
```

---

## 十二、綜合練習題 (Practice Exercises)

### 【Easy】練習 1
**題目**：寫一個函數 `isEven(int n)`，判斷 n 是否為偶數，回傳 `true` 或 `false`。

```
輸入：4  → 輸出：true
輸入：7  → 輸出：false
```

<details>
<summary>查看解答</summary>

```cpp
#include <iostream>
using namespace std;

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    cout << boolalpha;  // 讓 true/false 以文字顯示
    cout << isEven(4) << endl;  // true
    cout << isEven(7) << endl;  // false
    return 0;
}
```
</details>

---

### 【Medium】練習 2
**題目**：寫一個函數 `maxOfThree(int a, int b, int c)`，回傳三個數中最大值。  
**要求**：不可使用 `max()` 標準函式庫。

```
輸入：3, 9, 5  → 輸出：9
```

<details>
<summary>查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int maxOfThree(int a, int b, int c) {
    int maxVal = a;
    if (b > maxVal) maxVal = b;
    if (c > maxVal) maxVal = c;
    return maxVal;
}

int main() {
    cout << maxOfThree(3, 9, 5) << endl;   // 9
    cout << maxOfThree(10, 2, 7) << endl;  // 10
    return 0;
}
```
</details>

---

### 【Hard】練習 3
**題目**：使用遞迴寫一個函數 `fibonacci(int n)`，回傳費氏數列第 n 項。  
（費氏數列：0, 1, 1, 2, 3, 5, 8, 13, ...）

```
fibonacci(0) = 0
fibonacci(1) = 1
fibonacci(6) = 8
```

<details>
<summary>查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n == 0) return 0;          // 基本情況 1
    if (n == 1) return 1;          // 基本情況 2
    return fibonacci(n - 1) + fibonacci(n - 2);  // 遞迴
}

int main() {
    for (int i = 0; i <= 8; i++) {
        cout << "fibonacci(" << i << ") = " << fibonacci(i) << endl;
    }
    return 0;
}
```
**輸出：**
```
fibonacci(0) = 0
fibonacci(1) = 1
fibonacci(2) = 1
fibonacci(3) = 2
fibonacci(4) = 3
fibonacci(5) = 5
fibonacci(6) = 8
fibonacci(7) = 13
fibonacci(8) = 21
```
</details>

---

## 十三、學習重點摘要 (Key Takeaways)

| # | 重點 | 核心觀念 |
|---|------|---------|
| 1 | 函數基本結構 | 回傳型別、名稱、參數、本體、return |
| 2 | `void` | 不需要回傳值時使用 |
| 3 | 傳值 vs 傳參考 | `&` 符號讓函數直接修改原始變數 |
| 4 | `const &` | 效能佳又安全的大物件傳遞方式 |
| 5 | 預設參數 | 有預設值的參數必須放最右邊 |
| 6 | 函數多載 | 同名、不同參數列表 |
| 7 | 遞迴 | 一定要有 Base Case（停止條件） |
| 8 | `inline` | 短小函數的效能優化提示 |

---

## 現在試試看！ (Try It Now!)

1. 開啟你的 C++ 編譯環境（VS Code + g++ 或 OnlineGDB）
2. 自己打出 `add(int a, int b)` 函數，不要複製貼上
3. 嘗試改成傳參考版本，觀察行為差異
4. 挑戰：寫一個計算圓面積的函數 `circleArea(double radius)`

---

*文件版本：1.0 ｜ 最後更新：2026-04-16*
