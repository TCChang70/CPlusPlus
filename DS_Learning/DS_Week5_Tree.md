# 第 5 週：樹狀結構與二元樹 (Trees & Binary Trees)

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、什麼是樹？ (What is a Tree?)

樹是一種**非線性**的階層結構，每個節點可以有零個或多個子節點，但**只有一個父節點**（根節點除外）。

```
              [A]           ← 根節點 (Root)
             /   \
           [B]   [C]        ← 內部節點
          /   \     \
        [D]   [E]   [F]     ← 葉節點 (Leaf)
```

**關鍵術語：**

| 術語 | 英文 | 說明 |
|------|------|------|
| 根節點 | Root | 樹的起點，無父節點 |
| 葉節點 | Leaf | 無子節點的節點 |
| 分支度 | Degree | 一個節點的子節點數量 |
| 深度/層次 | Depth/Level | 根節點為第 0 層（或第 1 層） |
| 高度 | Height | 樹中最長路徑的邊數 |
| 子樹 | Subtree | 任一節點與其所有後裔構成的樹 |

---

## 二、二元樹 (Binary Tree)

**定義：** 每個節點**最多有 2 個子節點**（左子節點 Left、右子節點 Right）。

### 2.1 節點結構

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

### 2.2 特殊二元樹

**完滿二元樹 (Full Binary Tree)：** 每個節點恰好有 0 或 2 個子節點

**完整二元樹 (Complete Binary Tree)：** 除最後一層外每層填滿，最後一層靠左填

```
完整二元樹：          非完整：
      1                  1
    /   \              /   \
   2     3            2     3
  / \   /           /         \
 4   5 6           4            7
```

---

## 三、二元樹走訪 (Tree Traversal)

### 3.1 三種走訪順序

以根節點的「處理時機」來命名：

| 走訪名稱 | 順序 | 記憶方式 |
|---------|------|---------|
| 前序 Pre-order | **根** → 左 → 右 | 根在「前」 |
| 中序 In-order | 左 → **根** → 右 | 根在「中」 |
| 後序 Post-order | 左 → 右 → **根** | 根在「後」 |

**範例樹：**
```
       1
      / \
     2   3
    / \
   4   5
```

- 前序：`1 2 4 5 3`
- 中序：`4 2 5 1 3`
- 後序：`4 5 2 3 1`

### 3.2 程式碼實作（遞迴）

```cpp
#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 前序走訪：根 → 左 → 右
void preOrder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->data << " ";   // 處理根
    preOrder(root->left);        // 遞迴左
    preOrder(root->right);       // 遞迴右
}

// 中序走訪：左 → 根 → 右
void inOrder(TreeNode* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->data << " ";   // 處理根
    inOrder(root->right);
}

// 後序走訪：左 → 右 → 根
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";   // 處理根（最後）
}

int main() {
    // 建立範例樹
    TreeNode* root = new TreeNode(1);
    root->left  = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left  = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "前序: "; preOrder(root);  cout << endl;  // 1 2 4 5 3
    cout << "中序: "; inOrder(root);   cout << endl;  // 4 2 5 1 3
    cout << "後序: "; postOrder(root); cout << endl;  // 4 5 2 3 1

    return 0;
}
```

### 3.3 走訪與運算式的對應

```
運算式樹：  (A + B) * (C - D)

          [*]
         /   \
       [+]   [-]
       / \   / \
      A   B C   D

前序（前綴/波蘭式）：  * + A B - C D
中序（中綴/一般式）：  A + B * C - D  （需加括號）
後序（後綴/逆波蘭式）：A B + C D - *
```

---

## 四、堆積 (Heap)

### 4.1 概念說明

堆積是一種**完整二元樹**，並滿足堆積性質：
- **最大堆積 (Max-Heap)：** 每個節點的值 ≥ 子節點的值 → 根節點是最大值
- **最小堆積 (Min-Heap)：** 每個節點的值 ≤ 子節點的值 → 根節點是最小值

```
最大堆積：
         90
        /  \
       80   70
      / \  /
     50  60 65
```

### 4.2 陣列表示法（完整二元樹）

完整二元樹可以用陣列緊密存放：

```
索引：   1    2    3    4    5    6
值：    90   80   70   50   60   65

父節點索引 = i / 2
左子節點索引 = 2 * i
右子節點索引 = 2 * i + 1
```

### 4.3 Max-Heap 插入與調整

