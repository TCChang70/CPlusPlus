# 第 2 週 程式碼解析：排序演算法與穩定性

> 對應練習檔：`week2_sorting_practice.cpp`  
> 對應學習文件：[DS_Week2_Sorting.md](DS_Week2_Sorting.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔實作並示範 5 種排序演算法，以及穩定性（stability）的具體驗證：

| 編號 | 函式 | 排序法 | 穩定性 | 時間複雜度 |
|------|------|--------|--------|-----------|
| 範例 1 | `bubbleSort` | 氣泡排序 Bubble Sort | ✅ 穩定 | $O(n^2)$ |
| 範例 2 | `selectionSort` | 挑選排序 Selection Sort | ❌ 不穩定 | $O(n^2)$ |
| 範例 3 | `insertionSort` | 插入排序 Insertion Sort | ✅ 穩定 | $O(n^2)$ / $O(n)$ |
| 範例 4 | `mergeSort` | 合併排序 Merge Sort | ✅ 穩定 | $O(n \log n)$ |
| 範例 5 | `quickSort` | 快速排序 Quick Sort | ❌ 不穩定 | $O(n \log n)$ 平均 |

---

## 輔助結構：`LabeledVal`（穩定性展示）

```cpp
struct LabeledVal {
    int val;
    char tag;   // 'a', 'b' 區分相同值的元素
};
```

用來模擬「相同鍵值但不同身份」的元素（例如 `3a`、`3b`），讓穩定性的效果**肉眼可見**。

---

## 範例 1：氣泡排序 (Bubble Sort)

### 程式碼

```cpp
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;   // 提前結束
    }
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| 外迴圈 `i < n - 1` | 共需 $n-1$ 輪，每輪將最大值「浮」到尾端 |
| 內迴圈 `j < n - 1 - i` | 每輪已排好尾端 $i$ 個元素，不需再比較 |
| `arr[j] > arr[j + 1]` | 使用**嚴格大於**（`>`），相等時不交換 → 確保穩定性 |
| `bool swapped` + `if (!swapped) break` | 最佳化：若某輪沒有發生交換，表示已排序，提前結束 → 最佳 $O(n)$ |

### 穩定性說明

條件是 `arr[j] > arr[j + 1]`：只有「前者嚴格大於後者」才交換。  
若兩元素**相等**，不交換 → 相同值的相對順序不變 → **穩定**。

---

## 範例 2：挑選排序 (Selection Sort) — 不穩定示範

### 程式碼

```cpp
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `minIdx = i` | 假設當前位置已是最小值 |
| 內迴圈找最小 | 從 `i+1` 掃到末尾，找到最小值的索引 |
| `swap(arr[i], arr[minIdx])` | 將最小值交換到位置 `i` |

### 為何不穩定？

```
原始：[3a, 3b, 1c]
第 1 輪：找到最小 1c（在索引 2），與 arr[0]（3a）交換
→ [1c, 3b, 3a]
最終：3a 跑到 3b 後面，相對順序改變 → 不穩定
```

Selection Sort 的交換可能**跨越**相同鍵值的元素，導致不穩定。

---

## 範例 3：插入排序 (Insertion Sort)

### 程式碼

```cpp
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];   // 向右移動，騰出空位
            j--;
        }
        arr[j + 1] = key;          // 插入到正確位置
    }
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `int key = arr[i]` | 取出當前要插入的元素 |
| `while (j >= 0 && arr[j] > key)` | 從右往左掃已排序區域，將比 key 大的元素右移 |
| `arr[j + 1] = arr[j]` | 不用交換，直接右移（效率比 Bubble Sort 高） |
| `arr[j + 1] = key` | 找到正確位置後插入 |

### 複雜度分析

| 情境 | 說明 | 複雜度 |
|------|------|--------|
| 最佳（已排序） | while 迴圈從不執行 | $O(n)$ |
| 最壞（逆序） | 每個元素都要移動到最前面 | $O(n^2)$ |
| 適用情境 | **幾乎已排序** 的資料 | 接近 $O(n)$ |

### 穩定性

條件是 `arr[j] > key`（嚴格大於），相等時不移動 → **穩定**。

---

## 範例 4：合併排序 (Merge Sort)

### 整體架構

```
mergeSort(arr, left, right)
├── 分割：mid = left + (right - left) / 2
├── 遞迴左半：mergeSort(arr, left, mid)
├── 遞迴右半：mergeSort(arr, mid+1, right)
└── 合併：merge(arr, left, mid, right)
```

### 合併函式 `merge`

```cpp
#include <vector>
#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(arr + left, arr + left + n1);
    vector<int> R(arr + mid + 1, arr + mid + 1 + n2);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])       // <= 保證穩定性
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    // 填入剩餘元素
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);  // 遞迴排序左半部
    mergeSort(arr, mid + 1, right); // 遞迴排序右半部
    merge(arr, left, mid, right);
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    mergeSort(arr, 0, n - 1);

    cout << "排序後: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

