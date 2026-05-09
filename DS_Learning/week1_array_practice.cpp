// ============================================================
//  第 1 週：陣列與記憶體配置 — 範例 & 練習題
//  對應學習文件：DS_Week1_Array_Memory.md
//  編譯：g++ -g week1_array_practice.cpp -o week1_array_practice
// ============================================================
#include <iostream>
using namespace std;

// ============================================================
//  【範例 1】一維陣列位址計算
//  公式：Address(A[i]) = A + i * d
// ============================================================
void example1_address() {
    cout << "=== 範例 1：一維陣列位址 ===" << endl;

    int arr[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        cout << "arr[" << i << "] = " << arr[i]
             << "\t位址 = " << &arr[i] << endl;
    }

    // 驗證相鄰元素位址差 = sizeof(int) = 4 bytes
    long long diff = (long long)&arr[1] - (long long)&arr[0];
    cout << "相鄰元素位址差 = " << diff << " bytes (應為 " << sizeof(int) << ")" << endl;
    cout << endl;
}

// ============================================================
//  【範例 2】二維陣列 Row-major 走訪（C++ 預設）
//  公式：Address(A[i][j]) = A + (i * n + j) * d
// ============================================================
void example2_2d_array() {
    cout << "=== 範例 2：二維陣列 Row-major ===" << endl;

    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    // n = 欄數 = 3, d = sizeof(int) = 4

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "A[" << i << "][" << j << "] = " << A[i][j]
                 << "\t位址 = " << &A[i][j] << endl;
        }
    }
    cout << endl;
}

// ============================================================
//  【範例 3】Binary Search 遞迴版
//  時間複雜度：O(log n)，前提：陣列已排序
// ============================================================
// 回傳目標值的索引，找不到回傳 -1
int binarySearch(int arr[], int left, int right, int target) {
    if (left > right)           // 基底條件：搜尋範圍已空
        return -1;

    int mid = left + (right - left) / 2;   // 避免大數相加溢位

    if (arr[mid] == target)     // 找到
        return mid;
    else if (arr[mid] > target) // 目標在左半
        return binarySearch(arr, left, mid - 1, target);
    else                        // 目標在右半
        return binarySearch(arr, mid + 1, right, target);
}

