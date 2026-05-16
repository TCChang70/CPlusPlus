# C++ Array 與 Pointer — LeetCode 風格練習題

**語言：** C++  
**主題：** 陣列（Array）、指標（Pointer）、雙指標（Two Pointers）  
**參考來源：** [LeetCode](https://leetcode.com)

---

## 目錄

| # | 題目 | 難度 | 核心概念 |
|---|------|------|---------|
| 1 | 找出陣列中最大值與其索引 | `Easy` | 陣列走訪、指標取值 |
| 2 | 兩數之和 (Two Sum) | `Easy` | 陣列索引、暴力搜尋 |
| 3 | 移除已排序陣列的重複元素 | `Medium` | 雙指標 (in-place) |
| 4 | 合併兩個有序陣列 | `Medium` | 雙指標、反向填入 |
| 5 | 買賣股票的最佳時機 | `Medium` | 陣列掃描、滑動最小值 |
| 6 | 接雨水 (Trapping Rain Water) | `Hard` | 雙指標、前後綴最大值 |

---

## 練習題 1：找出陣列中最大值與其索引

**難度：** `Easy`  
**語言：** C++  
**主題：** 陣列走訪（Array Traversal）、指標取值（Pointer Dereference）  
**對應 LeetCode：** 自訂基礎題（概念來自 [LC 1679](https://leetcode.com/problems/max-number-of-k-sum-pairs/) 前置練習）

---

### 題目說明

給定一個整數陣列 `nums`，請寫一個函式，使用 **指標** 走訪陣列，找出最大值及其第一次出現的索引，並透過指標參數回傳結果。

**函式簽名（Function Signature）：**

```cpp
void findMax(int* arr, int size, int* maxVal, int* maxIdx);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `arr = {3, 1, 7, 2, 5}` | `maxVal=7, maxIdx=2` | 7 在索引 2 |
| `arr = {-5, -1, -3}` | `maxVal=-1, maxIdx=1` | 負數陣列取最大 |
| `arr = {4, 4, 2}` | `maxVal=4, maxIdx=0` | 重複最大值取第一個 |

---

### 限制條件

- 輸入範圍：1 ≤ size ≤ 10⁴，-10⁵ ≤ arr[i] ≤ 10⁵
- 必須使用指標走訪（`*(arr + i)` 或 `arr[i]` 均可）
- 結果透過指標參數 `maxVal`、`maxIdx` 回傳（不使用 return）

---

### 提示

<details>
<summary>顯示提示 1</summary>

用 `*maxVal = arr[0]`、`*maxIdx = 0` 初始化，再從索引 1 開始迴圈比較。

</details>

<details>
<summary>顯示提示 2</summary>

`*(arr + i)` 等同於 `arr[i]`，嘗試兩種寫法都用用看。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

void findMax(int* arr, int size, int* maxVal, int* maxIdx) {
    *maxVal = *arr;       // 等同 arr[0]
    *maxIdx = 0;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxVal) {
            *maxVal = *(arr + i);
            *maxIdx = i;
        }
    }
}

int main() {
    int nums[] = {3, 1, 7, 2, 5};
    int maxVal, maxIdx;
    findMax(nums, 5, &maxVal, &maxIdx);
    cout << "最大值: " << maxVal << "，索引: " << maxIdx << endl;
    return 0;
}
```

**解題思路：**

1. 以陣列第一個元素初始化目前最大值與索引。
2. 迴圈從 `i=1` 開始，每次用 `*(arr + i)` 取值比較。
3. 若更大則更新，透過 `*maxVal` 和 `*maxIdx` 寫入呼叫者的變數。
4. 關鍵：指標參數讓函式能修改外部變數（call by address）。

</details>

---

## 練習題 2：兩數之和 (Two Sum)

**難度：** `Easy`  
**語言：** C++  
**主題：** 陣列索引（Array Indexing）、暴力搜尋（Brute Force）  
**對應 LeetCode：** [#1 Two Sum](https://leetcode.com/problems/two-sum/)

---

### 題目說明

給定整數陣列 `nums` 與目標值 `target`，找出兩個加總等於 `target` 的元素**索引**，並以陣列形式回傳（保證唯一解，且同一元素不能使用兩次）。

**函式簽名（Function Signature）：**

```cpp
// 回傳動態配置的 int 陣列，[0] 為第一個索引，[1] 為第二個索引
int* twoSum(int* nums, int numsSize, int target);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `nums=[2,7,11,15], target=9` | `[0, 1]` | 2+7=9 |
| `nums=[3,2,4], target=6` | `[1, 2]` | 2+4=6 |
| `nums=[3,3], target=6` | `[0, 1]` | 相同值不同索引 |

---

### 限制條件

- 2 ≤ numsSize ≤ 10⁴
- 保證恰好有一組解
- 回傳前需用 `new int[2]` 動態配置記憶體

---

### 提示

<details>
<summary>顯示提示 1</summary>

使用兩層 `for` 迴圈（i 和 j，j > i），檢查 `nums[i] + nums[j] == target`。

</details>

<details>
<summary>顯示提示 2</summary>

找到答案後，將結果存入 `int* result = new int[2]`，設定 `result[0] = i`、`result[1] = j` 後 return。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int* twoSum(int* nums, int numsSize, int target) {
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int* result = new int[2];
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    return nullptr; // 依題意不會到這裡
}

int main() {
    int nums[] = {2, 7, 11, 15};
    int* ans = twoSum(nums, 4, 9);
    cout << "[" << ans[0] << ", " << ans[1] << "]" << endl;
    delete[] ans; // 釋放動態記憶體
    return 0;
}
```

**解題思路：**

1. 兩層迴圈枚舉所有組合，`j` 從 `i+1` 開始避免重複使用同一元素。
2. 找到後用 `new int[2]` 配置堆積記憶體並回傳指標。
3. 重要：呼叫端用完後必須 `delete[] ans` 釋放記憶體，避免 memory leak。
4. 時間複雜度 O(n²)，進階可用 hash map 降為 O(n)。

</details>

---

## 練習題 3：移除已排序陣列的重複元素

**難度：** `Medium`  
**語言：** C++  
**主題：** 雙指標（Two Pointers）、原地修改（In-place）  
**對應 LeetCode：** [#26 Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

---

### 題目說明

給定一個**已升序排序**的整數陣列 `nums`，請**原地（in-place）**移除重複元素，使每個元素只出現一次，回傳不重複元素的個數 `k`。陣列前 `k` 個元素應為不重複的有序元素。

**函式簽名（Function Signature）：**

```cpp
int removeDuplicates(int* nums, int numsSize);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 k | 陣列前 k 個元素 | 說明 |
|------|--------|-----------------|------|
| `[1,1,2]` | `2` | `[1,2]` | 1 重複一次 |
| `[0,0,1,1,1,2,2,3,3,4]` | `5` | `[0,1,2,3,4]` | 各有重複 |

---

### 限制條件

- 1 ≤ numsSize ≤ 3×10⁴
- -100 ≤ nums[i] ≤ 100
- 必須原地修改，不可使用額外陣列（空間複雜度 O(1)）

---

### 提示

<details>
<summary>顯示提示 1</summary>

用兩個指標 `slow` 和 `fast`。`slow` 標記下一個要填入的位置，`fast` 掃描整個陣列。

</details>

<details>
<summary>顯示提示 2</summary>

當 `nums[fast] != nums[slow]` 時，表示遇到新的不重複元素，將它複製到 `nums[++slow]`。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int slow = 0; // 慢指標：指向已處理區間的最後位置
    for (int fast = 1; fast < numsSize; fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    return slow + 1; // 不重複元素個數
}

int main() {
    int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k = removeDuplicates(nums, 10);
    cout << "k = " << k << endl;
    cout << "陣列: ";
    for (int i = 0; i < k; i++) cout << nums[i] << " ";
    cout << endl;
    return 0;
}
```

**解題思路：**

1. `slow=0` 為慢指標，代表「目前不重複序列的尾端」。
2. `fast` 從 1 開始往前掃，遇到與 `nums[slow]` 不同的元素就搬到 `nums[++slow]`。
3. 因陣列已排序，重複元素必然相鄰，此方法能保證正確。
4. 時間 O(n)，空間 O(1)，是雙指標的經典應用。

</details>

---

## 練習題 4：合併兩個有序陣列

**難度：** `Medium`  
**語言：** C++  
**主題：** 雙指標（Two Pointers）、反向填入（Backward Fill）  
**對應 LeetCode：** [#88 Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

---

### 題目說明

給定兩個非遞減有序陣列 `nums1` 和 `nums2`。`nums1` 的長度為 `m+n`（前 `m` 個有效，後 `n` 個為 0 的佔位空間）；`nums2` 長度為 `n`。請將 `nums2` 合併進 `nums1` 使其仍然有序，**原地修改 `nums1`，不回傳值**。

**函式簽名（Function Signature）：**

```cpp
void merge(int* nums1, int m, int* nums2, int n);
```

---

### 輸入 / 輸出範例

| nums1 | m | nums2 | n | 合併結果 |
|-------|---|-------|---|---------|
| `[1,2,3,0,0,0]` | 3 | `[2,5,6]` | 3 | `[1,2,2,3,5,6]` |
| `[1]` | 1 | `[]` | 0 | `[1]` |
| `[0]` | 0 | `[1]` | 1 | `[1]` |

---

### 限制條件

- 0 ≤ m, n ≤ 200，1 ≤ m+n
- **從尾端往前填入**，避免覆蓋尚未處理的元素

---

### 提示

<details>
<summary>顯示提示 1</summary>

若從前面填入，nums1 前段有效元素會被覆蓋。改從**尾端**開始比較 `nums1[m-1]` 與 `nums2[n-1]`，大的放到 `nums1[m+n-1]`。

</details>

<details>
<summary>顯示提示 2</summary>

三個指標：`p1 = m-1`（nums1 有效尾）、`p2 = n-1`（nums2 尾）、`p = m+n-1`（填入位置）。迴圈直到 `p2 < 0`。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

void merge(int* nums1, int m, int* nums2, int n) {
    int p1 = m - 1;       // nums1 有效元素的尾端指標
    int p2 = n - 1;       // nums2 的尾端指標
    int p  = m + n - 1;   // 填入位置（從最後開始）

    while (p2 >= 0) {
        if (p1 >= 0 && nums1[p1] > nums2[p2]) {
            nums1[p--] = nums1[p1--];
        } else {
            nums1[p--] = nums2[p2--];
        }
    }
}

int main() {
    int nums1[] = {1, 2, 3, 0, 0, 0};
    int nums2[] = {2, 5, 6};
    merge(nums1, 3, nums2, 3);
    for (int i = 0; i < 6; i++) cout << nums1[i] << " ";
    cout << endl;
    return 0;
}
```

**解題思路：**

1. 從尾端往前填，最大的元素先確定位置，不會覆蓋未處理的 nums1 元素。
2. 只要 `p2 >= 0` 就繼續；`p1` 先被耗盡也沒關係，此時直接把 nums2 剩餘搬過來。
3. 時間 O(m+n)，空間 O(1)，是反向雙指標的標準解法。

</details>

---

## 練習題 5：買賣股票的最佳時機

**難度：** `Medium`  
**語言：** C++  
**主題：** 陣列掃描（Array Scan）、滑動最小值（Running Minimum）  
**對應 LeetCode：** [#121 Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

---

### 題目說明

給定整數陣列 `prices`，`prices[i]` 代表第 `i` 天的股票價格。你只能交易一次（先買後賣），求**最大利潤**。若無法獲利則回傳 0。

**函式簽名（Function Signature）：**

```cpp
int maxProfit(int* prices, int pricesSize);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `[7,1,5,3,6,4]` | `5` | 第2天買1，第5天賣6，利潤=5 |
| `[7,6,4,3,1]` | `0` | 價格一直跌，無利可圖 |
| `[2,4,1]` | `2` | 第1天買2，第2天賣4 |

---

### 限制條件

- 1 ≤ pricesSize ≤ 10⁵
- 0 ≤ prices[i] ≤ 10⁴
- 時間複雜度要求：O(n)（僅一次走訪）

---

### 提示

<details>
<summary>顯示提示 1</summary>

用一個變數 `minPrice` 記錄走訪過程中遇到的**最低買入價**；另一個變數 `maxProfit` 記錄目前最大利潤。

</details>

<details>
<summary>顯示提示 2</summary>

每一天：先嘗試用 `prices[i] - minPrice` 更新最大利潤，再更新 `minPrice`（若 prices[i] 更小）。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
#include <climits>
using namespace std;

int maxProfit(int* prices, int pricesSize) {
    int minPrice = INT_MAX;  // 目前最低買入價
    int profit   = 0;        // 目前最大利潤

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];           // 更新最低買入價
        } else if (prices[i] - minPrice > profit) {
            profit = prices[i] - minPrice;  // 更新最大利潤
        }
    }
    return profit;
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    cout << "最大利潤: " << maxProfit(prices, 6) << endl;
    return 0;
}
```

**解題思路：**

1. 維護一個「到目前為止見過的最低價格」`minPrice`。
2. 每天計算若今日賣出能賺多少，取歷史最大值。
3. 關鍵：買必須在賣之前，由左到右掃描自然保證此順序。
4. 時間 O(n)，空間 O(1)，是貪心策略的典型應用。

</details>

---

## 練習題 6：接雨水 (Trapping Rain Water)

**難度：** `Hard`  
**語言：** C++  
**主題：** 雙指標（Two Pointers）、前後綴最大值（Prefix/Suffix Max）  
**對應 LeetCode：** [#42 Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

---

### 題目說明

給定非負整數陣列 `height`，代表地形每個位置的高度。計算下雨後**能夠積聚的雨水總量**。

```
範例視覺化：
height = [0,1,0,2,1,0,1,3,2,1,2,1]

    #
  # ##  #
  ######  ##
----------------------------------
積水區域用 ~ 表示，答案 = 6
```

**函式簽名（Function Signature）：**

```cpp
int trap(int* height, int heightSize);
```

---

### 輸入 / 輸出範例

| 輸入 | 輸出 | 說明 |
|------|------|------|
| `[0,1,0,2,1,0,1,3,2,1,2,1]` | `6` | 經典範例 |
| `[4,2,0,3,2,5]` | `9` | 左右有高牆 |
| `[3,0,2,0,4]` | `7` | 中間凹陷 |

---

### 限制條件

- 1 ≤ heightSize ≤ 2×10⁴
- 0 ≤ height[i] ≤ 10⁵
- 時間複雜度：O(n)；空間複雜度：O(1)（雙指標解法）

---

### 提示

<details>
<summary>顯示提示 1</summary>

每個位置能積的水 = `min(左側最高, 右側最高) - 當前高度`。關鍵問題：如何 O(1) 知道左右最高值？

</details>

<details>
<summary>顯示提示 2</summary>

雙指標：`left=0`，`right=n-1`，各自維護 `leftMax`、`rightMax`。  
若 `leftMax < rightMax`，左側是瓶頸，處理 `left` 那端並 `left++`；反之處理右端。

</details>

<details>
<summary>顯示提示 3</summary>

當 `height[left] >= leftMax`，更新 `leftMax`（無法積水）；否則加上 `leftMax - height[left]`（可積水）。

</details>

---

### 參考解答

<details>
<summary>顯示解答</summary>

```cpp
#include <iostream>
using namespace std;

int trap(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            // 左側是瓶頸
            if (height[left] >= leftMax) {
                leftMax = height[left]; // 更新左側最高
            } else {
                water += leftMax - height[left]; // 積水
            }
            left++;
        } else {
            // 右側是瓶頸
            if (height[right] >= rightMax) {
                rightMax = height[right]; // 更新右側最高
            } else {
                water += rightMax - height[right]; // 積水
            }
            right--;
        }
    }
    return water;
}

