// ============================================================
//  第 2 週：排序演算法與穩定性 — 範例 & 練習題
//  對應學習文件：DS_Week2_Sorting.md
//  編譯：g++ -g week2_sorting_practice.cpp -o week2_sorting_practice
// ============================================================
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ────────────────────────────────────────────────────────────
//  工具函式：印出陣列
// ────────────────────────────────────────────────────────────
void printArr(int arr[], int n, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ────────────────────────────────────────────────────────────
//  穩定性展示用：帶標籤的元素
// ────────────────────────────────────────────────────────────
struct LabeledVal {
    int val;
    char tag;   // 'a', 'b' 區分相同值的元素
};

void printLabeled(LabeledVal arr[], int n, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i].val << arr[i].tag;
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ============================================================
//  【範例 1】氣泡排序 (Bubble Sort) — 穩定排序
// ============================================================
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;   // 已完成排序，提前結束（最佳 O(n)）
    }
}

void example1_bubble() {
    cout << "=== 範例 1：氣泡排序 (Bubble Sort) ===" << endl;

    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "排序前");
    bubbleSort(arr, n);
    printArr(arr, n, "排序後");
    cout << "時間複雜度：O(n²)  穩定性：✅ 穩定" << endl << endl;
}

// ============================================================
//  【範例 2】挑選排序 (Selection Sort) — 不穩定排序
// ============================================================
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

void example2_selection() {
    cout << "=== 範例 2：挑選排序 (Selection Sort) — 不穩定示範 ===" << endl;

    // 用帶標籤元素展示不穩定性
    LabeledVal arr[] = {{3,'a'}, {3,'b'}, {1,'c'}};
    int n = 3;

    printLabeled(arr, n, "排序前");
    // 模擬 Selection Sort 的第一輪：找最小值(1c)與 arr[0](3a) 交換
    // 交換後：1c, 3b, 3a → 3a 跑到 3b 後面了！
    swap(arr[0], arr[2]);   // 模擬第一輪 swap
    printLabeled(arr, n, "第1輪後");
    cout << "→ 3a 跑到 3b 後面 ✗ 不穩定！" << endl;

    int arr2[] = {64, 25, 12, 22, 11};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printArr(arr2, n2, "\n整數排序前");
    selectionSort(arr2, n2);
    printArr(arr2, n2, "整數排序後");
    cout << "時間複雜度：O(n²)  穩定性：❌ 不穩定" << endl << endl;
}

// ============================================================
//  【範例 3】插入排序 (Insertion Sort) — 穩定排序
// ============================================================
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void example3_insertion() {
    cout << "=== 範例 3：插入排序 (Insertion Sort) ===" << endl;

    int arr[] = {5, 2, 4, 6, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "排序前");

    // 逐步顯示每輪結果
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        cout << "插入 " << key << " 後：";
        printArr(arr, n);
    }
    cout << "時間複雜度：最佳 O(n)（幾乎已排序時），最壞 O(n²)" << endl;
    cout << "穩定性：✅ 穩定" << endl << endl;
}

// ============================================================
//  【範例 4】合併排序 (Merge Sort) — 穩定排序，O(n log n)
// ============================================================
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(arr + left, arr + left + n1);
    vector<int> R(arr + mid + 1, arr + mid + 1 + n2);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])   // <= 保證穩定性
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void example4_merge() {
    cout << "=== 範例 4：合併排序 (Merge Sort) ===" << endl;

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "排序前");
    mergeSort(arr, 0, n - 1);
    printArr(arr, n, "排序後");
    cout << "時間複雜度：O(n log n)  空間：O(n)  穩定性：✅ 穩定" << endl << endl;
}

// ============================================================
//  【範例 5】快速排序 (Quick Sort) — 不穩定，平均 O(n log n)
// ============================================================
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // 選最後一個元素為基準
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void example5_quick() {
    cout << "=== 範例 5：快速排序 (Quick Sort) ===" << endl;

    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "排序前");
    quickSort(arr, 0, n - 1);
    printArr(arr, n, "排序後");
    cout << "時間複雜度：平均 O(n log n)，最壞 O(n²)（已排序時）" << endl;
    cout << "穩定性：❌ 不穩定" << endl << endl;
}

// ============================================================
//  ★ 練習題 1：逐步追蹤 Selection Sort
//  要求：修改 selectionSort，讓它每輪都印出狀態
// ============================================================
void practice1_selection_trace() {
    cout << "=== 練習題 1：Selection Sort 逐步追蹤 ===" << endl;

    int arr[] = {5, 3, 8, 1, 9, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "初始");

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);

        cout << "第 " << i + 1 << " 輪（最小值 " << arr[i] << " 放到位置 " << i << "）: ";
        printArr(arr, n);
    }
    cout << endl;
}

