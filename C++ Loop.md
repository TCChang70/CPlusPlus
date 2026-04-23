# C++ 迴圈（Loop）學習文件

## 1. 概念定義（What）

迴圈是「讓電腦重複執行同一段動作的指令」。就像工廠的輸送帶，每個零件經過同樣的工站被處理，直到所有零件處理完畢，輸送帶才停下來。

C++ 提供三種迴圈：

| 迴圈 | 白話說明 |
|------|---------|
| `for` | 「重複 N 次」— 知道次數時用 |
| `while` | 「一直做，直到條件不成立」— 不確定次數時用 |
| `do-while` | 「先做一次，再判斷要不要繼續」— 至少執行一次時用 |
| `range-for` | 「逐一處理集合裡的每個元素」— C++11 現代寫法 |

---

## 2. 使用時機（When）

- 走訪陣列或容器的每個元素
- 重複計算（累加、累乘、搜尋）
- 等待使用者輸入直到合法為止
- 實作遊戲主迴圈（Game Loop）
- 矩陣、二維陣列的巢狀走訪

---

## 3. 語法結構

### `for` 迴圈

```cpp
for (<初始化>; <條件>; <更新>) {
    // 迴圈本體
}
```

### `while` 迴圈

```cpp
while (<條件>) {
    // 迴圈本體
}
```

### `do-while` 迴圈

```cpp
do {
    // 迴圈本體（至少執行一次）
} while (<條件>);  // ← 注意分號！
```

### Range-based `for`（C++11）

```cpp
for (<型別> <變數> : <容器或陣列>) {
    // 逐元素處理
}
```

---

## 4. 最小可執行範例

### `for` — 印出 1 到 5

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    // 輸出：1 2 3 4 5
    return 0;
}
```

### `while` — 數字加總直到超過 100

```cpp
#include <iostream>
using namespace std;

int main() {
    int sum = 0, n = 1;
    while (sum <= 100) {
        sum += n;
        n++;
    }
    cout << "總和超過100時 n = " << n - 1 << ", sum = " << sum << endl;
    // 輸出：總和超過100時 n = 14, sum = 105
    return 0;
}
```

### `do-while` — 確保使用者輸入正數

```cpp
#include <iostream>
using namespace std;

int main() {
    int input;
    do {
        cout << "請輸入一個正數：";
        cin >> input;
    } while (input <= 0);  // 輸入不合法就再問一次
    cout << "你輸入了：" << input << endl;
    return 0;
}
```

### Range-based `for` — 走訪 vector

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {10, 20, 30, 40, 50};
    for (int n : nums) {
        cout << n << " ";
    }
    // 輸出：10 20 30 40 50
    return 0;
}
```

---

## 5. 進階用法

### 5-1. `break` 與 `continue`

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 10; i++) {
        if (i == 5) continue;  // 跳過 5
        if (i == 8) break;     // 到 8 就停止
        cout << i << " ";
    }
    // 輸出：1 2 3 4 6 7
    return 0;
}
```

| 關鍵字 | 作用 |
|--------|------|
| `break` | 立即跳出整個迴圈 |
| `continue` | 跳過本次迭代，繼續下一次 |

---

### 5-2. 巢狀迴圈 — 九九乘法表

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << i << "x" << j << "=" << i * j << "\t";
        }
        cout << "\n";
    }
    return 0;
}
```

> 注意：巢狀迴圈的時間複雜度是 $O(n^2)$，超過 3 層時要特別注意效能。

---

### 5-3. Range-for 搭配引用（避免複製）

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> names = {"Alice", "Bob", "Charlie"};

    // 唯讀走訪 — 用 const &
    for (const string& name : names) {
        cout << name << "\n";
    }

    // 修改元素 — 用 & （引用，Reference）
    for (string& name : names) {
        name += "!";
    }

    for (const string& name : names) {
        cout << name << "\n";
    }
    // 輸出：Alice! Bob! Charlie!
    return 0;
}
```

> 對大型物件（如 `string`、`struct`）一律用 `const T&` 走訪，避免不必要的複製（Copy）開銷。

---

### 5-4. 現代 C++：`auto` 搭配 range-for

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // auto 讓編譯器自動推導型別
    for (auto x : v) {
        cout << x * x << " ";
    }
    // 輸出：1 4 9 16 25
    return 0;
}
```

---

## 6. 常見錯誤（Common Pitfalls）

### Pitfall 1 — 無窮迴圈（Infinite Loop）

```cpp
// ❌ 錯誤寫法
int i = 0;
while (i < 10) {
    cout << i;
    // 忘記更新 i！
}
// 錯誤原因：i 永遠是 0，條件永遠成立，程式卡死

// ✅ 正確寫法
int i = 0;
while (i < 10) {
    cout << i;
    i++;  // 記得更新計數器
}
```

---

### Pitfall 2 — 差一錯誤（Off-by-one Error）

```cpp
// ❌ 錯誤寫法：陣列大小是 5，卻走到 index 5（越界！）
int arr[5] = {1, 2, 3, 4, 5};
for (int i = 0; i <= 5; i++) {  // 應該是 i < 5
    cout << arr[i];
}
// 錯誤原因：arr[5] 是未定義行為（Undefined Behavior，UB）

// ✅ 正確寫法
for (int i = 0; i < 5; i++) {
    cout << arr[i];
}
// 或直接用 range-for 完全避免此問題：
for (int x : arr) {
    cout << x;
}
```

---

### Pitfall 3 — `do-while` 忘記分號

```cpp
// ❌ 錯誤寫法
do {
    cout << "hello";
} while (true)  // 缺少分號 → 編譯錯誤

// ✅ 正確寫法
do {
    cout << "hello";
} while (true);
```

---

### Pitfall 4 — Range-for 修改元素忘記加 `&`

```cpp
// ❌ 錯誤寫法（修改的是副本，不影響原始容器）
vector<int> v = {1, 2, 3};
for (int x : v) {
    x = x * 2;  // x 是副本，原始 v 不變
}

// ✅ 正確寫法（加上引用符號 &）
for (int& x : v) {
    x = x * 2;  // 修改到原始元素
}
```

---

### Pitfall 5 — `int` 計數器溢位

```cpp
// ❌ 潛在問題：n 很大時 i * i 可能溢位
for (int i = 0; i < 100000; i++) {
    long long result = i * i;  // i * i 先以 int 計算，再轉 long long → 溢位
}

// ✅ 正確寫法
for (long long i = 0; i < 100000; i++) {
    long long result = i * i;  // 全程以 long long 計算
}
```

---

## 7. 選擇迴圈的判斷樹

```
要重複執行嗎？
    │
    ├─ 知道確切次數 / 走訪容器？
    │       ├─ 走訪容器 (vector/array) → range-for
    │       └─ 固定次數              → for
    │
    └─ 不確定次數？
            ├─ 需要先執行一次再判斷？ → do-while
            └─ 先判斷再執行？        → while
```

---

## 現在試試看

1. **Easy**：用 `for` 迴圈印出 1 到 100 中所有 3 的倍數。
2. **Medium**：用 `while` 迴圈實作「猜數字」遊戲，程式隨機產生 1-100 的數，使用者一直猜直到猜對。
3. **Hard**：用巢狀迴圈輸出一個由 `*` 組成的等腰三角形，高度由使用者輸入決定。

Similar code found with 1 license type