// ============================================================
//  【範例 4】Binary Search 迭代版（不使用遞迴）
// ============================================================
int binarySearchIter(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void example3_binary_search() {
    cout << "=== 範例 3 & 4：Binary Search ===" << endl;

    int sorted[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(sorted) / sizeof(sorted[0]);

    int targets[] = {23, 1, 91};
    for (int t : targets) {
        int idx = binarySearch(sorted, 0, n - 1, t);
        cout << "遞迴搜尋 " << t << " → ";
        if (idx != -1) cout << "找到，索引 = " << idx << endl;
        else           cout << "找不到" << endl;
    }

    cout << "迭代搜尋 38 → 索引 = " << binarySearchIter(sorted, n, 38) << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 1：計算位址（填寫答案）
//  題目：int B[3][4] 基底位址 = 200，sizeof(int) = 4
//        Row-major：Address(B[i][j]) = 200 + (i*4 + j) * 4
//        請計算 B[2][3] 的位址
// ============================================================
void practice1_address_calc() {
    cout << "=== 練習題 1：位址計算 ===" << endl;

    // 驗算
    int B[3][4] = {};
    long long base = (long long)&B[0][0];

    cout << "B[0][0] 位址 = " << base << endl;
    cout << "B[2][3] 實際位址 = " << (long long)&B[2][3] << endl;

    // TODO：依公式手動計算並驗證
    int d = sizeof(int);   // = 4
    int n_cols = 4;
    long long calc = base + (2 * n_cols + 3) * d;
    cout << "公式計算 B[2][3] = " << calc
         << (calc == (long long)&B[2][3] ? " ✓ 正確" : " ✗ 錯誤") << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 2：實作「計算比較次數」的 Binary Search
//  要求：在 binarySearchCount 中，每次比較時將 count++
//        執行後印出搜尋所需的比較次數
// ============================================================
int binarySearchCount(int arr[], int n, int target, int& count) {
    int left = 0, right = n - 1;
    count = 0;

    // TODO：在迴圈內加入 count++ 並完成搜尋邏輯
    // 提示：架構與 binarySearchIter 相同，只多一個 count++
    while (left <= right) {
        count++;                               // 每次進迴圈 = 一次比較
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void practice2_count_comparisons() {
    cout << "=== 練習題 2：計算比較次數 ===" << endl;

    int arr[1024];
    for (int i = 0; i < 1024; i++) arr[i] = i * 2;   // 0,2,4,...,2046

    int count;
    int targets[] = {100, 512, 2045, 9999};
    for (int t : targets) {
        int idx = binarySearchCount(arr, 1024, t, count);
        cout << "搜尋 " << t << " → ";
        if (idx != -1) cout << "找到(索引=" << idx << ")";
        else           cout << "找不到";
        cout << "，比較次數 = " << count
             << "（log2(1024) = 10）" << endl;
    }
    cout << endl;
}

// ============================================================
//  ★ 練習題 3：Column-major 位址計算（挑戰）
//  公式：Address(A[i][j]) = A + (j * m + i) * d
//        m = 列數（rows）
// ============================================================
void practice3_column_major() {
    cout << "=== 練習題 3：Column-major 位址 ===" << endl;

    // C++ 本身是 Row-major，這裡模擬 Column-major 的索引邏輯
    // 二維陣列 int C[3][4]，m=3（列），n=4（欄），d=4
    int m = 3, d = 4;
    long long base = 1000;   // 假設基底位址 = 1000

    // TODO：計算 C[1][2] 的 Column-major 位址
    // 答案：1000 + (2 * 3 + 1) * 4 = 1000 + 28 = 1028
    int i = 1, j = 2;
    long long addr = base + (j * m + i) * d;
    cout << "C[" << i << "][" << j << "] Column-major 位址 = "
         << addr << "（預期 1028）" << endl;

    // 對比 Row-major：1000 + (1 * 4 + 2) * 4 = 1024
    int n_cols = 4;
    long long addr_row = base + (i * n_cols + j) * d;
    cout << "C[" << i << "][" << j << "] Row-major    位址 = "
         << addr_row << "（預期 1024）" << endl;
    cout << "→ 兩種儲存方式，相同的 [i][j] 對應到不同的物理位址！" << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 4：自行實作 Linear Search 並比較效率
//  要求：實作 linearSearch，並比較與 Binary Search 的比較次數
// ============================================================
int linearSearch(int arr[], int n, int target, int& count) {
    count = 0;
    for (int i = 0; i < n; i++) {
        count++;
        if (arr[i] == target) return i;
    }
    return -1;
}

void practice4_compare_search() {
    cout << "=== 練習題 4：Linear vs Binary Search 效率比較 ===" << endl;

    const int N = 1000;
    int arr[N];
    for (int i = 0; i < N; i++) arr[i] = i;   // 0,1,2,...,999

    int testVal = 887;
    int cLinear, cBinary;

    linearSearch(arr, N, testVal, cLinear);
    binarySearchCount(arr, N, testVal, cBinary);

    cout << "搜尋值 " << testVal << "（N = " << N << "）" << endl;
    cout << "Linear Search  比較次數：" << cLinear << endl;
    cout << "Binary Search  比較次數：" << cBinary << endl;
    cout << "效率差距：約 " << cLinear / (float)cBinary << " 倍" << endl;
    cout << endl;
}

// ============================================================
//  main：執行所有範例與練習題
// ============================================================
int main() {
    example1_address();
    example2_2d_array();
    example3_binary_search();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_address_calc();
    practice2_count_comparisons();
    practice3_column_major();
    practice4_compare_search();

    return 0;
}