```cpp
#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
    vector<int> heap;

    // 上浮調整（插入後從底部往上調整）
    void siftUp(int idx) {
        while (idx > 1 && heap[idx] > heap[idx / 2]) {
            swap(heap[idx], heap[idx / 2]);
            idx /= 2;
        }
    }

    // 下沉調整（刪除根後從頂部往下調整）
    void siftDown(int idx) {
        int n = heap.size() - 1;
        while (2 * idx <= n) {
            int child = 2 * idx;
            if (child + 1 <= n && heap[child + 1] > heap[child])
                child++;
            if (heap[idx] >= heap[child]) break;
            swap(heap[idx], heap[child]);
            idx = child;
        }
    }

public:
    MaxHeap() { heap.push_back(0); }  // heap[0] 不使用，索引從 1 開始

    void insert(int val) {
        heap.push_back(val);
        siftUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.size() <= 1) return -1;
        int maxVal = heap[1];
        heap[1] = heap.back();
        heap.pop_back();
        if (heap.size() > 1) siftDown(1);
        return maxVal;
    }

    int getMax() { return heap.size() > 1 ? heap[1] : -1; }
};

int main() {
    MaxHeap h;
    h.insert(50); h.insert(80); h.insert(70);
    h.insert(90); h.insert(60);

    cout << "最大值: " << h.getMax() << endl;     // 90
    cout << "取出: "   << h.extractMax() << endl; // 90
    cout << "最大值: " << h.getMax() << endl;     // 80

    return 0;
}
```

---

## 五、二元搜尋樹 (Binary Search Tree, BST)

### 5.1 定義

對任意節點 $N$：
- 左子樹中所有節點的值 **< N** 的值
- 右子樹中所有節點的值 **> N** 的值

```
插入 5, 3, 7, 1, 4, 6, 8 後：

        5
       / \
      3   7
     / \ / \
    1  4 6  8
```

中序走訪 BST → 得到**排序後的結果**（1 3 4 5 6 7 8）

### 5.2 程式碼實作

```cpp
#include <iostream>
using namespace std;

struct BST_Node {
    int data;
    BST_Node* left;
    BST_Node* right;
    BST_Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 插入
BST_Node* insert(BST_Node* root, int val) {
    if (root == nullptr) return new BST_Node(val);
    if (val < root->data) root->left  = insert(root->left, val);
    if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// 搜尋
bool search(BST_Node* root, int val) {
    if (root == nullptr) return false;
    if (val == root->data) return true;
    if (val < root->data)  return search(root->left, val);
    return search(root->right, val);
}

// 中序走訪（輸出排序後結果）
void inOrder(BST_Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

int main() {
    BST_Node* root = nullptr;
    for (int val : {5, 3, 7, 1, 4, 6, 8})
        root = insert(root, val);

    cout << "中序（排序）: "; inOrder(root); cout << endl;  // 1 3 4 5 6 7 8
    cout << "搜尋 4: " << search(root, 4) << endl;         // 1 (true)
    cout << "搜尋 9: " << search(root, 9) << endl;         // 0 (false)

    return 0;
}
```

---

## 六、常見錯誤與注意事項

| 錯誤類型 | 說明 | 建議 |
|---------|------|------|
| 混淆前/中/後序 | 三種順序名稱易搞混 | 記住：名稱指的是「根」的處理時機 |
| BST 退化為鏈結串列 | 依序插入 1,2,3,4,5 → 全往右 | 實際應用使用自平衡 BST（AVL/紅黑樹） |
| Heap 索引從 0 開始計算錯誤 | 父子索引公式在 0-based 與 1-based 不同 | 1-based：父 = i/2，子 = 2i, 2i+1 |
| 樹節點未釋放 | 遞迴刪除整棵樹前需後序走訪 `delete` | 用後序走訪逐一 `delete` 節點 |

---

## 七、學習筆記摘要

```
本週關鍵概念：
┌──────────────────────────────────────────────────────┐
│ ✦ 三種走訪：前序(根左右)、中序(左根右)、後序(左右根)│
│ ✦ 中序走訪 BST 可得排序結果                         │
│ ✦ 完整二元樹可用陣列表示，父 = i/2，子 = 2i, 2i+1  │
│ ✦ Max-Heap：根是最大值，插入後 siftUp，刪除後 siftDown│
│ ✦ BST：左 < 根 < 右，搜尋效率 O(log n)（均勻時）    │
└──────────────────────────────────────────────────────┘
```

**現在試試看：**
> 手動追蹤依序插入 `{10, 5, 15, 3, 7}` 到 BST 的過程，畫出樹狀結構，再驗證中序走訪結果。
