# 第 2 週：排序演算法與穩定性 (Sorting Algorithms)

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、什麼是排序？ (What is Sorting?)

排序是「**將一組資料依照特定規則重新排列**」的過程。  
就像整理書架：可以按書名字母順序、出版年份或書背顏色排列，關鍵是規則要一致。

**為什麼重要？**
- 排序後的資料可以使用二元搜尋（$O(\log n)$）而非線性搜尋（$O(n)$）
- 許多演算法依賴「已排序」的前提
- 理解排序是學習時間複雜度分析的最佳入口

---

## 二、排序的穩定性 (Stability)

**定義：** 若排序後，**相同鍵值的元素相對位置不變**，則稱為穩定排序（Stable Sort）。

```
原始：  [3a, 1, 3b, 2]   ← 3a 與 3b 值相同，a 在 b 前
穩定排序後：[1, 2, 3a, 3b]  ← 3a 仍在 3b 前 ✓
不穩定排序後：[1, 2, 3b, 3a] ← 相對位置可能改變 ✗
```

**何時重要？** 多欄位排序時（先按姓名排，再按成績排），穩定性確保第一次排序的結果被保留。

---

## 三、各排序演算法比較

| 演算法 | 最佳時間 | 平均時間 | 最壞時間 | 空間 | 穩定性 |
|--------|---------|---------|---------|------|-------|
| 氣泡排序 Bubble Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | ✅ 穩定 |
| 挑選排序 Selection Sort | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | ❌ 不穩定 |
| 插入排序 Insertion Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | ✅ 穩定 |
| 合併排序 Merge Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | ✅ 穩定 |
| 快速排序 Quick Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ | ❌ 不穩定 |
| 堆積排序 Heap Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ | ❌ 不穩定 |

---

## 四、挑選排序法 (Selection Sort)

### 4.1 概念說明

「每次從**未排序部分**找出最小值，放到已排序部分的末尾。」

```
原始：  [64, 25, 12, 22, 11]

第1輪：找到最小 11，與 arr[0] 交換
       [11, 25, 12, 22, 64]

第2輪：找到最小 12，與 arr[1] 交換
       [11, 12, 25, 22, 64]

第3輪：找到最小 22，與 arr[2] 交換
       [11, 12, 22, 25, 64]

第4輪：找到最小 25，與 arr[3] 交換
       [11, 12, 22, 25, 64]  ← 完成
```

### 4.2 為什麼不穩定？

```
原始：[3a, 3b, 1]
第1輪：找最小 1，與 3a 交換 → [1, 3b, 3a]
排序後：[1, 3b, 3a]  ← 3a 與 3b 的相對位置改變了！
```

### 4.3 程式碼實作

```cpp
#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // 找未排序部分 [i..n-1] 的最小值索引
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        // 將最小值與 arr[i] 交換
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前: ";
    printArray(arr, n);

    selectionSort(arr, n);

    cout << "排序後: ";
    printArray(arr, n);

    return 0;
}
```

**輸出：**
```
排序前: 64 25 12 22 11
排序後: 11 12 22 25 64
```

---

## 五、插入排序法 (Insertion Sort)

### 5.1 概念說明

「像整理撲克牌：每次拿起一張牌，**插入**到手中已排好的正確位置。」

```
原始：  [5, 2, 4, 6, 1, 3]

取 2：[5] → 2 < 5，插在前面 → [2, 5]
取 4：[2,5] → 4 < 5, 4 > 2 → [2, 4, 5]
取 6：[2,4,5] → 6 > 5 → [2, 4, 5, 6]
取 1：全部右移 → [1, 2, 4, 5, 6]
取 3：插入 2 和 4 之間 → [1, 2, 3, 4, 5, 6]
```

### 5.2 程式碼實作

```cpp
#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];   // 目前要插入的值
        int j = i - 1;

        // 將所有大於 key 的已排序元素向右移一位
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;   // 插入到正確位置
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {5, 2, 4, 6, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前: ";
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "排序後: ";
    printArray(arr, n);

    return 0;
}
```

---

## 六、合併排序法 (Merge Sort)

### 6.1 概念說明（分治策略）

「**分**：將陣列對半切到只剩 1 個元素（必定有序）。  
**治**：**合併**兩個有序的子陣列成一個有序陣列。」

```
[38, 27, 43, 3, 9, 82, 10]
      分        分
[38,27,43]  [3,9,82,10]
  分    分      分    分
[38][27,43] [3,9] [82,10]
      分           分
  [27][43]      [82][10]
      合           合
  [27,43]       [10,82]
      合     合
  [27,38,43] [3,9,10,82]
          合
  [3,9,10,27,38,43,82]
```

### 6.2 程式碼實作

```cpp
#include <iostream>
using namespace std;

// 合併兩個已排序的子陣列 arr[l..m] 和 arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // 建立暫存陣列
    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // 合併回 arr[]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])   arr[k++] = L[i++];  // <= 保證穩定性
        else                arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);       // 排序左半
        mergeSort(arr, m + 1, r);   // 排序右半
        merge(arr, l, m, r);        // 合併
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    cout << "排序後: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

## 七、快速排序法 (Quick Sort)

### 7.1 概念說明

「選定一個 **Pivot（樞軸）**，將陣列分成『小於 pivot 的左區』和『大於 pivot 的右區』，再遞迴處理兩區。」

```
[3, 6, 8, 10, 1, 2, 1]  ← 選 pivot = arr[末] = 1
partition 後: [1, 1, | 8, 10, 3, 6, 2]  ← 1 放到正確位置
遞迴左：[1, 1] → 已完成
遞迴右：[8, 10, 3, 6, 2] → 繼續…
```

### 7.2 程式碼實作

```cpp
#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 選最後一個元素為 pivot
    int i = low - 1;        // i 指向「小於 pivot 區域」的末端

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);  // pivot 放到正確位置
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);   // 排序 pivot 左側
        quickSort(arr, pi + 1, high);  // 排序 pivot 右側
    }
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    cout << "排序後: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

## 八、常見錯誤與注意事項

| 錯誤類型 | 說明 | 建議 |
|---------|------|------|
| 把 Selection Sort 誤認為穩定 | 交換操作會破壞相對順序 | 記住：選擇排序不穩定 |
| Quick Sort 選到最壞 pivot | 已排序陣列選末端 → $O(n^2)$ | 使用「三數取中」選 pivot |
| Merge Sort 忘記釋放記憶體 | `new` 後需 `delete[]` | 或改用 `std::vector` 自動管理 |
| Insertion Sort 的 while 條件 | `j >= 0` 必須加，否則陣列越界 | 兩個條件缺一不可 |

---

## 九、學習筆記摘要

```
本週關鍵概念：
┌──────────────────────────────────────────────────────┐
│ ✦ 穩定排序：相同鍵值元素排序後相對位置不變           │
│ ✦ Selection Sort：不穩定，交換破壞相對順序 O(n²)    │
│ ✦ Insertion Sort：穩定，像整理撲克牌 O(n²)          │
│ ✦ Merge Sort：穩定，分治，O(n log n)，需 O(n) 空間  │
│ ✦ Quick Sort：不穩定，平均 O(n log n)，最壞 O(n²)   │
└──────────────────────────────────────────────────────┘
```

**現在試試看：**
> 輸入陣列 `{5, 3, 8, 1, 9, 2, 7, 4, 6}`，分別用 Selection Sort 與 Insertion Sort 手動追蹤每一輪的陣列狀態，確認兩者的差異。
