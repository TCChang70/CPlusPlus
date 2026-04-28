# C++ Array 陣列練習題

## 基本概念快速複習

| 操作 | 語法 |
|------|------|
| 宣告陣列 | `int arr[5] = {1, 2, 3, 4, 5};` |
| 存取元素 | `arr[0]`（索引從 0 開始） |
| 取得長度 | `sizeof(arr) / sizeof(arr[0])` |
| 傳入函式 | `void func(int arr[], int n)` |

---

## 練習題 1｜🟢 Easy — 陣列反轉

**題目說明：**
寫一個函式 `reverseArray(int arr[], int n)`，將陣列**原地**反轉（不使用第二個陣列）。

**範例：**
```
輸入：{1, 2, 3, 4, 5}
輸出：{5, 4, 3, 2, 1}

輸入：{10, 20, 30}
輸出：{30, 20, 10}
```

**限制：** 不可使用額外陣列，不可使用 `reverse()`。

**提示：**
> 使用兩個索引，一個從頭、一個從尾，交換後向中間靠近

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        // 交換兩端元素
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    reverseArray(arr, n);
    printArray(arr, n);  // 5 4 3 2 1
    return 0;
}
```

**學習重點：**
- 雙指標 (Two Pointer) 是陣列操作的核心技巧
- `sizeof(arr) / sizeof(arr[0])` 計算陣列長度
- 陣列傳入函式時是傳指標，修改會影響原陣列

</details>

---

## 練習題 2｜🟢 Easy — 找出第二大的數

**題目說明：**
寫一個函式 `secondMax(int arr[], int n)`，找出陣列中**第二大**的數字並回傳。

**範例：**
```
{3, 1, 4, 1, 5, 9, 2, 6}  → 6
{10, 10, 9}                → 9
{1, 2}                     → 1
```

**限制：** 只能走訪陣列一次（單一迴圈），`n >= 2`。

**提示：**
> 維護兩個變數：`max1`（最大）與 `max2`（第二大），邊走訪邊更新

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
#include <climits>
using namespace std;

int secondMax(int arr[], int n) {
    int max1 = INT_MIN, max2 = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;      // 原最大降為第二大
            max1 = arr[i];    // 更新最大值
        } else if (arr[i] > max2 && arr[i] != max1) {
            max2 = arr[i];    // 更新第二大
        }
    }
    return max2;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << secondMax(arr, n) << endl;  // 6

    int arr2[] = {10, 10, 9};
    cout << secondMax(arr2, 3) << endl; // 9
    return 0;
}
```

**學習重點：**
- `INT_MIN`（來自 `<climits>`）代表 int 的最小值，適合當初始值
- `arr[i] != max1` 確保第二大與最大值不同（排除重複）
- 單次遍歷保持 $O(n)$ 時間複雜度

</details>

---

## 練習題 3｜🟡 Medium — 移除重複元素

**題目說明：**
給定一個**已排序**的整數陣列，寫一個函式 `removeDuplicates(int arr[], int n)`，原地移除重複元素，回傳新的有效長度。有效範圍以外的元素不需理會。

**範例：**
```
輸入：{1, 1, 2, 3, 3, 3, 4, 5, 5}，n=9
輸出：有效長度 = 5，有效部分為 {1, 2, 3, 4, 5}

輸入：{0, 0, 1, 1, 1, 2}，n=6
輸出：有效長度 = 3，有效部分為 {0, 1, 2}
```

**限制：** 不可使用額外陣列，原地修改。