| 程式碼 | 說明 |
|--------|------|
| `L[i] <= R[j]` | **小於等於**：相等時優先取左邊，保持原相對順序 → 穩定 |
| `vector<int> L(...)` | 額外複製子陣列，需要 $O(n)$ 額外空間 |
| 最後兩個 while | 將未用完的那半邊剩餘元素全部複製 |

### 複雜度

$$ T(n) = 2T(n/2) + O(n) \Rightarrow O(n \log n) $$

---

## 範例 5：快速排序 (Quick Sort)

### Partition 函式

```cpp
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // 選最後一個元素為基準值 (pivot)
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);   // 將 pivot 放到正確位置
    return i + 1;                  // 回傳 pivot 的最終索引
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `pivot = arr[high]` | 選最後一個元素為 pivot（最簡單但非最優） |
| `i = low - 1` | `i` 追蹤「小於等於 pivot 的元素」的尾端 |
| `arr[j] <= pivot` | 凡比 pivot 小或等於的，放到左邊 |
| 最後 `swap(arr[i+1], arr[high])` | 將 pivot 放回其最終排序位置 |

### 最壞情況

當陣列**已排序**（正序或逆序），每次 pivot 都選到最大/最小值，分割不均：
$$T(n) = T(n-1) + O(n) \Rightarrow O(n^2)$$

解法：使用**隨機選 pivot** 或 **三數取中法 (Median-of-Three)**。

---

## 練習題 1：Selection Sort 逐步追蹤

```cpp
for (int i = 0; i < n - 1; i++) {
    // 找最小值並交換
    cout << "第 " << i + 1 << " 輪：";
    printArr(arr, n);
}
```

讓每輪結束後印出陣列狀態，幫助視覺化理解排序過程。

---

## 練習題 2：Bubble Sort 計算 Swap 次數

```cpp
int bubbleSortCount(int arr[], int n) {
    int swapCount = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapCount++;
            }
    return swapCount;
}
```

- 逆序陣列 `[5,4,3,2,1]`：swap 次數 = $\frac{n(n-1)}{2} = 10$（最壞情況）  
- 已排序陣列 `[1,2,3,4,5]`：swap 次數 = 0（最佳情況）

---

## 學習筆記摘要

```
【Week 2 重點整理】

✅ 穩定性判斷方法
   條件使用嚴格大於 (>) → 相等不交換 → 穩定
   稀疏交換（Selection Sort 跨位置交換）→ 可能不穩定

✅ 各排序法適用情境
   資料幾乎已排序   → Insertion Sort（接近 O(n)）
   需穩定 + 大量資料 → Merge Sort（O(n log n)，但需 O(n) 空間）
   一般用途快速      → Quick Sort（平均最快，但最壞 O(n²)）
   記憶體受限        → Heap Sort（O(n log n)，O(1) 空間，不穩定）

✅ Merge Sort 關鍵
   合併時用 <= 而非 < ，才能保持穩定性
   需要 O(n) 額外空間，不能原地 (in-place) 合併

✅ Quick Sort 關鍵
   選 pivot 影響效能：已排序資料選末端 pivot → O(n²)
   實務建議：隨機 pivot 或 Median-of-Three

⚠️ 常見陷阱
   1. Selection Sort：swap 可能破壞穩定性，即使鍵值相等
   2. Merge Sort 的 merge 若用 < 而非 <=，會變成不穩定
   3. Quick Sort 遞迴深度最壞 O(n)，可能 Stack Overflow
```

---

> 現在試試看：修改 `quickSort`，改用**隨機選 pivot**（`rand() % (high - low + 1) + low`），  
> 觀察對已排序陣列的效能是否改善。
