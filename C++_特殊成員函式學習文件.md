# C++ 特殊成員函式（Special Members）學習文件

> 參考來源：https://cplusplus.com/doc/tutorial/classes2/  
> 前置知識：需先了解[動態記憶體配置](C++_動態記憶體配置學習文件.md)與[類別基礎](C++_類別Classes學習文件.md)

## 目錄

1. [六大特殊成員函式概覽](#六大特殊成員函式概覽)
2. [預設建構子（Default Constructor）](#預設建構子default-constructor)
3. [解構子（Destructor）](#解構子destructor)
4. [複製建構子（Copy Constructor）](#複製建構子copy-constructor)
5. [複製指派運算子（Copy Assignment）](#複製指派運算子copy-assignment)
6. [移動建構子與移動指派（Move Constructor & Assignment）](#移動建構子與移動指派move-constructor--assignment)
7. [隱式成員與 default / delete 控制](#隱式成員與-default--delete-控制)
8. [淺複製 vs 深複製 — 核心觀念](#淺複製-vs-深複製--核心觀念)
9. [完整範例：資源管理類別](#完整範例資源管理類別)
10. [常見錯誤與最佳實踐](#常見錯誤與最佳實踐)
11. [學習重點摘要](#學習重點摘要)

---

## 六大特殊成員函式概覽

**特殊成員函式（Special Member Functions）** 是在特定情況下由編譯器**自動隱式定義**的成員函式，共有六種：

| 特殊成員函式 | 典型形式（以類別 C 為例） |
|-------------|-------------------------|
| 預設建構子 | `C::C();` |
| 解構子 | `C::~C();` |
| 複製建構子 | `C::C (const C&);` |
| 複製指派運算子 | `C& operator= (const C&);` |
| 移動建構子 | `C::C (C&&);` |
| 移動指派運算子 | `C& operator= (C&&);` |

```
物件的生命週期與特殊成員的對應：

建立物件 ──→ [預設建構子] / [複製建構子] / [移動建構子]
複製物件 ──→ [複製指派運算子]
移動物件 ──→ [移動指派運算子]
物件結束 ──→ [解構子]
```

---

## 預設建構子（Default Constructor）

**預設建構子（Default Constructor）** 是呼叫時**不需要任何引數**的建構子，在宣告物件時若未傳入參數就會被呼叫。

### 隱式預設建構子的規則

```
規則：
  ┌ 類別沒有定義任何建構子  →  編譯器自動提供預設建構子
  └ 類別有定義任何帶參數的建構子  →  編譯器【不再】自動提供預設建構子
```

### 情境一：有隱式預設建構子

```cpp
class Example {
  public:
    int total;
    void accumulate(int x) { total += x; }
};

// ✅ 沒有定義任何建構子，編譯器自動提供預設建構子
Example ex;  // 合法：使用隱式預設建構子
```

### 情境二：定義了帶參數建構子後，預設建構子消失

```cpp
class Example2 {
  public:
    int total;
    Example2(int initial_value) : total(initial_value) {}  // 帶參數建構子
    void accumulate(int x) { total += x; }
};

Example2 ex(100);  // ✅ 合法
Example2 ex;       // ❌ 錯誤！已無預設建構子
```

### 情境三：手動補回預設建構子

```cpp
#include <iostream>
#include <string>
using namespace std;

class Example3 {
    string data;
  public:
    Example3(const string& str) : data(str) {}  // 帶參數建構子
    Example3() {}                                // 手動補回預設建構子
    const string& content() const { return data; }
};

int main() {
    Example3 foo;              // 使用預設建構子（data 為空字串）
    Example3 bar("Example");   // 使用帶參數建構子

    cout << "bar's content: " << bar.content() << '\n';
    // 輸出：bar's content: Example
    return 0;
}
```

---

## 解構子（Destructor）

**解構子（Destructor）** 是在物件**生命結束時自動呼叫**的函式，負責釋放物件所使用的資源（尤其是動態配置的記憶體）。

### 解構子的特性

- 名稱為 `~類別名稱`（前綴波浪符號 `~`）
- **沒有參數、沒有回傳型別**（連 `void` 也不寫）
- 每個類別只能有**一個**解構子（不能多載）
- 當物件離開作用域或被 `delete` 時自動呼叫

### 語法

```cpp
class MyClass {
  public:
    ~MyClass() {
        // 清理資源的程式碼
    }
};
```

### 範例：管理動態記憶體的解構子

```cpp
#include <iostream>
#include <string>
using namespace std;

class Example4 {
    string* ptr;   // 動態配置的字串指標
  public:
    Example4()                   : ptr(new string)    {}   // 預設建構子
    Example4(const string& str)  : ptr(new string(str)) {} // 帶參數建構子
    ~Example4() { delete ptr; }                            // 解構子：釋放記憶體

    const string& content() const { return *ptr; }
};

int main() {
    Example4 foo;              // 建構 → ptr 指向空字串
    Example4 bar("Example");   // 建構 → ptr 指向 "Example"

    cout << "bar's content: " << bar.content() << '\n';
    // main 結束 → bar 解構（delete ptr）→ foo 解構（delete ptr）
    return 0;
}
```

### 解構子的呼叫時機

```
Stack 上的物件：
    {
        Example4 obj("Hello");   ← 建構
        // ...使用 obj
    }   ← 離開作用域，自動呼叫 obj.~Example4()

Heap 上的物件：
    Example4* p = new Example4("Hi");   ← 建構
    // ...使用 p
    delete p;   ← 手動觸發 p->~Example4()，然後釋放記憶體
```

---

## 複製建構子（Copy Constructor）

**複製建構子（Copy Constructor）** 在以**同類型的具名物件**初始化新物件時被呼叫。

### 簽名格式

```cpp
MyClass::MyClass (const MyClass&);
```

### 何時呼叫複製建構子？

```cpp
MyClass foo("original");
MyClass bar(foo);       // ← 直接呼叫複製建構子
MyClass baz = foo;      // ← 也是呼叫複製建構子（初始化宣告，不是指派！）
```

### 隱式複製建構子（淺複製）

若未定義自訂複製建構子，編譯器提供的預設版本執行**淺複製（Shallow Copy）**：

```cpp
class MyClass {
  public:
    int a, b;
    string c;
};

// 編譯器自動等效為：
MyClass::MyClass(const MyClass& x) : a(x.a), b(x.b), c(x.c) {}
```

### 淺複製的危險：指標成員問題

```
淺複製示意圖（指標成員）：

  original:  ptr ─────→ "Hello"
                            ↑
  shallow copy: ptr ────────┘   ← 兩個指標指向同一塊記憶體！

  當 original 解構 → delete ptr → 釋放 "Hello"
  當 copy 解構    → delete ptr → ❌ 對已釋放的記憶體再次 delete → 崩潰！
```

### 自訂複製建構子（深複製）

```cpp
#include <iostream>
#include <string>
using namespace std;

class Example5 {
    string* ptr;
  public:
    Example5(const string& str) : ptr(new string(str)) {}
    ~Example5() { delete ptr; }

    // 自訂複製建構子：深複製
    Example5(const Example5& x) : ptr(new string(x.content())) {}
    //                                  ↑ 配置新記憶體並複製內容

    const string& content() const { return *ptr; }
};

int main() {
    Example5 foo("Example");
    Example5 bar = foo;   // 呼叫複製建構子（深複製）

    cout << "bar's content: " << bar.content() << '\n';
    // 輸出：bar's content: Example
    // foo 和 bar 各自擁有獨立的字串記憶體，解構時互不干擾
    return 0;
}
```

```
深複製示意圖：

  original: ptr ──→ "Hello"（記憶體 A）
  deep copy: ptr ──→ "Hello"（記憶體 B）← 獨立的新記憶體

  各自解構時只 delete 自己的記憶體，安全！
```

---

## 複製指派運算子（Copy Assignment）

**複製指派運算子（Copy Assignment Operator）** 在**已存在的物件**被指派另一個同類型物件的值時呼叫。

### 複製建構子 vs 複製指派

```cpp
MyClass foo;
MyClass bar(foo);   // 初始化宣告 → 呼叫【複製建構子】
MyClass baz = foo;  // 初始化宣告 → 呼叫【複製建構子】（看起來像指派，但不是！）
foo = bar;          // 已存在物件的指派 → 呼叫【複製指派運算子】
```

### 簽名格式

```cpp
MyClass& operator= (const MyClass&);
//         ↑ 回傳 *this 的參考，以支援鏈式指派（a = b = c）
```

### 自訂複製指派（深複製版本）

```cpp
// 方式一：刪除舊資源 + 配置新資源
Example5& operator=(const Example5& x) {
    delete ptr;                      // 先釋放自己原本的記憶體
    ptr = new string(x.content());   // 配置新記憶體並複製
    return *this;
}

// 方式二：直接複寫（更高效，省去重新配置）
Example5& operator=(const Example5& x) {
    *ptr = x.content();   // 直接修改所指字串的內容
    return *this;
}
```

### 注意：自我指派（Self-Assignment）

```cpp
foo = foo;   // 自我指派！

// 方式一的寫法有自我指派問題：
// delete ptr 後，x.content() 的記憶體已被釋放！
// 需加保護：
Example5& operator=(const Example5& x) {
    if (this != &x) {          // 防止自我指派
        delete ptr;
        ptr = new string(x.content());
    }
    return *this;
}
```

---

## 移動建構子與移動指派（Move Constructor & Assignment）

**移動（Move）** 與複製（Copy）相似，但移動是將資源的**所有權直接轉移**，而非複製一份新的，因此更有效率。

### 何時觸發移動？

移動語意（Move Semantics）只在來源是**無名暫存物件（Unnamed Temporary）** 時發生：

```cpp
MyClass fn();          // 回傳 MyClass 物件的函式

MyClass foo;           // 預設建構子
MyClass bar = foo;     // 複製建構子（foo 是具名物件）
MyClass baz = fn();    // 移動建構子（fn() 的回傳值是無名暫存物件）
foo = bar;             // 複製指派運算子（bar 是具名物件）
baz = MyClass();       // 移動指派運算子（MyClass() 是無名暫存物件）
```

### 右值參考（Rvalue Reference）`&&`

移動語意透過**右值參考（Rvalue Reference）** 實現，語法是在型別後加兩個 `&`：

```cpp
MyClass (MyClass&&);              // 移動建構子
MyClass& operator= (MyClass&&);   // 移動指派運算子
```

### 複製 vs 移動的記憶體操作差異

```
複製（Copy）：
  A: ptr ──→ [記憶體 A]
  B: ptr ──→ [記憶體 B]  ← 新配置，複製 A 的內容
  結果：A 和 B 各自擁有獨立資源

移動（Move）：
  A: ptr ──→ [記憶體 A]
  B: ptr ──→ [記憶體 A]  ← 直接「偷走」A 的指標
  A: ptr = nullptr        ← A 的指標被清空，不再擁有資源
  結果：B 接管資源，A 變成空的
```

### 完整移動語意範例

```cpp
#include <iostream>
#include <string>
using namespace std;

class Example6 {
    string* ptr;
  public:
    Example6(const string& str) : ptr(new string(str)) {}
    ~Example6() { delete ptr; }

    // 移動建構子：「偷走」來源的指標
    Example6(Example6&& x) : ptr(x.ptr) {
        x.ptr = nullptr;   // ← 關鍵！讓來源物件的指標失效
    }

    // 移動指派運算子
    Example6& operator=(Example6&& x) {
        delete ptr;        // 釋放自己原本的資源
        ptr = x.ptr;       // 接管來源的指標
        x.ptr = nullptr;   // 讓來源失效
        return *this;
    }

    const string& content() const { return *ptr; }

    // 加法運算子（回傳無名暫存物件，觸發移動）
    Example6 operator+(const Example6& rhs) {
        return Example6(content() + rhs.content());
    }
};

int main() {
    Example6 foo("Exam");
    Example6 bar = Example6("ple");   // 移動建構（Example6("ple") 是暫存物件）
    foo = foo + bar;                  // 移動指派（foo+bar 回傳暫存物件）

    cout << "foo's content: " << foo.content() << '\n';
    // 輸出：foo's content: Example
    return 0;
}
```

### 為什麼要讓來源指標設為 `nullptr`？

```cpp
Example6(Example6&& x) : ptr(x.ptr) {
    x.ptr = nullptr;   // 若不設為 nullptr：
                       // 1. x 結束生命時，解構子會 delete ptr
                       // 2. 但 ptr 已被 this 接管！
                       // 3. 導致 double-free，程式崩潰
}
```

### 返回值最佳化（RVO）

> 編譯器已最佳化許多正式需要移動建構子的情況，稱為 **返回值最佳化（Return Value Optimization, RVO）**，此時移動建構子可能不會被實際呼叫。

---

## 隱式成員與 default / delete 控制

### 六大特殊成員的隱式定義條件

| 特殊成員函式 | 隱式定義條件 | 預設行為 |
|-------------|------------|---------|
| 預設建構子 | 沒有任何其他建構子 | 什麼都不做 |
| 解構子 | 沒有定義解構子 | 什麼都不做 |
| 複製建構子 | 沒有移動建構子且沒有移動指派 | 複製所有成員 |
| 複製指派運算子 | 沒有移動建構子且沒有移動指派 | 複製所有成員 |
| 移動建構子 | 沒有解構子、複製建構子，且沒有複製/移動指派 | 移動所有成員 |
| 移動指派運算子 | 沒有解構子、複製建構子，且沒有複製/移動指派 | 移動所有成員 |

### `= default`：明確要求使用隱式版本

使用 `= default` 告訴編譯器「使用它本來會自動產生的版本」：

```cpp
class Rectangle {
    int width, height;
  public:
    Rectangle(int x, int y) : width(x), height(y) {}
    Rectangle() = default;   // ← 明確要求預設建構子（即使有其他建構子）
    int area() { return width * height; }
};

int main() {
    Rectangle foo;         // ✅ 使用 = default 的預設建構子
    Rectangle bar(10, 20); // ✅ 使用自訂建構子
    cout << bar.area() << '\n';  // 200
    return 0;
}
```

### `= delete`：明確禁用某個特殊成員

使用 `= delete` 告訴編譯器「禁止生成這個函式」：

```cpp
class Rectangle {
    int width, height;
  public:
    Rectangle(int x, int y) : width(x), height(y) {}
    Rectangle() = default;
    Rectangle(const Rectangle& other) = delete;   // ← 禁止複製建構
    int area() { return width * height; }
};

int main() {
    Rectangle foo;
    Rectangle bar(10, 20);
    Rectangle baz(foo);    // ❌ 編譯錯誤！複製建構子已被刪除
    return 0;
}
```

### 常見的 `= delete` 使用場景

```cpp
// 單例模式（Singleton）：禁止複製
class Singleton {
    Singleton() {}   // private 建構子
  public:
    static Singleton& instance() {
        static Singleton s;
        return s;
    }
    Singleton(const Singleton&) = delete;            // 禁止複製建構
    Singleton& operator=(const Singleton&) = delete; // 禁止複製指派
};
```

---

## 淺複製 vs 深複製 — 核心觀念

這是理解特殊成員函式最重要的概念。

### 什麼情況需要自訂特殊成員？

```
「三/五法則（Rule of Three / Five）」：
  若類別需要自訂以下任一成員，通常需要同時定義全部：

  Rule of Three（C++03）：
    ① 解構子
    ② 複製建構子
    ③ 複製指派運算子

  Rule of Five（C++11）：
    在 Rule of Three 的基礎上加上：
    ④ 移動建構子
    ⑤ 移動指派運算子

  觸發條件：類別中有「裸指標（Raw Pointer）」或其他需要手動管理的資源
```

### 決策流程圖

```
類別有指標成員嗎？
    ├─ 否 → 使用隱式版本（淺複製即可）
    └─ 是 → 需要自訂：
               ├─ 解構子（釋放資源）
               ├─ 複製建構子（深複製）
               ├─ 複製指派運算子（先釋放舊的，再深複製）
               ├─ 移動建構子（轉移指標，來源設 nullptr）
               └─ 移動指派運算子（釋放自身，轉移指標，來源設 nullptr）
```

---

## 完整範例：資源管理類別

整合所有六大特殊成員的完整示範：

```cpp
#include <iostream>
#include <string>
using namespace std;

class ManagedString {
    string* ptr;

  public:
    // 1. 預設建構子
    ManagedString() : ptr(new string("")) {
        cout << "[預設建構] 空字串\n";
    }

    // 2. 帶參數建構子
    ManagedString(const string& s) : ptr(new string(s)) {
        cout << "[建構] " << *ptr << "\n";
    }

    // 3. 解構子
    ~ManagedString() {
        cout << "[解構] " << *ptr << "\n";
        delete ptr;
    }

    // 4. 複製建構子（深複製）
    ManagedString(const ManagedString& other)
        : ptr(new string(*other.ptr)) {
        cout << "[複製建構] " << *ptr << "\n";
    }

    // 5. 複製指派運算子（深複製）
    ManagedString& operator=(const ManagedString& other) {
        if (this != &other) {
            *ptr = *other.ptr;   // 複寫內容（不重新配置）
        }
        cout << "[複製指派] " << *ptr << "\n";
        return *this;
    }

    // 6. 移動建構子
    ManagedString(ManagedString&& other) : ptr(other.ptr) {
        other.ptr = nullptr;   // 讓來源失效
        cout << "[移動建構] " << *ptr << "\n";
    }

    // 7. 移動指派運算子
    ManagedString& operator=(ManagedString&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        cout << "[移動指派] " << *ptr << "\n";
        return *this;
    }

    const string& get() const { return *ptr; }
};

int main() {
    cout << "=== 建構 ===\n";
    ManagedString a("Hello");
    ManagedString b("World");

    cout << "\n=== 複製建構 ===\n";
    ManagedString c = a;       // 複製建構子

    cout << "\n=== 複製指派 ===\n";
    b = c;                     // 複製指派運算子

    cout << "\n=== 移動建構 ===\n";
    ManagedString d = ManagedString("Temp");  // 移動建構子

    cout << "\n=== 程式結束，逆序解構 ===\n";
    return 0;
}
```

**執行輸出（示意）：**
```
=== 建構 ===
[建構] Hello
[建構] World

=== 複製建構 ===
[複製建構] Hello

=== 複製指派 ===
[複製指派] Hello

=== 移動建構 ===
[建構] Temp
[移動建構] Temp
[解構] 

=== 程式結束，逆序解構 ===
[解構] Temp
[解構] Hello
[解構] Hello
[解構] Hello
```

---

## 常見錯誤與最佳實踐

### ❌ 常見錯誤

#### 1. 有指標成員卻用隱式複製（淺複製 Bug）

```cpp
class Bad {
    int* data;
  public:
    Bad(int v) : data(new int(v)) {}
    ~Bad() { delete data; }
    // ❌ 沒有自訂複製建構子與複製指派！
};

Bad a(10);
Bad b = a;   // 淺複製：a.data 和 b.data 指向同一個 int
// a 和 b 解構時都 delete 同一個指標 → 未定義行為！
```

#### 2. 移動後還繼續使用來源物件

```cpp
ManagedString a("Hello");
ManagedString b = move(a);   // a 的資源被移走，a.ptr = nullptr

cout << a.get();   // ❌ 危險！a.ptr 已是 nullptr，解參考 nullptr
```

#### 3. 複製指派沒有處理自我指派

```cpp
// ❌ 危險的複製指派
MyClass& operator=(const MyClass& x) {
    delete ptr;           // 若 this == &x，先刪掉了自己的資源
    ptr = new T(*x.ptr);  // x.ptr 已被 delete！未定義行為
    return *this;
}

// ✅ 加上自我指派保護
MyClass& operator=(const MyClass& x) {
    if (this != &x) {
        delete ptr;
        ptr = new T(*x.ptr);
    }
    return *this;
}
```

#### 4. 移動建構子忘記讓來源失效

```cpp
// ❌ 忘記讓來源的指標失效
MyClass(MyClass&& x) : ptr(x.ptr) {
    // 沒有 x.ptr = nullptr
    // x 解構時會 delete ptr，但 ptr 已被 this 接管！→ double-free
}
```

### ✅ 最佳實踐

| 原則 | 說明 |
|------|------|
| **遵循 Rule of Five** | 有裸指標就同時定義全部五個特殊成員 |
| **移動後清空來源指標** | `x.ptr = nullptr` 防止 double-free |
| **複製指派防自我指派** | `if (this != &x)` 保護 |
| **使用 `= default` 明確意圖** | 即使想要隱式版本，也明確寫出來提高可讀性 |
| **考慮用智慧指標取代裸指標** | `unique_ptr`/`shared_ptr` 自動管理資源，省去手動實作 |

---

## 學習重點摘要

```
六大特殊成員函式：

┌──────────────────────────────────────────────────────────┐
│  建構（Construction）                                     │
│    ① 預設建構子 C()         ← 無參數建立物件             │
│    ③ 複製建構子 C(const C&) ← 從另一物件複製建立         │
│    ⑤ 移動建構子 C(C&&)      ← 從暫存物件轉移資源建立     │
├──────────────────────────────────────────────────────────┤
│  指派（Assignment）                                       │
│    ④ 複製指派 operator=(const C&) ← 複製具名物件的值     │
│    ⑥ 移動指派 operator=(C&&)      ← 轉移暫存物件的資源   │
├──────────────────────────────────────────────────────────┤
│  結束（Destruction）                                      │
│    ② 解構子 ~C()            ← 物件結束時自動呼叫          │
└──────────────────────────────────────────────────────────┘

關鍵概念：
  ・淺複製（Shallow Copy）：只複製指標值   → 危險（共用資源）
  ・深複製（Deep Copy）  ：複製指標所指內容 → 安全（各自擁有資源）
  ・移動（Move）         ：轉移指標所有權   → 最高效（無需配置新記憶體）

控制隱式成員：
  = default  →  明確要求使用編譯器的隱式版本
  = delete   →  明確禁止該函式被呼叫/生成
```

---

## 現在試試看

1. **初級**：定義一個 `IntArray` 類別，包含一個 `int*` 指標和 `size` 成員，實作建構子（動態配置陣列）、解構子（釋放記憶體），以及一個 `print()` 成員函式印出所有元素。

2. **中級**：為上題的 `IntArray` 類別加上正確的複製建構子和複製指派運算子（深複製），並在 `main` 中測試：建立 `IntArray a`，複製到 `IntArray b = a`，修改 `a` 的元素後確認 `b` 不受影響。

3. **進階**：為 `IntArray` 繼續加上移動建構子和移動指派運算子，並在每個特殊成員中加入 `cout` 診斷訊息。在 `main` 中撰寫一個回傳 `IntArray` 的函式，觀察並解釋哪些特殊成員被呼叫（注意 RVO 的影響）。

---

*資料來源：[cplusplus.com - Special Members](https://cplusplus.com/doc/tutorial/classes2/)*