// ============================================================
//  ★ 練習題 2：實作 Bubble Sort 並計算 swap 次數
//  要求：完成 bubbleSortCount，回傳 swap 總次數
// ============================================================
int bubbleSortCount(int arr[], int n) {
    int swapCount = 0;

    // TODO：實作 Bubble Sort，每次交換時 swapCount++
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapCount++;
            }
        }
    }
    return swapCount;
}

void practice2_bubble_count() {
    cout << "=== 練習題 2：Bubble Sort — 計算 Swap 次數 ===" << endl;

    // 最壞情況：逆序排列
    int arr1[] = {5, 4, 3, 2, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int cnt1 = bubbleSortCount(arr1, n1);
    cout << "逆序 [5,4,3,2,1] → swap 次數 = " << cnt1
         << "（最壞：n*(n-1)/2 = " << n1*(n1-1)/2 << "）" << endl;

    // 最佳情況：已排序
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int cnt2 = bubbleSortCount(arr2, n2);
    cout << "已排序 [1,2,3,4,5] → swap 次數 = " << cnt2
         << "（最佳：0 次交換）" << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 3：自行實作 Insertion Sort（留空版）
//  要求：不看範例，自行填寫 myInsertionSort 的邏輯
// ============================================================
void myInsertionSort(int arr[], int n) {
    // TODO：實作插入排序
    // 提示：
    //   外層迴圈 i 從 1 到 n-1
    //   key = arr[i]
    //   內層往左搬移比 key 大的元素
    //   最後將 key 放入 arr[j+1]

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void practice3_insertion_impl() {
    cout << "=== 練習題 3：自行實作 Insertion Sort ===" << endl;

    int arr[] = {9, 1, 5, 3, 7, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n, "排序前");
    myInsertionSort(arr, n);
    printArr(arr, n, "排序後");
    cout << "預期：[1, 2, 3, 5, 7, 8, 9]" << endl << endl;
}

// ============================================================
//  ★ 練習題 4：比較三種排序的執行時間（大 N）
// ============================================================
#include <ctime>

void practice4_timing() {
    cout << "=== 練習題 4：排序演算法執行時間比較 ===" << endl;

    const int N = 10000;
    int base[N];
    srand(42);
    for (int i = 0; i < N; i++) base[i] = rand() % 100000;

    // Bubble Sort
    int arr1[N]; for (int i=0;i<N;i++) arr1[i]=base[i];
    clock_t t1 = clock();
    bubbleSort(arr1, N);
    double time1 = (double)(clock() - t1) / CLOCKS_PER_SEC * 1000;

    // Insertion Sort
    int arr2[N]; for (int i=0;i<N;i++) arr2[i]=base[i];
    clock_t t2 = clock();
    insertionSort(arr2, N);
    double time2 = (double)(clock() - t2) / CLOCKS_PER_SEC * 1000;

    // Merge Sort
    int arr3[N]; for (int i=0;i<N;i++) arr3[i]=base[i];
    clock_t t3 = clock();
    mergeSort(arr3, 0, N - 1);
    double time3 = (double)(clock() - t3) / CLOCKS_PER_SEC * 1000;

    // Quick Sort
    int arr4[N]; for (int i=0;i<N;i++) arr4[i]=base[i];
    clock_t t4 = clock();
    quickSort(arr4, 0, N - 1);
    double time4 = (double)(clock() - t4) / CLOCKS_PER_SEC * 1000;

    cout << "N = " << N << " 隨機資料：" << endl;
    cout << "  Bubble Sort    : " << time1 << " ms" << endl;
    cout << "  Insertion Sort : " << time2 << " ms" << endl;
    cout << "  Merge Sort     : " << time3 << " ms" << endl;
    cout << "  Quick Sort     : " << time4 << " ms" << endl;
    cout << "→ O(n²) 演算法比 O(n log n) 慢約 " 
         << (int)(time1 / (time3 + 0.001)) << " 倍" << endl;
    cout << endl;
}

// ============================================================
//  main
// ============================================================
int main() {
    example1_bubble();
    example2_selection();
    example3_insertion();
    example4_merge();
    example5_quick();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_selection_trace();
    practice2_bubble_count();
    practice3_insertion_impl();
    practice4_timing();

    return 0;
}
