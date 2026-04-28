# C++ Array 陣列練習題｜第二回合

## 練習題 1｜🟢 Easy — 統計正負零個數

**題目說明：**
寫一個函式，走訪整數陣列一次，分別統計**正數、負數、零**的個數並印出。

**範例：**
```
輸入：{4, -1, 0, 7, -3, 0, -9, 2}
輸出：
正數個數：3
負數個數：3
零的個數：2
```

**限制：** 只能走訪陣列一次。

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

void countPosNegZero(int arr[], int n) {
    int pos = 0, neg = 0, zero = 0;

    for (int i = 0; i < n; i++) {
        if      (arr[i] > 0) pos++;
        else if (arr[i] < 0) neg++;
        else                 zero++;
    }

    cout << "正數個數：" << pos  << endl;
    cout << "負數個數：" << neg  << endl;
    cout << "零的個數：" << zero << endl;
}

int main() {
    int arr[] = {4, -1, 0, 7, -3, 0, -9, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    countPosNegZero(arr, n);
    return 0;
}
```

**學習重點：**
- 單次遍歷同時維護多個計數器，避免重複走訪
- `else if / else` 三路分支確保每個元素只被計算一次

</details>

---

## 練習題 2｜🟢 Easy — 合併兩個已排序陣列

**題目說明：**
給定兩個**已排序**（由小到大）的整數陣列 `a[]` 與 `b[]`，寫一個函式將它們合併成一個新的排序陣列並印出。

**範例：**
```
a = {1, 3, 5, 7}，b = {2, 4, 6, 8}
輸出：{1, 2, 3, 4, 5, 6, 7, 8}

a = {1, 2, 9}，b = {3, 5}
輸出：{1, 2, 3, 5, 9}
```

**提示：**
> 使用三個索引分別指向 `a`、`b`、結果陣列，每次取兩者中較小的元素放入結果

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

void mergeSorted(int a[], int m, int b[], int n, int result[]) {
    int i = 0, j = 0, k = 0;

    while (i < m && j < n) {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }
    // 將剩餘元素補入
    while (i < m) result[k++] = a[i++];
    while (j < n) result[k++] = b[j++];
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    int m = 4, n = 4;
    int result[8];

    mergeSorted(a, m, b, n, result);
    printArray(result, m + n);  // 1 2 3 4 5 6 7 8
    return 0;
}
```

**學習重點：**
- 這是 **Merge Sort（合併排序）** 的核心步驟
- `k++`、`i++` 的後置遞增：先取值使用，再將索引加 1
- 兩個 while 迴圈處理其中一個陣列提前走完的情況

</details>

---

## 練習題 3｜🟡 Medium — 矩陣轉置（2D Array）

**題目說明：**
給定一個 `3×3` 的二維整數陣列，寫一個函式 `transpose(int mat[][3])` 將它**原地**轉置（沿主對角線翻轉）。

**範例：**
```
輸入：          輸出：
1  2  3         1  4  7
4  5  6    →    2  5  8
7  8  9         3  6  9
```

**限制：** 原地操作，不使用額外矩陣。

**提示：**
> 只需交換 `mat[i][j]` 與 `mat[j][i]`，且 `j` 的起始值為 `i+1`（避免重複交換）

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

void transpose(int mat[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {  // j 從 i+1 開始，只處理上三角
            int temp  = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

void printMatrix(int mat[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main() {
    int mat[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    transpose(mat);
    printMatrix(mat);
    return 0;
}
```

**學習重點：**
- 二維陣列傳入函式必須指定**列數**：`int mat[][3]`
- 主對角線元素 `mat[i][i]` 不需交換
- `j` 從 `i+1` 開始確保每對只交換一次，避免換回原位

</details>

---

## 練習題 4｜🟡 Medium — 滑動視窗最大平均值

**題目說明：**
給定整數陣列與視窗大小 `k`，找出所有連續 `k` 個元素中**平均值最大**的那個，回傳該平均值。

**範例：**
```
arr={1, 3, -1, -3, 5, 3, 6}, k=3
各視窗：[1,3,-1]=1.0  [3,-1,-3]=-0.33  [-1,-3,5]=0.33
        [-3,5,3]=1.67  [5,3,6]=4.67
輸出：4.67（即最後一個視窗 {5,3,6}）

arr={2, 4, 6, 8}, k=2  → 7.0（視窗 {6,8}）
```

**限制：** 時間複雜度需為 $O(n)$，不可每個視窗重新加總。

**提示：**
> 先計算第一個視窗的總和，之後每移動一步：加入新元素、移除最左元素（滑動視窗技巧）

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

double maxAvgWindow(int arr[], int n, int k) {
    // 計算第一個視窗的總和
    double windowSum = 0;
    for (int i = 0; i < k; i++)
        windowSum += arr[i];

    double maxSum = windowSum;

    // 滑動視窗：每次加入右端新元素，移除左端舊元素
    for (int i = k; i < n; i++) {
        windowSum += arr[i];         // 加入新元素
        windowSum -= arr[i - k];     // 移除舊元素
        if (windowSum > maxSum)
            maxSum = windowSum;
    }

    return maxSum / k;
}

int main() {
    int arr[] = {1, 3, -1, -3, 5, 3, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxAvgWindow(arr, n, 3) << endl;  // 4.667

    int arr2[] = {2, 4, 6, 8};
    cout << maxAvgWindow(arr2, 4, 2) << endl; // 7
    return 0;
}
```

**學習重點：**
- **滑動視窗 (Sliding Window)** 是陣列面試最高頻技巧之一
- 避免重複計算：每次只做一加一減，維持 $O(n)$ 效率
- 若每個視窗重新加總則為 $O(n \times k)$，資料量大時差距極大

</details>

---

## 練習題 5｜🔴 Hard — 找出所有總和為目標值的配對

**題目說明：**
給定一個整數陣列與目標值 `target`，找出所有總和等於 `target` 的**不重複配對**，印出所有配對。

**範例：**
```
arr={2, 7, 4, 0, 9, 5, 1, 3}, target=7
輸出：
(0, 7)
(2, 5)
(3, 4)
```
（配對以小的數在前、由小到大排序輸出）

**限制：** 同一個索引的元素不可使用兩次，不輸出重複配對。

**提示：**
> 先排序陣列，再使用雙指標從兩端向中間逼近

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
#include <algorithm>  // sort
using namespace std;

void findPairs(int arr[], int n, int target) {
    sort(arr, arr + n);  // 先排序

    int left = 0, right = n - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            cout << "(" << arr[left] << ", " << arr[right] << ")" << endl;
            left++;
            right--;
            // 跳過重複元素
            while (left < right && arr[left] == arr[left - 1])  left++;
            while (left < right && arr[right] == arr[right + 1]) right--;
        } else if (sum < target) {
            left++;   // 總和太小，左指標右移
        } else {
            right--;  // 總和太大，右指標左移
        }
    }
}

int main() {
    int arr[] = {2, 7, 4, 0, 9, 5, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    findPairs(arr, n, 7);
    return 0;
}
```

**輸出：**
```
(0, 7)
(2, 5)
(3, 4)
```

**學習重點：**
- **排序 + 雙指標** 是 Two Sum 類問題的標準解法，時間複雜度 $O(n \log n)$
- 暴力解雙層迴圈為 $O(n^2)$，資料量大時效能差異明顯
- 跳過重複元素的兩行 while 確保不輸出重複配對
- `sort(arr, arr + n)` 使用 STL 的 `<algorithm>` 排序

**進階挑戰：** 改用 `unordered_set` 實作 $O(n)$ 解法。

</details>

---

## 難度總覽

| # | 題目 | 難度 | 核心技巧 |
|---|------|------|----------|
| 1 | 統計正負零個數 | 🟢 Easy | 單次遍歷多計數器 |
| 2 | 合併已排序陣列 | 🟢 Easy | 三指標合併 |
| 3 | 矩陣轉置 | 🟡 Medium | 2D Array 操作 |
| 4 | 滑動視窗最大平均值 | 🟡 Medium | 滑動視窗 |
| 5 | 找總和為目標的配對 | 🔴 Hard | 排序 + 雙指標 |

---

**現在試試看：** 題目 4（滑動視窗）和題目 5（兩數之和）都是 LeetCode 熱門題型（#643、#1），完成後試著挑戰進階變形版本！

