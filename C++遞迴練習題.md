# C++ 遞迴練習題

## 練習題 1｜🟢 Easy — 計算次方

**題目說明：**
寫一個遞迴函式 `power(int base, int exp)`，計算 `base` 的 `exp` 次方，不使用 `pow()`。

**範例：**
```
power(2, 0)  → 1
power(2, 3)  → 8
power(3, 4)  → 81
power(5, 1)  → 5
```

**限制：** `exp >= 0`，使用遞迴，禁止使用迴圈。

**提示：**
> $base^{exp} = base \times base^{exp-1}$，當 $exp = 0$ 時結果為 1

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int power(int base, int exp) {
    // Base Case：任何數的 0 次方為 1
    if (exp == 0) return 1;

    // Recursive Case：base 乘以 base^(exp-1)
    return base * power(base, exp - 1);
}

int main() {
    cout << power(2, 3)  << endl;  // 8
    cout << power(3, 4)  << endl;  // 81
    cout << power(5, 0)  << endl;  // 1
    return 0;
}
```

**學習重點：**
- `exp` 每次減 1，遞迴深度為 `exp` 層
- 進階優化：可用快速冪 (Fast Power) 將複雜度從 $O(n)$ 降到 $O(\log n)$

</details>

---

## 練習題 2｜🟢 Easy — 陣列最大值

**題目說明：**
寫一個遞迴函式 `arrayMax(int arr[], int n)`，找出長度為 `n` 的整數陣列中的最大值。

**範例：**
```
arr = {3, 7, 2, 9, 4},  n=5  → 9
arr = {1},               n=1  → 1
arr = {-3, -1, -5},      n=3  → -1
```

**限制：** 使用遞迴，禁止使用迴圈或 `max_element()`。

**提示：**
> 陣列最大值 = max(第一個元素, 剩餘陣列的最大值)

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int arrayMax(int arr[], int n) {
    // Base Case：只剩一個元素
    if (n == 1) return arr[0];

    // Recursive Case：比較第一個元素與剩餘部分的最大值
    int restMax = arrayMax(arr + 1, n - 1);
    return (arr[0] > restMax) ? arr[0] : restMax;
}

int main() {
    int arr[] = {3, 7, 2, 9, 4};
    cout << arrayMax(arr, 5) << endl;  // 9

    int arr2[] = {-3, -1, -5};
    cout << arrayMax(arr2, 3) << endl; // -1
    return 0;
}
```

**學習重點：**
- `arr + 1` 是指標位移，指向陣列第二個元素開始的子陣列
- 問題規模每次縮小 1（`n-1`），直到只剩一個元素

</details>

---

## 練習題 3｜🟡 Medium — 判斷回文字串

**題目說明：**
寫一個遞迴函式 `isPalindrome(string s, int left, int right)`，判斷字串 `s` 是否為回文 (Palindrome)，回傳 `bool`。

**範例：**
```
isPalindrome("racecar", 0, 6)  → true
isPalindrome("hello",   0, 4)  → false
isPalindrome("a",       0, 0)  → true
isPalindrome("abba",    0, 3)  → true
```

**限制：** 使用遞迴，禁止使用 `reverse()`。

**提示：**
> 若首尾字元相同，再檢查去掉首尾後的子字串是否也是回文

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string s, int left, int right) {
    // Base Case：指標交叉或相遇，確認完畢
    if (left >= right) return true;

    // 首尾字元不同，不是回文
    if (s[left] != s[right]) return false;

    // Recursive Case：縮小範圍繼續檢查
    return isPalindrome(s, left + 1, right - 1);
}

