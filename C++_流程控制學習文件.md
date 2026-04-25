# C++ 流程控制學習文件

> 參考來源：https://cplusplus.com/doc/tutorial/control/

## 目錄

1. [什麼是流程控制](#什麼是流程控制)
2. [選擇敘述：if 與 else](#選擇敘述if-與-else)
3. [迴圈：while](#迴圈while)
4. [迴圈：do-while](#迴圈do-while)
5. [迴圈：for](#迴圈for)
6. [範圍式 for 迴圈](#範圍式-for-迴圈)
7. [跳躍敘述：break / continue / goto](#跳躍敘述break--continue--goto)
8. [選擇敘述：switch](#選擇敘述switch)
9. [常見錯誤與最佳實踐](#常見錯誤與最佳實踐)
10. [學習重點摘要](#學習重點摘要)

---

## 什麼是流程控制

C++ 程式預設由上而下**循序執行 (Sequential Execution)**，但實際程式需要做決策、重複動作。  
**流程控制敘述 (Flow Control Statements)** 讓程式能夠：

- **分支（Selection）**：根據條件決定要執行哪段程式碼
- **迴圈（Iteration）**：重複執行某段程式碼
- **跳躍（Jump）**：跳到程式的特定位置

### 複合敘述（Compound Statement）

用大括號 `{}` 把多行程式碼包成「一個單元」：

```cpp
{
    statement1;
    statement2;
    statement3;
}
```

流程控制中「需要一個 statement 的地方」，都可以放一個複合敘述。

---

## 選擇敘述：if 與 else

### 語法結構

```
if (條件) 敘述;

if (條件) {
    敘述1;
    敘述2;
} else {
    敘述3;
}

if (條件1) {
    ...
} else if (條件2) {
    ...
} else {
    ...
}
```

### 範例一：基本 if

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 100;

    if (x == 100)
        cout << "x is 100" << endl;

    return 0;
}
```

### 範例二：if-else 二選一

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 50;

    if (x == 100)
        cout << "x is 100" << endl;
    else
        cout << "x is not 100" << endl;

    return 0;
}
```

### 範例三：else if 多重分支

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = -5;

    if (x > 0)
        cout << "x is positive" << endl;
    else if (x < 0)
        cout << "x is negative" << endl;
    else
        cout << "x is 0" << endl;

    return 0;
}
```

**輸出：** `x is negative`

### 執行流程圖

```
if (x > 0) ──→ true  ──→ 印出 "positive"
     │
     └──→ false ──→ if (x < 0) ──→ true  ──→ 印出 "negative"
                         │
                         └──→ false ──→ 印出 "x is 0"
```

---

## 迴圈：while

**while 迴圈**：先檢查條件，條件為真才執行，條件一開始就為假則一次也不執行。

### 語法結構

```
while (條件) {
    敘述;
}
```

### 執行步驟

```
1. 檢查條件
2. 條件為 true → 執行迴圈本體 → 回到步驟 1
   條件為 false → 離開迴圈
```

### 範例：倒數計時

```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 10;

    while (n > 0) {
        cout << n << ", ";
        --n;        // 每次迴圈讓 n 減 1，確保條件最終變 false
    }

    cout << "liftoff!" << endl;
    return 0;
}
```

**輸出：** `10, 9, 8, 7, 6, 5, 4, 3, 2, 1, liftoff!`

> ⚠️ 迴圈內必須有改變條件的程式碼，否則會造成**無限迴圈 (Infinite Loop)**。

---

## 迴圈：do-while

**do-while 迴圈**：先執行本體，再檢查條件。**至少執行一次**，不論條件是否成立。

### 語法結構

```
do {
    敘述;
} while (條件);      ← 注意結尾有分號！
```

### while vs do-while 比較

```
while 迴圈：           do-while 迴圈：
──────────────         ──────────────
檢查條件               執行本體
  ↓ true              檢查條件
執行本體                 ↓ true
  ↓                   執行本體
回到檢查                 ↓
                      回到檢查
```

### 範例：輸入直到使用者輸入 "goodbye"

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;

    do {
        cout << "Enter text: ";
        getline(cin, str);
        cout << "You entered: " << str << endl;
    } while (str != "goodbye");

    return 0;
}
```

**執行結果範例：**
```
Enter text: hello
You entered: hello
Enter text: goodbye
You entered: goodbye
```

**適用時機：** 需要先執行一次再判斷是否繼續的情境（如輸入驗證）。

---

## 迴圈：for

**for 迴圈**：將「初始化」、「條件」、「更新」集中在一行，最適合已知次數的迴圈。

### 語法結構

```
for (初始化; 條件; 更新) {
    敘述;
}
```

### 執行步驟

```
1. 執行初始化（只執行一次）
2. 檢查條件
   → true：執行本體
   → false：離開迴圈
3. 執行更新
4. 回到步驟 2
```

### 範例一：基本 for 迴圈

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int n = 10; n > 0; n--) {
        cout << n << ", ";
    }
    cout << "liftoff!" << endl;
    return 0;
}
```

**輸出：** `10, 9, 8, 7, 6, 5, 4, 3, 2, 1, liftoff!`

### 範例二：累加 1 到 100

```cpp
#include <iostream>
using namespace std;

int main() {
    int sum = 0;

    for (int i = 1; i <= 100; i++) {
        sum += i;
    }

    cout << "1 到 100 的總和：" << sum << endl;  // 輸出：5050
    return 0;
}
```

### 範例三：多個計數器（使用逗號運算子）

```cpp
for (int n = 0, i = 100; n != i; ++n, --i) {
    // n 從 0 增加，i 從 100 減少
    // 當 n == i == 50 時結束（共執行 50 次）
}
```

### 省略 for 的各欄位

```cpp
// 全部省略 = 無限迴圈
for (;;) { ... }

// 省略初始化（變數已事先宣告）
int n = 0;
for (; n < 10; n++) { ... }

// 省略更新（在迴圈內手動更新）
for (int n = 0; n < 10;) {
    n++;
}
```

---

## 範圍式 for 迴圈

C++11 引入的**範圍式 for 迴圈 (Range-based for loop)**，可直接迭代陣列、字串、容器等，無需手動管理索引。

### 語法結構

```
for (宣告 : 範圍) {
    敘述;
}
```

### 範例一：逐字元遍歷字串

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello!";

    for (char c : str) {
        cout << "[" << c << "]";
    }
    cout << endl;
    return 0;
}
```

**輸出：** `[H][e][l][l][o][!]`

### 範例二：使用 auto 自動推導型別

```cpp
string str = "Hello!";

// 和上面範例等效，auto 自動推導 c 的型別為 char
for (auto c : str) {
    cout << "[" << c << "]";
}
```

### 範例三：遍歷整數陣列

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
```

**輸出：** `10 20 30 40 50`

### 修改元素（使用參考）

```cpp
int arr[] = {1, 2, 3, 4, 5};

// 加上 & 才能修改原陣列的值
for (int& x : arr) {
    x *= 2;
}
// arr 變成 {2, 4, 6, 8, 10}
```

---

## 跳躍敘述：break / continue / goto

### break — 強制離開迴圈

`break` 立即跳出當前迴圈（或 switch），不管條件是否已滿足。

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int n = 10; n > 0; n--) {
        cout << n << ", ";
        if (n == 3) {
            cout << "countdown aborted!" << endl;
            break;  // 當 n==3 時立即離開迴圈
        }
    }
    return 0;
}
```

**輸出：** `10, 9, 8, 7, 6, 5, 4, 3, countdown aborted!`

### continue — 跳過本次迭代

`continue` 跳過本次迴圈剩餘的程式碼，直接進入下一次迭代。

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int n = 10; n > 0; n--) {
        if (n == 5) continue;  // 跳過 n==5 的這次迭代
        cout << n << ", ";
    }
    cout << "liftoff!" << endl;
    return 0;
}
```

**輸出：** `10, 9, 8, 7, 6, 4, 3, 2, 1, liftoff!`（5 被跳過）

### goto — 無條件跳躍（不建議使用）

`goto` 跳到程式碼中某個**標籤 (label)** 的位置（標籤格式：`名稱:`）。

```cpp
#include <iostream>
using namespace std;

int main() {
    int n = 10;

mylabel:
    cout << n << ", ";
    n--;
    if (n > 0) goto mylabel;  // 跳回 mylabel

    cout << "liftoff!" << endl;
    return 0;
}
```

> ⚠️ **現代 C++ 強烈不建議使用 `goto`**：
> - 使程式邏輯難以閱讀與維護
> - 無法與物件生命週期機制配合
> - 幾乎所有 `goto` 的場景都可以用迴圈取代

---

## 選擇敘述：switch

`switch` 適合在**多個固定常數值**中選擇執行路徑，比多層 `if-else if` 更簡潔。

### 語法結構

```cpp
switch (運算式) {
    case 常數1:
        敘述1;
        break;
    case 常數2:
        敘述2;
        break;
    // ... 可以有任意多個 case
    default:
        預設敘述;
}
```

### 執行邏輯

```
1. 計算 switch 的運算式
2. 找到符合的 case 常數 → 執行該 case 後的程式碼
3. 遇到 break → 跳出 switch
4. 若沒有符合的 case → 執行 default（若有）
```

### 範例一：基本 switch

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 2;

    switch (x) {
        case 1:
            cout << "x is 1" << endl;
            break;
        case 2:
            cout << "x is 2" << endl;
            break;
        default:
            cout << "value of x unknown" << endl;
    }
    return 0;
}
```

**輸出：** `x is 2`

### 範例二：多個 case 共用相同邏輯（Fall-through）

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 2;

    switch (x) {
        case 1:
        case 2:
        case 3:
            cout << "x is 1, 2 or 3" << endl;
            break;
        default:
            cout << "x is not 1, 2 nor 3" << endl;
    }
    return 0;
}
```

**輸出：** `x is 1, 2 or 3`

### switch vs if-else 比較

| 比較項目 | switch | if-else if |
|---------|--------|------------|
| 條件類型 | 只能是**整數/字元常數** | 任意運算式（包含範圍） |
| 可讀性 | 多個固定值時較清晰 | 條件複雜時較靈活 |
| 效能 | 可能被最佳化為跳躍表 | 逐條判斷 |
| 適用場景 | 菜單選項、狀態機 | 範圍判斷、複雜條件 |

### 忘記 break 的陷阱（Fall-through）

```cpp
int x = 1;
switch (x) {
    case 1:
        cout << "case 1" << endl;
        // ❌ 忘記 break！
    case 2:
        cout << "case 2" << endl;
        break;
    case 3:
        cout << "case 3" << endl;
        break;
}
// 輸出：case 1
//       case 2   ← 因為沒有 break，繼續往下執行！
```

---

## 常見錯誤與最佳實踐

### ❌ 常見錯誤

#### 1. if 條件中用 `=` 而非 `==`

```cpp
int x = 5;

// ❌ 錯誤：= 是賦值，條件永遠為 true（x 被改為 10）
if (x = 10) {
    cout << "always true" << endl;
}

// ✅ 正確：== 是比較
if (x == 10) {
    cout << "x is 10" << endl;
}
```

#### 2. 無限迴圈（while 條件永遠為真）

```cpp
int n = 10;

// ❌ 錯誤：忘記在迴圈內改變 n
while (n > 0) {
    cout << n << endl;
    // n 永遠不變 → 無限迴圈！
}

// ✅ 正確：確保條件最終會變 false
while (n > 0) {
    cout << n << endl;
    n--;
}
```

#### 3. do-while 少了結尾分號

```cpp
// ❌ 錯誤：缺少分號
do {
    cin >> x;
} while (x != 0)    // ← 這裡需要分號！

// ✅ 正確
do {
    cin >> x;
} while (x != 0);
```

#### 4. switch 忘記 break

```cpp
// ❌ 如果不想 fall-through，每個 case 都要加 break
switch (x) {
    case 1:
        doSomething();
        // 忘記 break，會繼續執行 case 2！
    case 2:
        doSomethingElse();
        break;
}
```

#### 5. switch 中使用變數或範圍

```cpp
int threshold = 5;
int x = 3;

// ❌ 錯誤：switch case 不能使用變數
switch (x) {
    case threshold:    // 編譯錯誤！case 必須是常數
        break;
}

// ✅ 正確：改用 if-else
if (x == threshold) { ... }
```

### ✅ 最佳實踐

| 建議 | 說明 |
|------|------|
| 使用大括號 `{}` | 即使只有一行，建議也加大括號，避免維護時出錯 |
| 避免 `goto` | 使用迴圈和 break/continue 取代 |
| switch 加 default | 處理未預期的值，避免靜默失敗 |
| 範圍式 for 優先 | 遍歷容器時優先使用，減少索引錯誤 |
| 修改元素用 `auto&` | 範圍式 for 要修改元素時加上參考符號 |

---

## 學習重點摘要

```
流程控制完整地圖：

┌─────────────────────────────────────────┐
│           C++ 流程控制                   │
├───────────────┬─────────────────────────┤
│   選擇（分支） │        迴圈              │
│               │                         │
│  if           │  while    先判斷後執行   │
│  if-else      │  do-while 先執行後判斷   │
│  else if      │  for      計次型迴圈     │
│  switch       │  for(:)   範圍式迴圈     │
├───────────────┴─────────────────────────┤
│               跳躍                       │
│  break    — 跳出迴圈 / switch            │
│  continue — 跳過本次迭代                 │
│  goto     — 跳到標籤（不建議）           │
└─────────────────────────────────────────┘

選擇關鍵：
  固定常數值多選一 → switch
  條件複雜/含範圍  → if-else if

迴圈選擇：
  已知執行次數    → for
  未知次數,先判斷 → while
  至少執行一次    → do-while
  遍歷容器/陣列   → for (auto x : range)
```

---

## 現在試試看

1. **初級**：寫一個程式，輸入一個整數，判斷它是正數、負數還是零。
2. **中級**：用 `for` 迴圈印出 1 到 50 中所有 3 的倍數（使用 `continue` 跳過非倍數）。
3. **進階**：寫一個簡易計算機，用 `do-while` 反覆讓使用者輸入兩個數字和一個運算符（`+`, `-`, `*`, `/`），用 `switch` 計算結果，輸入 `q` 時結束程式。

---

*資料來源：[cplusplus.com - Statements and flow control](https://cplusplus.com/doc/tutorial/control/)*
