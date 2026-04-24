# C++ 河內塔（Tower of Hanoi）逐行加註解版

**語言：** C++  
**主題：** 遞迴（Recursion）、分治（Divide and Conquer）  
**日期：** 2026-04-24  
**難度感受：** ⭐⭐⭐⭐  

---

## 這段程式碼做了什麼？

這段程式會列出河內塔的搬移步驟，也就是把 `n` 個圓盤從起點柱搬到目標柱。  
它利用遞迴把大問題拆成兩個較小的同類型問題，因此是學習遞迴思維的經典範例。

---

## 原始程式

```cpp
#include <iostream>
using namespace std;

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << from << " -> " << to << endl;
        return;
    }

    hanoi(n - 1, from, aux, to);
    cout << from << " -> " << to << endl;
    hanoi(n - 1, aux, to, from);
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    return 0;
}
```

---

## 逐行解析

```cpp
#include <iostream>                  // 引入輸入輸出函式庫，讓我們可以使用 cout
using namespace std;                 // 省略 std::，方便直接寫 cout、endl

void hanoi(int n, char from, char to, char aux) {
    // 宣告 hanoi 函式
    // n    : 目前要搬的圓盤數量
    // from : 起點柱（source peg）
    // to   : 目標柱（target peg）
    // aux  : 輔助柱（auxiliary peg）

    if (n == 1) {
        // Base Case：如果只剩 1 個圓盤，就直接從起點搬到終點
        cout << from << " -> " << to << endl;
        // 印出這一步搬移，例如 A -> C
        return;
        // 搬完這個最小問題後，立刻結束這一層函式
    }

    hanoi(n - 1, from, aux, to);
    // 第 1 步：先把上面 n-1 個小圓盤
    // 從 from 搬到 aux，借用 to 當中繼柱
    // 目的：把最大的那個圓盤露出來

    cout << from << " -> " << to << endl;
    // 第 2 步：把目前最大的圓盤
    // 從 from 搬到 to

    hanoi(n - 1, aux, to, from);
    // 第 3 步：再把剛剛暫放在 aux 的 n-1 個小圓盤
    // 從 aux 搬到 to，借用 from 當中繼柱
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    // 呼叫 hanoi：
    // 把 3 個圓盤從 A 搬到 C，B 當輔助柱

    return 0;
    // 程式正常結束
}
```

---

## 核心邏輯拆解

河內塔的規則是：

- 一次只能搬 1 個圓盤
- 大圓盤不能壓在小圓盤上

因此，當你想搬 `n` 個圓盤時，不能直接搬最大的那個，因為它上面壓著 `n-1` 個小圓盤。

所以固定流程一定是：

1. 先把上面 `n-1` 個搬到輔助柱
2. 再把最大的圓盤搬到目標柱
3. 最後把那 `n-1` 個小圓盤搬到目標柱

這三步就是這一行程式的完整意義：

```cpp
hanoi(n - 1, from, aux, to);
cout << from << " -> " << to << endl;
hanoi(n - 1, aux, to, from);
```

你可以把它背成一句口訣：  
**先清路，再搬大，再回收。**

---

## `hanoi(3, 'A', 'C', 'B')` 呼叫展開

主程式呼叫：

```cpp
hanoi(3, 'A', 'C', 'B');
```

意思是：

- 把 3 個圓盤從 `A` 搬到 `C`
- `B` 是輔助柱

### 第一層

```cpp
hanoi(3, A, C, B)
```

會拆成：

1. `hanoi(2, A, B, C)`
2. 印出 `A -> C`
3. `hanoi(2, B, C, A)`

### 第二層左半邊

```cpp
hanoi(2, A, B, C)
```

會拆成：

1. `hanoi(1, A, C, B)`  -> 印出 `A -> C`
2. 印出 `A -> B`
3. `hanoi(1, C, B, A)`  -> 印出 `C -> B`

### 回到第一層

印出：

```cpp
A -> C
```

### 第二層右半邊

```cpp
hanoi(2, B, C, A)
```

會拆成：

1. `hanoi(1, B, A, C)`  -> 印出 `B -> A`
2. 印出 `B -> C`
3. `hanoi(1, A, C, B)`  -> 印出 `A -> C`

### 最終輸出順序

```text
A -> C
A -> B
C -> B
A -> C
B -> A
B -> C
A -> C
```

共 7 步。

---

## 為什麼步數是 `2^n - 1`？

設 `T(n)` 代表搬 `n` 個圓盤需要的步數。

那麼：

- 先搬 `n-1` 個：`T(n-1)` 步
- 搬最大圓盤：`1` 步
- 再搬 `n-1` 個：`T(n-1)` 步

所以公式是：

$$
T(n) = 2T(n-1) + 1
$$

展開後可得：

$$
T(n) = 2^n - 1
$$

例如：

- `n = 1` -> `1` 步
- `n = 2` -> `3` 步
- `n = 3` -> `7` 步
- `n = 4` -> `15` 步

---

## 關鍵概念

| 概念 | 說明 | 記憶口訣 |
|------|------|---------|
| Base Case | `n == 1` 時直接搬，不再遞迴 | 「只剩一個，直接搬」 |
| Recursive Case | 把 `n` 個問題拆成兩個 `n-1` 問題 | 「大問題拆小問題」 |
| Divide and Conquer | 先拆、再解、再合成完整結果 | 「先清路，再搬大，再回收」 |
| Call Stack | 每層遞迴都暫存目前工作，等子問題做完再回來 | 「先壓進去，後面再回來」 |

---

## 我還不懂的地方

- [ ] 為什麼第一個遞迴是搬到 `aux`，不是直接搬到 `to`？
- [ ] 為什麼第二個遞迴的起點改成 `aux`？
- [ ] 為什麼輸出順序剛好就是正確搬法？

---

## 類似用法

- 階乘：用遞迴一路縮小到 `n == 1`
- 費波那契：把問題拆成兩個更小的子問題
- 合併排序：先拆左右半邊，再合併結果

---

## 我的練習

```cpp
#include <iostream>
using namespace std;

int stepCount = 0;

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        stepCount++;
        cout << stepCount << ". " << from << " -> " << to << endl;
        return;
    }

    hanoi(n - 1, from, aux, to);
    stepCount++;
    cout << stepCount << ". " << from << " -> " << to << endl;
    hanoi(n - 1, aux, to, from);
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    cout << "總步數：" << stepCount << endl;
    return 0;
}
```

這個版本多加了一個 `stepCount`，可以更清楚看到每一步的順序。

---

## 總結一句話

> 河內塔的核心不是硬記步驟，而是理解「搬 n 個」可以拆成「搬 n-1、搬最大、再搬 n-1」這三個固定步驟。
