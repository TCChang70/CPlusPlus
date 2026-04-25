# C++ Basics 學習文件

本文件整理自 https://cplusplus.com/doc/tutorial/ 的 Basics of C++ 內容

---

## 目錄

1. [程式結構 (Structure of a Program)](#1-程式結構-structure-of-a-program)
2. [變數與型別 (Variables and Types)](#2-變數與型別-variables-and-types)
3. [常數 (Constants)](#3-常數-constants)
4. [運算子 (Operators)](#4-運算子-operators)
5. [基本輸入輸出 (Basic Input/Output)](#5-基本輸入輸出-basic-inputoutput)

---

## 1. 程式結構 (Structure of a Program)

### 1.1 第一個程式：Hello World

```cpp
// my first program in C++
#include <iostream>

int main()
{
    std::cout << "Hello World!";
}
```

**輸出結果：**

```
Hello World!
```

### 1.2 程式碼逐行解析

#### Line 1: `// my first program in C++`

- 這是**註解 (comment)**
- 使用雙斜線 `//` 開始，該行剩餘部分為註解
- 註解不會影響程式執行

#### Line 2: `#include <iostream>`

- 這是**前置處理指令 (preprocessor directive)**
- 以井字號 `#` 開頭
- `#include <iostream>` 指示前置處理器包含標準 C++ 的 iostream 標頭檔
- 此標頭檔允許執行標準輸入輸出操作

#### Line 3: 空白行

- 空白行不影響程式
- 僅用於提升程式碼可讀性

#### Line 4: `int main()`

- 這是**函數宣告 (function declaration)**
- `main` 是特殊函數，所有 C++ 程式都從 main 開始執行
- 函數定義由型別 (int)、名稱 (main) 和括號 `()` 組成

#### Lines 5 和 7: `{` 和 `}`

- 大括號 `{` 表示函數主體的開始
- 大括號 `}` 表示函數主體的結束
- 所有函數都使用大括號標示定義的開始和結束

#### Line 6: `std::cout << "Hello World!";`

- 這是**C++ 陳述句 (statement)**
- `std::cout` 識別標準字元輸出裝置（通常是螢幕）
- `<<` 是插入運算子，表示將後面的內容插入到 cout
- `"Hello World!"` 是要輸出的字串
- 分號 `;` 標示陳述句的結束（**重要：所有 C++ 陳述句必須以分號結束**）

### 1.3 註解 (Comments)

C++ 支援兩種註解方式：

```cpp
// 單行註解
/* 區塊註解 */
```

**範例：**

```cpp
/* my second program in C++
   with more comments */
#include <iostream>

int main()
{
    std::cout << "Hello World! ";    // prints Hello World!
    std::cout << "I'm a C++ program"; // prints I'm a C++ program
}
```

### 1.4 使用命名空間 std (Using namespace std)

兩種方式使用標準函式庫元素：

#### 方式 1：完整限定名稱

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello World!";
}
```

#### 方式 2：使用 using 宣告

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World!";
}
```

`using namespace std;` 允許不加 `std::` 前綴直接使用標準函式庫元素。

---

## 2. 變數與型別 (Variables and Types)

### 2.1 什麼是變數？

**變數 (Variable)** 是記憶體中用來儲存值的一部分空間。

**範例：**

```cpp
a = 5;
b = 2;
a = a + 1;
result = a - b;
```

### 2.2 識別字 (Identifiers)

有效的識別字規則：

- 由字母、數字或底線 `_` 組成
- 必須以字母或底線開頭（**不能以數字開頭**）
- 不能包含空格、標點符號或符號
- 不能使用 C++ 保留關鍵字

**重要：C++ 區分大小寫**

- `RESULT`、`result` 和 `Result` 是三個不同的變數

### 2.3 基本資料型別 (Fundamental Data Types)

#### 字元型別 (Character types)

| 型別       | 說明         | 大小                       |
| ---------- | ------------ | -------------------------- |
| `char`     | 基本字元型別 | 恰好 1 位元組，至少 8 位元 |
| `char16_t` | 16 位元字元  | 至少 16 位元               |
| `char32_t` | 32 位元字元  | 至少 32 位元               |
| `wchar_t`  | 寬字元       | 可表示最大字元集           |

#### 整數型別 (Integer types - signed)

| 型別                                    | 說明     | 大小                      |
| --------------------------------------- | -------- | ------------------------- |
| `signed char`                           | 有號字元 | 與 char 相同，至少 8 位元 |
| `signed short int` (或 `short`)         | 短整數   | 至少 16 位元              |
| `signed int` (或 `int`)                 | 整數     | 至少 16 位元              |
| `signed long int` (或 `long`)           | 長整數   | 至少 32 位元              |
| `signed long long int` (或 `long long`) | 超長整數 | 至少 64 位元              |

#### 整數型別 (Integer types - unsigned)

| 型別                                               | 說明         |
| -------------------------------------------------- | ------------ |
| `unsigned char`                                    | 無號字元     |
| `unsigned short int` (或 `unsigned short`)         | 無號短整數   |
| `unsigned int` (或 `unsigned`)                     | 無號整數     |
| `unsigned long int` (或 `unsigned long`)           | 無號長整數   |
| `unsigned long long int` (或 `unsigned long long`) | 無號超長整數 |

#### 浮點數型別 (Floating-point types)

| 型別          | 說明                                |
| ------------- | ----------------------------------- |
| `float`       | 單精度浮點數                        |
| `double`      | 雙精度浮點數（精度不低於 float）    |
| `long double` | 長雙精度浮點數（精度不低於 double） |

#### 其他型別

| 型別                | 說明                      |
| ------------------- | ------------------------- |
| `bool`              | 布林型別（true 或 false） |
| `void`              | 無型別                    |
| `decltype(nullptr)` | 空指標型別                |

#### 型別大小與可表示值的範圍

| 大小   | 可表示的唯一值數量         | 說明               |
| ------ | -------------------------- | ------------------ |
| 8-bit  | 256                        | = 2^8              |
| 16-bit | 65,536                     | = 2^16             |
| 32-bit | 4,294,967,296              | = 2^32 (~40 億)    |
| 64-bit | 18,446,744,073,709,551,616 | = 2^64 (~180 億億) |

### 2.4 變數宣告 (Declaration of Variables)

C++ 是**強型別語言**，每個變數在使用前必須先宣告其型別。

**語法：**

```cpp
type variable_name;
```

**範例：**

```cpp
int a;
float mynumber;
```

**多個同型別變數宣告：**

```cpp
int a, b, c;
```

等同於：

```cpp
int a;
int b;
int c;
```

**完整範例：**

```cpp
// operating with variables
#include <iostream>
using namespace std;

int main()
{
    // declaring variables:
    int a, b;
    int result;

    // process:
    a = 5;
    b = 2;
    a = a + 1;
    result = a - b;

    // print out the result:
    cout << result;

    // terminate the program:
    return 0;
}
```

**輸出：** `4`

### 2.5 變數初始化 (Initialization of Variables)

C++ 提供三種初始化方式：

#### 方式 1：C 風格初始化

```cpp
int x = 0;
```

#### 方式 2：建構子初始化

```cpp
int x (0);
```

#### 方式 3：統一初始化 (C++11)

```cpp
int x {0};
```

**範例：**

```cpp
// initialization of variables
#include <iostream>
using namespace std;

int main()
{
    int a = 5;      // initial value: 5
    int b(3);       // initial value: 3
    int c{2};       // initial value: 2
    int result;     // initial value undetermined

    a = a + b;
    result = a - c;
    cout << result;

    return 0;
}
```

**輸出：** `6`

### 2.6 型別推導：auto 和 decltype

#### auto 關鍵字

編譯器自動推導變數型別：

```cpp
int foo = 0;
auto bar = foo;  // 等同於：int bar = foo;
```

#### decltype 關鍵字

使用現有變數的型別：

```cpp
int foo = 0;
decltype(foo) bar;  // 等同於：int bar;
```

### 2.7 字串簡介 (Introduction to Strings)

字串是**複合型別 (compound type)**，需要包含 `<string>` 標頭檔。

**範例：**

```cpp
// my first string
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string mystring;
    mystring = "This is a string";
    cout << mystring;
    return 0;
}
```

**輸出：** `This is a string`

**字串初始化的三種方式：**

```cpp
string mystring = "This is a string";
string mystring ("This is a string");
string mystring {"This is a string"};
```

**字串內容變更範例：**

```cpp
// my first string
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string mystring;
    mystring = "This is the initial string content";
    cout << mystring << endl;
    mystring = "This is a different string content";
    cout << mystring << endl;
    return 0;
}
```

**輸出：**

```
This is the initial string content
This is a different string content
```

**註：** `endl` 操縱器會結束該行（印出換行字元並清空串流）。

---

## 3. 常數 (Constants)

常數是具有**固定值的運算式**。

### 3.1 字面常數 (Literals)

#### 整數字面常數 (Integer Numerals)

**十進位、八進位和十六進位表示法：**

```cpp
75      // 十進位
0113    // 八進位（以 0 開頭）
0x4b    // 十六進位（以 0x 開頭）
```

以上三者都表示相同的數值：75

**整數後綴 (Integer Suffixes)：**
| 後綴 | 型別修飾 |
|------|----------|
| `u` 或 `U` | unsigned |
| `l` 或 `L` | long |
| `ll` 或 `LL` | long long |

**範例：**

```cpp
75      // int
75u     // unsigned int
75l     // long
75ul    // unsigned long
75lu    // unsigned long
```

#### 浮點數字面常數 (Floating Point Numerals)

**表示方式：**

```cpp
3.14159    // 3.14159
6.02e23    // 6.02 x 10^23
1.6e-19    // 1.6 x 10^-19
3.0        // 3.0
```

**浮點數後綴 (Floating-point Suffixes)：**
| 後綴 | 型別 |
|------|------|
| `f` 或 `F` | float |
| `l` 或 `L` | long double |

**範例：**

```cpp
3.14159L   // long double
6.02e23f   // float
```

#### 字元和字串字面常數 (Character and String Literals)

**字元與字串：**

```cpp
'z'              // 單一字元（使用單引號）
'p'              // 單一字元
"Hello world"    // 字串（使用雙引號）
"How do you do?" // 字串
```

**逸出序列 (Escape Codes)：**
| 逸出碼 | 說明 |
|--------|------|
| `\n` | 換行 |
| `\r` | 歸位 |
| `\t` | Tab |
| `\v` | 垂直 Tab |
| `\b` | 退格 |
| `\f` | 換頁 |
| `\a` | 警報音（嗶聲） |
| `\'` | 單引號 (') |
| `\"` | 雙引號 (") |
| `\?` | 問號 (?) |
| `\\` | 反斜線 (\) |

**範例：**

```cpp
'\n'
'\t'
"Left \t Right"
"one\ntwo\nthree"
```

**字串連接：**

```cpp
"this forms" "a single" " string " "of characters"
```

等同於：

```cpp
"this formsa single string of characters"
```

**字元型別前綴：**
| 前綴 | 字元型別 |
|------|----------|
| `u` | char16_t |
| `U` | char32_t |
| `L` | wchar_t |

**字串前綴：**
| 前綴 | 說明 |
|------|------|
| `u8` | UTF-8 編碼字串 |
| `R` | 原始字串（Raw string） |

**原始字串範例：**

```cpp
R"(string with \backslash)"
R"&%$(string with \backslash)&%$"
```

兩者都等同於 `"string with \\backslash"`

#### 其他字面常數

三個關鍵字字面常數：

```cpp
bool foo = true;
bool bar = false;
int* p = nullptr;
```

### 3.2 具型別的常數運算式 (Typed Constant Expressions)

使用 `const` 關鍵字定義常數：

```cpp
const double pi = 3.1415926;
const char tab = '\t';
```

**完整範例：**

```cpp
#include <iostream>
using namespace std;

const double pi = 3.14159;
const char newline = '\n';

int main()
{
    double r = 5.0;     // radius
    double circle;

    circle = 2 * pi * r;
    cout << circle;
    cout << newline;
}
```

**輸出：** `31.4159`

### 3.3 前置處理器定義 (#define)

**語法：**

```cpp
#define identifier replacement
```

**範例：**

```cpp
#include <iostream>
using namespace std;

#define PI 3.14159
#define NEWLINE '\n'

int main()
{
    double r = 5.0;     // radius
    double circle;

    circle = 2 * PI * r;
    cout << circle;
    cout << NEWLINE;
}
```

**輸出：** `31.4159`

**注意：**

- `#define` 指令是前置處理器指令，**不需要分號**結尾
- 如果加了分號，它會成為替換序列的一部分

---

## 4. 運算子 (Operators)

### 4.1 指派運算子 (Assignment Operator)

**符號：** `=`

```cpp
x = 5;      // 將 5 指派給 x
x = y;      // 將 y 的值指派給 x
```

**範例：**

```cpp
// assignment operator
#include <iostream>
using namespace std;

int main()
{
    int a, b;         // a:?, b:?
    a = 10;           // a:10, b:?
    b = 4;            // a:10, b:4
    a = b;            // a:4, b:4
    b = 7;            // a:4, b:7

    cout << "a:";
    cout << a;
    cout << " b:";
    cout << b;
}
```

**輸出：** `a:4 b:7`

**連續指派：**

```cpp
x = y = z = 5;  // 從右到左，將 5 指派給 z、y、x
```

### 4.2 算術運算子 (Arithmetic Operators)

| 運算子 | 說明           |
| ------ | -------------- |
| `+`    | 加法           |
| `-`    | 減法           |
| `*`    | 乘法           |
| `/`    | 除法           |
| `%`    | 取餘數（模數） |

**範例：**

```cpp
x = 11 % 3;  // x = 2（11 除以 3 的餘數）
```

### 4.3 複合指派運算子 (Compound Assignment Operators)

| 運算式                | 等同於                         |
| --------------------- | ------------------------------ |
| `y += x;`             | `y = y + x;`                   |
| `x -= 5;`             | `x = x - 5;`                   |
| `x /= y;`             | `x = x / y;`                   |
| `price *= units + 1;` | `price = price * (units + 1);` |

**範例：**

```cpp
// compound assignment operators
#include <iostream>
using namespace std;

int main()
{
    int a, b = 3;
    a = b;
    a += 2;  // 等同於 a = a + 2
    cout << a;
}
```

**輸出：** `5`

### 4.4 遞增與遞減運算子 (Increment and Decrement)

**符號：** `++` 和 `--`

```cpp
++x;   // 前置遞增
x++;   // 後置遞增
--x;   // 前置遞減
x--;   // 後置遞減
```

**前置與後置的差異：**

| 範例 1                                    | 範例 2                                    |
| ----------------------------------------- | ----------------------------------------- |
| `x = 3;`<br>`y = ++x;`<br>// x = 4, y = 4 | `x = 3;`<br>`y = x++;`<br>// x = 4, y = 3 |

- **前置 (`++x`)**: 先遞增，再取值
- **後置 (`x++`)**: 先取值，再遞增

### 4.5 關係和比較運算子 (Relational and Comparison Operators)

| 運算子 | 說明       |
| ------ | ---------- |
| `==`   | 等於       |
| `!=`   | 不等於     |
| `<`    | 小於       |
| `>`    | 大於       |
| `<=`   | 小於或等於 |
| `>=`   | 大於或等於 |

**範例：**

```cpp
(7 == 5)   // false
(5 > 4)    // true
(3 != 2)   // true
(6 >= 6)   // true
(5 < 5)    // false
```

**注意：**

- `=` 是指派運算子
- `==` 是相等比較運算子

### 4.6 邏輯運算子 (Logical Operators)

| 運算子 | 說明      |
| ------ | --------- | --- | -------- |
| `!`    | NOT（非） |
| `&&`   | AND（且） |
| `      |           | `   | OR（或） |

**NOT 運算子範例：**

```cpp
!(5 == 5)   // false（因為 5 == 5 是 true）
!(6 <= 4)   // true（因為 6 <= 4 是 false）
!true       // false
!false      // true
```

**AND 運算子真值表：**
| a | b | a && b |
|---|---|--------|
| true | true | true |
| true | false | false |
| false | true | false |
| false | false | false |

**OR 運算子真值表：**
| a | b | a \|\| b |
|---|---|----------|
| true | true | true |
| true | false | true |
| false | true | true |
| false | false | false |

**範例：**

```cpp
((5 == 5) && (3 > 6))  // false (true && false)
((5 == 5) || (3 > 6))  // true (true || false)
```

**短路求值 (Short-circuit evaluation)：**
| 運算子 | 短路行為 |
|--------|----------|
| `&&` | 如果左側為 false，右側不會被評估 |
| `||` | 如果左側為 true，右側不會被評估 |

### 4.7 條件三元運算子 (Conditional Ternary Operator)

**語法：**

```cpp
condition ? result1 : result2
```

如果 condition 為 true，回傳 result1；否則回傳 result2。

**範例：**

```cpp
7==5 ? 4 : 3        // 3（因為 7 != 5）
7==5+2 ? 4 : 3      // 4（因為 7 == 5+2）
5>3 ? a : b         // a（因為 5 > 3）
a>b ? a : b         // 較大者
```

**完整範例：**

```cpp
// conditional operator
#include <iostream>
using namespace std;

int main()
{
    int a, b, c;

    a = 2;
    b = 7;
    c = (a > b) ? a : b;

    cout << c << '\n';
}
```

**輸出：** `7`

### 4.8 逗號運算子 (Comma Operator)

**符號：** `,`

用於分隔多個運算式，只有最右邊的運算式會被當作值。

**範例：**

```cpp
a = (b=3, b+2);
```

執行順序：

1. `b = 3`（b 被設為 3）
2. `b + 2`（計算 3 + 2 = 5）
3. `a = 5`（將 5 指派給 a）

最終：a = 5, b = 3

### 4.9 位元運算子 (Bitwise Operators)

| 運算子 | 組合語言等價 | 說明             |
| ------ | ------------ | ---------------- | ------- |
| `&`    | AND          | 位元 AND         |
| `      | `            | OR               | 位元 OR |
| `^`    | XOR          | 位元 XOR         |
| `~`    | NOT          | 位元補數（反轉） |
| `<<`   | SHL          | 左移位元         |
| `>>`   | SHR          | 右移位元         |

### 4.10 明確型別轉換運算子 (Explicit Type Casting)

**C 風格轉換：**

```cpp
int i;
float f = 3.14;
i = (int) f;  // i = 3
```

**C++ 函數風格轉換：**

```cpp
i = int(f);  // i = 3
```

### 4.11 sizeof 運算子

回傳型別或物件的大小（以位元組為單位）：

```cpp
x = sizeof(char);  // x = 1
```

### 4.12 運算子優先順序 (Precedence of Operators)

**範例：**

```cpp
x = 5 + 7 % 2;      // x = 6（因為 % 優先於 +）
x = 5 + (7 % 2);    // x = 6（明確表示）
x = (5 + 7) % 2;    // x = 0（使用括號改變順序）


**優先順序表（由高到低）：**
---



| 層級 | 類別         | 運算子            | 說明                | 結合性  |
| ---- | ------------ | ----------------- | ------------------- | ------- | ------- | ------ |
| 1    | 範圍         | `::`              | 範圍限定符          | 左到右  |
| 2    | 後置（一元）  | `++` `--`         | 後置遞增/遞減       | 左到右  |
|      |              | `()`              | 函數呼叫            |         |
|      |              | `[]`              | 陣列下標            |         |
|      |              | `.` `->`          | 成員存取            |         |
| 3    | 前置（一元）  | `++` `--`         | 前置遞增/遞減       | 右到左  |
|      |              | `~` `!`           | 位元 NOT / 邏輯 NOT |         |
|      |              | `+` `-`           | 一元正負號          |         |
|      |              | `&` `*`           | 取址 / 解參考       |         |
|      |              | `new` `delete`    | 配置 / 釋放記憶體   |         |
|      |              | `sizeof`          | 大小               |         |
|      |              | `(type)`          | C 風格型別轉換      |         |
| 5    | 算術：縮放    | `*` `/` `%`       | 乘、除、取餘數      | 左到右  |
| 6    | 算術：加法    | `+` `-`           | 加、減             | 左到右  |
| 7    | 位元移位      | `<<` `>>`         | 左移、右移          | 左到右  |
| 8    | 關係          | `<` `>` `<=` `>=` | 比較運算子         | 左到右  |
| 9    | 相等          | `==` `!=`         | 相等 / 不相等      | 左到右  |
| 10   | 位元 AND      | `&`               | 位元 AND          | 左到右  |
| 11   | 位元 XOR      | `^`               | 位元 XOR          | 左到右  |
| 12   | 位元 OR       | `                 | `                 | 位元 OR | 左到右  |
| 13   | 邏輯 AND      | `&&`              | 邏輯 AND          | 左到右  |
| 14   | 邏輯 OR       | `                 |  邏輯 OR          | 左到右 |
| 15   | 指派層級      | `=` `+=` `-=` 等   | 指派 / 複合指派     | 右到左  |
|      |              | `?:`               | 條件運算子          |         |
| 16   | 序列         | `,`                | 逗號分隔            | 左到右  |

---

## 5. 基本輸入輸出 (Basic Input/Output)

C++ 使用**串流 (streams)** 抽象概念執行輸入輸出操作。

### 5.1 標準串流物件

| 串流   | 說明                 |
| ------ | -------------------- |
| `cin`  | 標準輸入串流         |
| `cout` | 標準輸出串流         |
| `cerr` | 標準錯誤（輸出）串流 |
| `clog` | 標準日誌（輸出）串流 |

### 5.2 標準輸出 (cout)

**插入運算子：** `<<`

**範例：**

```cpp
cout << "Output sentence";  // 印出 Output sentence
cout << 120;                // 印出數字 120
cout << x;                  // 印出變數 x 的值
```

**字串字面值與變數的差異：**

```cpp
cout << "Hello";  // 印出 Hello
cout << Hello;    // 印出變數 Hello 的內容
```

**鏈接多個插入操作：**

```cpp
cout << "This " << " is a " << "single C++ statement";
```

**混合字面值與變數：**

```cpp
cout << "I am " << age << " years old and my zipcode is " << zipcode;
```

假設 `age = 24` 和 `zipcode = 90064`，輸出為：

```
I am 24 years old and my zipcode is 90064
```

**換行方式：**

方式 1：使用 `\n`

```cpp
cout << "First sentence.\n";
cout << "Second sentence.\nThird sentence.";
```

輸出：

```
First sentence.
Second sentence.
Third sentence.
```

方式 2：使用 `endl` 操縱器

```cpp
cout << "First sentence." << endl;
cout << "Second sentence." << endl;
```

輸出：

```
First sentence.
Second sentence.
```

**`endl` vs `\n`：**

- `endl` 會產生換行字元**並清空串流緩衝區**
- `\n` 只產生換行字元
- 一般建議：需要清空緩衝區時用 `endl`，否則用 `\n`

### 5.3 標準輸入 (cin)

**提取運算子：** `>>`

**範例：**

```cpp
int age;
cin >> age;
```

這會讓程式等待使用者從鍵盤輸入，並在按下 ENTER 後將值儲存到 `age`。

**完整範例：**

```cpp
// i/o example
#include <iostream>
using namespace std;

int main()
{
    int i;
    cout << "Please enter an integer value: ";
    cin >> i;
    cout << "The value you entered is " << i;
    cout << " and its double is " << i*2 << ".\n";
    return 0;
}
```

**範例輸出：**

```
Please enter an integer value: 702
The value you entered is 702 and its double is 1404.
```

**鏈接多個提取操作：**

```cpp
cin >> a >> b;
```

等同於：

```cpp
cin >> a;
cin >> b;
```

使用者需要輸入兩個值，以空格、Tab 或換行分隔。

### 5.4 cin 與字串 (cin and strings)

**基本用法：**

```cpp
string mystring;
cin >> mystring;
```

**注意：** `cin >>` 會在遇到空白字元時停止，因此只能提取單一單字。

**使用 getline 讀取整行：**

```cpp
getline(cin, mystring);
```

**完整範例：**

```cpp
// cin with strings
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string mystr;
    cout << "What's your name? ";
    getline(cin, mystr);
    cout << "Hello " << mystr << ".\n";
    cout << "What is your favorite team? ";
    getline(cin, mystr);
    cout << "I like " << mystr << " too!\n";
    return 0;
}
```

**範例輸出：**

```
What's your name? Homer Simpson
Hello Homer Simpson.
What is your favorite team? The Isotopes
I like The Isotopes too!
```

**最佳實踐：** 在主控台程式中，建議**總是使用 `getline`** 來取得使用者輸入。

### 5.5 字串串流 (stringstream)

標頭檔 `<sstream>` 定義了 `stringstream` 型別，允許將字串視為串流。

**用途：** 字串與數值型別之間的轉換

**從字串提取整數：**

```cpp
string mystr("1204");
int myint;
stringstream(mystr) >> myint;  // myint = 1204
```

**完整範例：**

```cpp
// stringstreams
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string mystr;
    float price = 0;
    int quantity = 0;

    cout << "Enter price: ";
    getline(cin, mystr);
    stringstream(mystr) >> price;

    cout << "Enter quantity: ";
    getline(cin, mystr);
    stringstream(mystr) >> quantity;

    cout << "Total price: " << price * quantity << endl;
    return 0;
}
```

**範例輸出：**

```
Enter price: 22.25
Enter quantity: 7
Total price: 155.75
```

**優點：**

- 將「取得使用者輸入」與「解釋資料」分離
- 讓輸入過程符合使用者預期（逐行輸入）
- 對資料轉換有更好的控制

---

## 總結

本文件涵蓋了 C++ 的五個基礎主題：

1. **程式結構**：了解 C++ 程式的基本架構、註解、前置處理指令和命名空間
2. **變數與型別**：掌握變數宣告、初始化、基本資料型別和字串
3. **常數**：學習字面常數、const 常數和 #define 定義
4. **運算子**：熟悉各種運算子及其優先順序
5. **基本輸入輸出**：使用 cout 和 cin 進行標準 I/O 操作，以及 stringstream 的應用

這些是學習 C++ 程式設計的基礎，掌握這些概念後，就可以進一步學習程式結構（流程控制、函數等）和複合資料型別（陣列、指標等）。

---

**參考資料：** https://cplusplus.com/doc/tutorial/
**文件建立日期：** 2026-01-16