**提示：**
> 使用一個慢指標 `slow` 記錄下一個不重複元素要放的位置，快指標 `fast` 往前掃

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int slow = 0;  // 指向最後一個不重複元素的位置

    for (int fast = 1; fast < n; fast++) {
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];  // 將新元素填入有效區域
        }
    }
    return slow + 1;  // 有效長度
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int newLen = removeDuplicates(arr, n);
    cout << "新長度：" << newLen << endl;  // 5
    printArray(arr, newLen);               // 1 2 3 4 5
    return 0;
}
```

**學習重點：**
- **快慢指標 (Fast-Slow Pointer)** 是原地操作陣列的關鍵技巧
- 已排序陣列：重複元素必定相鄰，只需比較前後兩個
- 此技巧廣泛應用於 LeetCode 第 26、27、80 題

</details>

---

## 練習題 4｜🟡 Medium — 旋轉陣列

**題目說明：**
寫一個函式 `rotateArray(int arr[], int n, int k)`，將陣列向右旋轉 `k` 步（原地操作）。

**範例：**
```
arr={1,2,3,4,5,6,7}, k=3  →  {5,6,7,1,2,3,4}
arr={-1,-100,3,99},  k=2  →  {3,99,-1,-100}
```

**說明：** 向右旋轉 1 步表示最後一個元素移到最前面。

**提示：**
> 三次反轉法：① 反轉全部 → ② 反轉前 k 個 → ③ 反轉剩餘部分

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
using namespace std;

void reverse(int arr[], int left, int right) {
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void rotateArray(int arr[], int n, int k) {
    k = k % n;          // 避免 k 大於 n 的情況
    reverse(arr, 0, n - 1);     // ① 反轉全部
    reverse(arr, 0, k - 1);     // ② 反轉前 k 個
    reverse(arr, k, n - 1);     // ③ 反轉剩餘部分
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    rotateArray(arr, n, 3);
    printArray(arr, n);  // 5 6 7 1 2 3 4
    return 0;
}
```

**學習重點：**
- `k % n` 處理 k ≥ n 的邊界情況（旋轉一圈等於沒旋轉）
- 三次反轉法：時間 $O(n)$、空間 $O(1)$，是最優解
- 直覺解法（用額外陣列）空間複雜度為 $O(n)$，三次反轉法更省記憶體

</details>

---

## 練習題 5｜🔴 Hard — 最大子陣列和（Kadane's Algorithm）

**題目說明：**
給定一個含有正負整數的陣列，找出**連續子陣列**中總和最大的值並回傳。

**範例：**
```
{-2, 1, -3, 4, -1, 2, 1, -5, 4}  → 6   (子陣列為 {4,-1,2,1})
{1}                                → 1
{-1, -2, -3}                       → -1  (全為負，取最大單一元素)
```

**限制：** 時間複雜度需為 $O(n)$，空間複雜度 $O(1)$。

**提示：**
> 維護兩個變數：`currentSum`（目前子陣列的和）與 `maxSum`（歷史最大值）。若 `currentSum` 變成負數，就從下一個元素重新開始。

<details>
<summary>📖 查看解答</summary>

```cpp
#include <iostream>
#include <climits>
using namespace std;

int maxSubarraySum(int arr[], int n) {
    int maxSum = INT_MIN;
    int currentSum = 0;

    for (int i = 0; i < n; i++) {
        currentSum += arr[i];

        if (currentSum > maxSum)
            maxSum = currentSum;

        // 若目前總和為負，捨棄，從下一個重新累加
        if (currentSum < 0)
            currentSum = 0;
    }
    return maxSum;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxSubarraySum(arr, n) << endl;  // 6

    int arr2[] = {-1, -2, -3};
    cout << maxSubarraySum(arr2, 3) << endl; // -1
    return 0;
}
```

**學習重點：**
- 這是著名的 **Kadane's Algorithm**，面試高頻題
- 核心思想：負數前綴對後續累加只有害處，果斷捨棄
- 全為負數時 `maxSum` 仍會被最大的負數更新，需用 `INT_MIN` 初始化而非 `0`

**進階挑戰：** 修改程式碼，同時印出最大子陣列的起始與結束索引。

</details>

---

## 難度總覽

| # | 題目 | 難度 | 核心技巧 |
|---|------|------|----------|
| 1 | 陣列反轉 | 🟢 Easy | 雙指標 |
| 2 | 找第二大的數 | 🟢 Easy | 單次遍歷 |
| 3 | 移除重複元素 | 🟡 Medium | 快慢指標 |
| 4 | 旋轉陣列 | 🟡 Medium | 三次反轉法 |
| 5 | 最大子陣列和 | 🔴 Hard | Kadane's Algorithm |

---

**現在試試看：** 題目 3、4、5 都是 LeetCode 經典題（#26、#189、#53），完成後可以到 LeetCode 上提交測試！
