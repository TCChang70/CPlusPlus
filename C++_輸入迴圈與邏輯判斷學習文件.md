# C++ 資料輸入迴圈與邏輯判斷學習文件

本文件依據 C++ Reference（cppreference）整理，聚焦初學與進階都必須掌握的「輸入」、「迴圈」、「邏輯判斷」核心觀念。

## 1. 必學地圖（先學這些）

1. 輸入串流狀態：`std::cin >> x` 成功與失敗的意義。
2. 以輸入當條件的迴圈：`while (std::cin >> x)`。
3. `while`、`for`、`do-while` 三種迴圈差異與使用時機。
4. 比較運算子：`== != < <= > >=`。
5. 邏輯運算子：`&& || !` 與短路求值（short-circuit）。
6. `if / else if / else` 條件分支與條件順序設計。
7. 常見輸入錯誤修復：`cin.clear()` 與 `cin.ignore(...)`。

---

## 2. 資料輸入核心

### 2.1 `std::cin >> x` 的真實行為

- 讀取成功：回傳可轉為 `true` 的串流狀態。
- 讀取失敗（型別不符、EOF 等）：串流狀態為失敗，可轉為 `false`。
- 因為串流可轉成 `bool`，所以可以直接放在條件式。

範例：

```cpp
int x;
while (std::cin >> x) {
    // 只有成功讀到整數才會進來
    std::cout << "read: " << x << '\n';
}
```

### 2.2 `operator>>` 與 `getline` 的差異

- `operator>>`：以空白（空格、Tab、換行）為分隔。
- `std::getline`：讀整行（含空白內容）。

常見坑：先 `cin >> n` 再 `getline(cin, s)` 時，前一次留下的換行字元會被 `getline` 直接讀走。

修正方式：

```cpp
int n;
std::string s;
std::cin >> n;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::getline(std::cin, s);
```

需要 `#include <limits>`。

### 2.3 輸入失敗後的恢復

當使用者輸入非預期型別（例如要整數卻輸入字串）：

```cpp
int x;
while (true) {
    if (std::cin >> x) {
        break; // 成功
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "請輸入整數：";
}
```

---

## 3. 迴圈必要觀念

### 3.1 `while`：條件成立才執行

```cpp
int i = 0;
while (i < 5) {
    std::cout << i << '\n';
    ++i;
}
```

適合：不知道會跑幾次、由輸入或條件決定次數。

### 3.2 `for`：次數型迴圈最清楚

```cpp
for (int i = 0; i < 5; ++i) {
    std::cout << i << '\n';
}
```

適合：已知次數、陣列索引、計數控制。

### 3.3 `do-while`：至少執行一次

```cpp
int menu;
do {
    std::cout << "1.Start 2.Exit: ";
    std::cin >> menu;
} while (menu != 2);
```

適合：選單、重試流程。

### 3.4 `break` 與 `continue`

- `break`：直接跳出整個迴圈。
- `continue`：跳過本輪後續、進入下一輪。

---

## 4. 邏輯判斷必要觀念

### 4.1 比較運算子

- 相等：`==`
- 不等：`!=`
- 大小：`< <= > >=`

注意：`a < b < c` 在 C++ 不是數學連鎖比較，會先算 `(a < b)`（得到 `true/false`），再拿布林值去和 `c` 比。

正確寫法：

```cpp
(a < b) && (b < c)
```

### 4.2 邏輯運算子與短路

- `A && B`：A 為假時，B 不會執行。
- `A || B`：A 為真時，B 不會執行。
- `!A`：邏輯反轉。

短路常見安全用法：

```cpp
if (ptr != nullptr && *ptr > 0) {
    // 先確認 ptr 非空，才解參考
}
```

### 4.3 條件優先順序

`!` > 比較運算（如 `<`, `==`）> `&&` > `||`

建議：複雜條件一律加括號，提升正確性與可讀性。

### 4.4 條件設計原則

- 先寫「排除條件」再寫主流程，減少巢狀層數。
- `if/else if/else` 由高優先規則往下排。
- 同一變數多分支（離散值）可考慮 `switch`。

---

## 5. 必背輸入迴圈模板

### 模板 A：讀到 EOF 為止

```cpp
int x;
while (std::cin >> x) {
    // process(x)
}
```

### 模板 B：哨兵值結束（例如 -1）

```cpp
int x;
while (std::cin >> x && x != -1) {
    // process(x)
}
```

### 模板 C：固定讀 N 筆

```cpp
int n;
std::cin >> n;
for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    // process(x)
}
```

### 模板 D：輸入驗證重試

```cpp
int x;
while (true) {
    std::cout << "請輸入 1~100: ";
    if (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
    }
    if (x < 1 || x > 100) {
        std::cout << "範圍錯誤\n";
        continue;
    }
    break;
}
```

---

## 6. 經典練習題（按順序）

1. 連續讀入整數直到 EOF，輸出總和與平均。
2. 讀入整數直到遇到 `-1`，找出最大值與最小值。
3. 讀入一行字串，統計英文字母、數字、空白數量。
4. 寫一個輸入驗證函式，只接受 1~100。
5. 給三個整數 `a, b, c`，判斷是否嚴格遞增（`a < b < c` 應正確寫成邏輯與）。
6. 選單程式：錯誤輸入時可恢復並重新提示。

---

## 7. 常見錯誤清單

1. 把比較寫成指定：`if (x = 5)`（應是 `==`）。
2. 用 `while (!cin.eof())` 讀資料（通常是錯誤寫法）。
3. 忘記在失敗後 `clear + ignore`，導致無限失敗迴圈。
4. 混用 `>>` 與 `getline` 卻未處理殘留換行。
5. 寫出 `a < b < c` 造成邏輯誤判。
6. 條件太長不加括號，造成優先順序誤解。

---

## 8. 對應 cppreference 條目

- `std::cin`: https://en.cppreference.com/w/cpp/io/cin
- `while`: https://en.cppreference.com/w/cpp/language/while
- `for`: https://en.cppreference.com/w/cpp/language/for
- `do-while`: https://en.cppreference.com/w/cpp/language/do
- logical operators (`&& || !`): https://en.cppreference.com/w/cpp/language/operator_logical
- comparison operators (`== != < <= > >=`): https://en.cppreference.com/w/cpp/language/operator_comparison

---

## 9. 一頁總結

- 讀輸入最穩定的主迴圈：`while (std::cin >> x)`。
- 任何使用者輸入都要考慮「輸入失敗」與「清理緩衝」。
- 條件判斷先求正確，再求精簡；複雜條件加括號。
- `&&`、`||` 的短路是安全與效能的重要工具。
- 看到 `a < b < c` 就改成 `(a < b) && (b < c)`。
