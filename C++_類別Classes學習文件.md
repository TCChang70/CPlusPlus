# C++ 類別（Classes）學習文件 (I)

> 參考來源：https://cplusplus.com/doc/tutorial/classes/

## 目錄

1. [什麼是類別與物件](#什麼是類別與物件)
2. [存取修飾子：private / public / protected](#存取修飾子private--public--protected)
3. [成員函式的定義方式](#成員函式的定義方式)
4. [建構子（Constructor）](#建構子constructor)
5. [建構子多載](#建構子多載)
6. [統一初始化語法](#統一初始化語法)
7. [成員初始化列表](#成員初始化列表)
8. [指向類別的指標](#指向類別的指標)
9. [struct 與 union 定義的類別](#struct-與-union-定義的類別)
10. [常見錯誤與最佳實踐](#常見錯誤與最佳實踐)
11. [學習重點摘要](#學習重點摘要)

---

## 什麼是類別與物件

**類別（Class）** 是一種擴充的資料結構，不只可以存放資料成員，還可以包含函式成員。  
**物件（Object）** 是類別的**實體（Instance）**，類別就是型別，物件就是變數。

```
類別（Class）  ←→  型別（Type）   例如：int
物件（Object） ←→  變數（Variable） 例如：int a;
```

### 類別的定義語法

```cpp
class 類別名稱 {
    存取修飾子1:
        成員1;
    存取修飾子2:
        成員2;
    ...
} 物件名稱;   // 可在定義同時宣告物件（選填）
```

### 最小可執行範例

```cpp
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;    // 預設為 private
  public:
    void set_values(int, int);
    int area() { return width * height; }  // 定義在類別內（inline）
};

// 在類別外定義成員函式，使用 :: 指定所屬類別
void Rectangle::set_values(int x, int y) {
    width = x;
    height = y;
}

int main() {
    Rectangle rect;
    rect.set_values(3, 4);
    cout << "area: " << rect.area() << endl;  // 輸出：area: 12
    return 0;
}
```

### 一個類別，多個物件

每個物件都有**自己的成員變數**，彼此獨立：

```cpp
int main() {
    Rectangle rect, rectb;     // 兩個獨立物件

    rect.set_values(3, 4);
    rectb.set_values(5, 6);

    cout << "rect area: "  << rect.area()  << endl;  // 12
    cout << "rectb area: " << rectb.area() << endl;  // 30

    return 0;
}
```

```
記憶體示意圖：
rect  ┌──────────┬──────────┐
      │ width=3  │ height=4 │
      └──────────┴──────────┘

rectb ┌──────────┬──────────┐
      │ width=5  │ height=6 │
      └──────────┴──────────┘
```

---

## 存取修飾子：private / public / protected

**存取修飾子（Access Specifier）** 控制類別成員對外的可見程度：

| 修飾子 | 可存取範圍 |
|--------|----------|
| `private` | 只有同一個類別的成員（及 friend） |
| `protected` | 同一類別成員 + 衍生類別（繼承用） |
| `public` | 任何地方都可存取 |

> 用 `class` 關鍵字定義的類別，**預設存取為 `private`**。

### 存取控制示意圖

```
class Rectangle {
    int width, height;    ← private（外部無法直接存取）
  public:
    void set_values(...); ← public（外部可呼叫）
    int area();           ← public（外部可呼叫）
};

main() {
    Rectangle rect;
    rect.width = 5;         // ❌ 編譯錯誤！width 是 private
    rect.set_values(5, 3);  // ✅ 正確，set_values 是 public
}
```

### 為什麼需要 private？

封裝（Encapsulation）的核心目的：

- 防止外部程式碼隨意修改物件內部狀態
- 強迫使用者透過公開介面（成員函式）操作物件
- 類別內部實作可以改變，只要公開介面不變，使用者程式碼無需修改

---

## 成員函式的定義方式

### 方式一：定義在類別內（自動視為 inline）

```cpp
class Rectangle {
    int width, height;
  public:
    int area() { return width * height; }  // 直接在類別內定義
};
```

### 方式二：在類別外定義（使用 `::` 範圍解析運算子）

```cpp
class Rectangle {
    int width, height;
  public:
    void set_values(int, int);  // 類別內只放宣告
    int area();
};

// 類別外定義：類別名::函式名
void Rectangle::set_values(int x, int y) {
    width = x;    // 可存取 private 成員 width, height
    height = y;
}

int Rectangle::area() {
    return width * height;
}
```

### 兩種方式的差異

| 比較 | 類別內定義 | 類別外定義 |
|------|-----------|-----------|
| 編譯器處理 | 自動 `inline`（可能被展開） | 一般函式 |
| 適用場景 | 短小、簡單的函式 | 較複雜的函式邏輯 |
| 程式碼組織 | 類別宣告較長 | 宣告與實作分離，較清晰 |

---

## 建構子（Constructor）

**建構子（Constructor）** 是類別的特殊成員函式，在**物件建立時自動呼叫**，通常用來初始化成員變數。

### 建構子的特性

- 名稱**與類別名稱完全相同**
- **沒有回傳型別**（連 `void` 也不寫）
- 建立物件時自動執行，**不能明確呼叫**

### 語法

```cpp
class 類別名稱 {
  public:
    類別名稱(參數列);   // 建構子宣告
};

類別名稱::類別名稱(參數列) {
    // 初始化成員
}
```

### 範例

```cpp
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle(int a, int b);      // 建構子宣告
    int area() { return width * height; }
};

Rectangle::Rectangle(int a, int b) {
    width = a;
    height = b;
}

int main() {
    Rectangle rect(3, 4);    // 建立物件時傳入引數，呼叫建構子
    Rectangle rectb(5, 6);

    cout << "rect area: "  << rect.area()  << endl;  // 12
    cout << "rectb area: " << rectb.area() << endl;  // 30

    return 0;
}
```

### 有無建構子的差異

```
// ❌ 沒有建構子：成員未初始化，呼叫 area() 是未定義行為
Rectangle rect;
cout << rect.area();   // 垃圾值！

// ✅ 有建構子：建立時自動初始化
Rectangle rect(3, 4);
cout << rect.area();   // 12，安全可預期
```

---

## 建構子多載

建構子可以像一般函式一樣**多載（Overload）**，提供多種建立物件的方式：

```cpp
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle();             // 預設建構子（Default Constructor）
    Rectangle(int a, int b); // 帶參數的建構子
    int area() { return width * height; }
};

Rectangle::Rectangle() {
    width = 5;
    height = 5;
}

Rectangle::Rectangle(int a, int b) {
    width = a;
    height = b;
}

int main() {
    Rectangle rect(3, 4);   // 呼叫帶參數的建構子
    Rectangle rectb;         // 呼叫預設建構子（注意：不加括號！）

    cout << "rect area: "  << rect.area()  << endl;  // 12
    cout << "rectb area: " << rectb.area() << endl;  // 25

    return 0;
}
```

### 預設建構子的陷阱

```cpp
Rectangle rectb;    // ✅ 正確：呼叫預設建構子
Rectangle rectc();  // ❌ 陷阱！這是「函式宣告」，不是建立物件！
                    //    編譯器將 rectc 視為：回傳 Rectangle 的無參函式
```

---

## 統一初始化語法

C++11 引入**統一初始化（Uniform Initialization）**，使用大括號 `{}` 建立物件，可避免與函式宣告混淆：

```cpp
class Circle {
    double radius;
  public:
    Circle(double r) { radius = r; }
    double circum() { return 2 * radius * 3.14159265; }
};

int main() {
    Circle foo(10.0);       // ① 函式形式（Functional Form）
    Circle bar = 20.0;      // ② 指派初始化（單一參數時可用）
    Circle baz{30.0};       // ③ 統一初始化（Uniform Initialization）
    Circle qux = {40.0};    // ④ 統一初始化（帶等號）

    cout << foo.circum() << endl;  // 62.8319

    // 使用 {} 呼叫預設建構子（比空括號更明確）
    Rectangle rectd{};    // ✅ 明確呼叫預設建構子
    Rectangle recte();    // ❌ 被視為函式宣告！

    return 0;
}
```

---

## 成員初始化列表

建構子可以在函式本體**之前**用冒號 `:` 引入**成員初始化列表（Member Initialization List）**，直接初始化成員：

### 三種等效寫法

```cpp
// 寫法一：在建構子本體內賦值
Rectangle::Rectangle(int x, int y) {
    width = x;
    height = y;
}

// 寫法二：成員初始化列表（部分）
Rectangle::Rectangle(int x, int y) : width(x) {
    height = y;
}

// 寫法三：成員初始化列表（完整，本體為空）
Rectangle::Rectangle(int x, int y) : width(x), height(y) {}
```

### 什麼時候必須用成員初始化列表？

當成員是**另一個沒有預設建構子的類別物件**時，必須透過列表呼叫其建構子：

```cpp
#include <iostream>
using namespace std;

class Circle {
    double radius;
  public:
    Circle(double r) : radius(r) {}   // Circle 沒有預設建構子
    double area() { return radius * radius * 3.14159265; }
};

class Cylinder {
    Circle base;      // 成員是 Circle 物件
    double height;
  public:
    // 必須在初始化列表中呼叫 base 的建構子
    Cylinder(double r, double h) : base(r), height(h) {}
    double volume() { return base.area() * height; }
};

int main() {
    Cylinder foo(10, 20);
    cout << "foo's volume: " << foo.volume() << endl;  // 6283.19
    return 0;
}
```

### 成員初始化列表 vs 建構子本體賦值

| 比較 | 初始化列表 | 本體賦值 |
|------|-----------|---------|
| 執行時機 | 物件建立時直接初始化 | 先預設建構再賦值（兩步驟） |
| 效能 | 較佳（一步完成） | 可能較差（先建構再覆蓋） |
| 必要場景 | `const` 成員、參考成員、無預設建構子的類別成員 | 一般情況 |

---

## 指向類別的指標

類別是合法的型別，可以用指標指向物件。透過指標存取成員時使用**箭頭運算子 `->` **：

```cpp
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle(int x, int y) : width(x), height(y) {}
    int area() { return width * height; }
};

int main() {
    Rectangle  obj(3, 4);
    Rectangle* foo;            // 指向 Rectangle 的指標
    Rectangle* bar;
    Rectangle* baz;

    foo = &obj;                          // 指向既有物件
    bar = new Rectangle(5, 6);           // 動態配置單一物件
    baz = new Rectangle[2]{{2,5},{3,6}}; // 動態配置陣列

    cout << "obj's area: "   << obj.area()    << endl;  // 12（用 . 存取）
    cout << "*foo's area: "  << foo->area()   << endl;  // 12（用 -> 存取）
    cout << "*bar's area: "  << bar->area()   << endl;  // 30
    cout << "baz[0]'s area: "<< baz[0].area() << endl;  // 10
    cout << "baz[1]'s area: "<< baz[1].area() << endl;  // 18

    delete bar;      // 釋放單一物件
    delete[] baz;    // 釋放陣列

    return 0;
}
```

### 運算子速查表

| 運算式 | 含義 |
|--------|------|
| `obj.member` | 物件 obj 的成員 member |
| `ptr->member` | 指標 ptr 所指物件的成員（等同 `(*ptr).member`） |
| `*ptr` | ptr 所指向的物件 |
| `&obj` | obj 的記憶體位址 |
| `ptr[0]` | ptr 所指第一個物件 |
| `ptr[n]` | ptr 所指第 (n+1) 個物件 |

---

## struct 與 union 定義的類別

`struct` 也可以用來定義含成員函式的類別，與 `class` 幾乎完全相同，唯一差異在於**預設存取等級**：

| 關鍵字 | 預設存取 |
|--------|---------|
| `class` | `private` |
| `struct` | `public` |
| `union` | `public` |

```cpp
// 以下兩個定義等效
class Rectangle {
    int width, height;    // private（class 預設）
  public:
    int area() { return width * height; }
};

struct Rectangle {
  private:                // 需明確標示 private
    int width, height;
  public:
    int area() { return width * height; }
};
```

> **慣例**：`struct` 通常用於「只有資料、無複雜行為」的純資料結構；`class` 用於「有封裝、行為、建構子」的完整物件導向設計。

---

## 常見錯誤與最佳實踐

### ❌ 常見錯誤

#### 1. 用空括號宣告物件（最令人困惑的陷阱）

```cpp
// ❌ 錯誤：這是「函式宣告」，不是物件建立
Rectangle rectc();

// ✅ 正確：不帶括號
Rectangle rectc;

// ✅ 或使用統一初始化
Rectangle rectc{};
```

#### 2. 在建構子外存取 private 成員

```cpp
class Rectangle {
    int width, height;  // private
  public:
    int area() { return width * height; }
};

int main() {
    Rectangle rect;
    rect.width = 5;  // ❌ 編譯錯誤：width 是 private
}
```

#### 3. 建構子寫了回傳型別

```cpp
// ❌ 錯誤：建構子不能有回傳型別
void Rectangle::Rectangle(int a, int b) {
    width = a;
    height = b;
}

// ✅ 正確：建構子無回傳型別
Rectangle::Rectangle(int a, int b) {
    width = a;
    height = b;
}
```

#### 4. 動態配置物件後忘記釋放

```cpp
Rectangle* r = new Rectangle(3, 4);
// ... 使用 r
delete r;    // ✅ 必須手動釋放！
r = nullptr; // ✅ 良好習慣
```

### ✅ 最佳實踐

| 原則 | 說明 |
|------|------|
| 成員變數設為 private | 透過公開介面控制存取，保護資料完整性 |
| 使用建構子初始化 | 避免成員變數未初始化的未定義行為 |
| 優先使用成員初始化列表 | 更高效，且某些情況下為必要 |
| 使用 `{}` 統一初始化 | 避免與函式宣告混淆 |
| 動態物件記得 delete | 避免記憶體洩漏（Memory Leak） |

---

## 學習重點摘要

```
C++ 類別核心概念：

┌─────────────────────────────────────────────┐
│                  Class（類別）               │
│                                             │
│  ┌──────────────┐   ┌──────────────────┐   │
│  │  資料成員     │   │   函式成員        │   │
│  │ (Data Member)│   │ (Member Function) │   │
│  │  int width;  │   │  int area();      │   │
│  │  int height; │   │  void set(...);   │   │
│  └──────────────┘   └──────────────────┘   │
│                                             │
│  存取控制：private | public | protected     │
└─────────────────────────────────────────────┘
         ↓ 實體化（Instantiation）
┌─────────────────────────────────────────────┐
│               Object（物件）                 │
│                                             │
│  Rectangle rect;    ← 一個物件              │
│  Rectangle rectb;   ← 另一個物件（獨立）    │
└─────────────────────────────────────────────┘

建構子（Constructor）：
  ・名稱 = 類別名稱，無回傳型別
  ・建立物件時自動呼叫
  ・可以多載（無參數 = 預設建構子）
  ・使用成員初始化列表更高效

存取成員：
  obj.member    →  直接存取
  ptr->member   →  透過指標存取
```

---

## 現在試試看

1. **初級**：定義一個 `Circle` 類別，包含私有成員 `radius`，建構子接受半徑值，以及公開成員函式 `area()` 和 `perimeter()` 各自計算面積與周長，在 `main` 中建立兩個不同半徑的圓並印出結果。

2. **中級**：定義一個 `BankAccount` 類別，包含 `owner`（string）和 `balance`（double），使用建構子初始化，提供 `deposit(double)`、`withdraw(double)` 成員函式（提款時檢查餘額是否足夠），以及 `print()` 印出帳戶資訊。

3. **進階**：定義 `Point` 類別（含 `x`、`y` 座標）與 `Triangle` 類別（含三個 `Point` 成員），使用成員初始化列表在 `Triangle` 建構子中初始化三個頂點，並新增 `perimeter()` 函式計算三角形周長（需計算兩點距離）。

---

*資料來源：[cplusplus.com - Classes (I)](https://cplusplus.com/doc/tutorial/classes/)*