int main() {
    int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "接到的雨水: " << trap(height, 12) << endl; // 輸出 6
    return 0;
}
```

**解題思路：**

1. **核心觀察**：每格積水量由左右兩側的「較矮牆」決定。
2. **雙指標策略**：哪側的 max 更小，哪側就是瓶頸，優先處理那側。
   - 若 `leftMax < rightMax`：左側積水量已確定（右側再高也不影響），處理 `left`。
   - 反之處理 `right`。
3. 兩指標從兩端往中間夾，每步必定處理一個位置，共 n 步。
4. 時間 O(n)，空間 O(1)，是雙指標最精妙的應用之一。

</details>

---

## 學習重點整理

| 概念 | 應用題 | 說明 |
|------|--------|------|
| 指標走訪 `*(arr+i)` | 題 1 | 等同 `arr[i]`，是理解指標的基礎 |
| 動態配置 `new / delete[]` | 題 2 | 函式回傳陣列時需配置 heap 記憶體 |
| 雙指標（同向） | 題 3 | slow/fast 指標原地過濾 |
| 雙指標（反向填入） | 題 4 | 從尾端合併避免覆蓋 |
| 陣列掃描維護狀態 | 題 5 | 一次走訪同時記錄最小值與最大差 |
| 雙指標（對撞） | 題 6 | 兩端往中間夾，動態決定處理哪側 |

---

> **現在試試看：** 先自己解題，再展開解答對照。若有不同解法也歡迎嘗試，例如題 2 可改用 `unordered_map` 優化到 O(n)，題 6 可先用前後綴陣列版本理解邏輯。