int main() {
    string s1 = "racecar";
    cout << boolalpha << isPalindrome(s1, 0, s1.length() - 1) << endl;  // true

    string s2 = "hello";
    cout << isPalindrome(s2, 0, s2.length() - 1) << endl;  // false
    return 0;
}
```

**學習重點：**
- 雙指標從兩端向中間收縮是回文判斷的標準思路
- `left >= right` 涵蓋奇數長度（相遇）與偶數長度（交叉）兩種情況
- `boolalpha` 讓 `cout` 印出 `true/false` 而非 `1/0`

</details>

---

## 練習題 4｜🔴 Hard — 爬樓梯問題

**題目說明：**
你在爬一段 `n` 階的樓梯，每次可以選擇跨 **1 階** 或 **2 階**。請寫一個遞迴函式 `climbStairs(int n)`，計算共有幾種不同的爬法。

**範例：**
```
climbStairs(1)  → 1   (只有：1)
climbStairs(2)  → 2   (1+1 或 2)
climbStairs(3)  → 3   (1+1+1、1+2、2+1)
climbStairs(5)  → 8
```

**限制：** 使用遞迴實作，`n >= 1`。

**提示：**
> 到達第 n 階，只能從第 n-1 階跨 1 步，或從第 n-2 階跨 2 步過來。思考這和哪個著名數列有關？

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int climbStairs(int n) {
    // Base Case
    if (n == 1) return 1;
    if (n == 2) return 2;

    // Recursive Case：從 n-1 來的方法數 + 從 n-2 來的方法數
    return climbStairs(n - 1) + climbStairs(n - 2);
}

int main() {
    cout << climbStairs(1) << endl;  // 1
    cout << climbStairs(3) << endl;  // 3
    cout << climbStairs(5) << endl;  // 8
    return 0;
}
```

**學習重點：**
- 這本質上是 **費波那契數列 (Fibonacci Sequence)** 的變形
- 純遞迴有大量重複計算，複雜度為 $O(2^n)$；實務上應搭配 **記憶化 (Memoization)** 優化至 $O(n)$
- 這是動態規劃 (Dynamic Programming) 的入門題型

**進階挑戰：** 使用 `unordered_map` 加上記憶化改寫，觀察 `n=40` 時的速度差異。

</details>

---

## 練習題 5｜🔴 Hard — 迷宮尋路

**題目說明：**
給定一個 4×4 的迷宮，`0` 代表可通行，`1` 代表牆壁。從左上角 `(0,0)` 出發，目標到達右下角 `(3,3)`，每次只能向右或向下移動。印出所有可能的路徑（以座標序列表示）。

**迷宮：**
```cpp
int maze[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 0},
    {0, 1, 0, 0}
};
```

**範例輸出（其中一條路徑）：**
```
(0,0) → (0,1) → (1,1) → (1,2) → (2,2) → (2,3) → (3,3)
```

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
#include <string>
using namespace std;

int maze[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 0},
    {0, 1, 0, 0}
};

void findPath(int row, int col, string path) {
    // 超出邊界或遇到牆壁，停止
    if (row > 3 || col > 3 || maze[row][col] == 1) return;

    // 加入目前位置
    path += "(" + to_string(row) + "," + to_string(col) + ")";

    // Base Case：到達終點
    if (row == 3 && col == 3) {
        cout << path << endl;
        return;
    }

    path += " → ";

    // Recursive Case：向右或向下
    findPath(row, col + 1, path);  // 向右
    findPath(row + 1, col, path);  // 向下
}

int main() {
    findPath(0, 0, "");
    return 0;
}
```

**輸出：**
```
(0,0) → (0,1) → (1,1) → (1,2) → (2,2) → (2,3) → (3,3)
(0,0) → (1,0) → (1,1) → (1,2) → (2,2) → (2,3) → (3,3)
```

**學習重點：**
- 遞迴天然形成 **深度優先搜尋 (DFS)**
- `path` 以傳值方式傳遞，每條分支擁有獨立的路徑記錄，不需回溯還原
- 邊界檢查必須放在最前面，避免陣列越界 (Array Out of Bounds)

</details>

---

## 難度總覽

| # | 題目 | 難度 | 核心概念 |
|---|------|------|----------|
| 1 | 計算次方 | 🟢 Easy | 數學遞迴 |
| 2 | 陣列最大值 | 🟢 Easy | 指標 + 遞迴 |
| 3 | 判斷回文 | 🟡 Medium | 雙指標遞迴 |
| 4 | 爬樓梯 | 🔴 Hard | Fibonacci / DP 入門 |
| 5 | 迷宮尋路 | 🔴 Hard | DFS 搜尋 |

---

