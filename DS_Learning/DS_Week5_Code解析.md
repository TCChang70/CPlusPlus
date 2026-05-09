# 第 5 週 程式碼解析：樹狀結構與二元樹

> 對應練習檔：`week5_tree_practice.cpp`  
> 對應學習文件：[DS_Week5_Tree.md](DS_Week5_Tree.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔涵蓋二元樹的核心操作與四種進階結構：

| 編號 | 函式 | 主題 |
|------|------|------|
| 範例 1 | `example1_traversal()` | 前序/中序/後序遞迴走訪 |
| 範例 2 | `example2_level_order()` | 層次走訪（BFS，使用 Queue） |
| 範例 3 | `example3_bst()` | 二元搜尋樹 BST 插入與搜尋 |
| 範例 4 | `example4_heap()` | 最大堆積 Max Heap（陣列實作） |
| 練習 1 | `practice1_height()` | 計算樹的高度 |
| 練習 2 | `practice2_leaves()` | 計算葉節點數量 |
| 練習 3 | `practice3_rebuild()` | 根據前序 + 中序重建二元樹 |
| 練習 4 | `isBST()` | 判斷是否為合法 BST |

---

## 核心節點結構

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

---

## 範例樹結構

本週使用的範例樹：

```
         1
       /   \
      2     3
     / \     \
    4   5     6
```

- 前序 (Preorder)：`1 2 4 5 3 6`
- 中序 (Inorder)：`4 2 5 1 3 6`
- 後序 (Postorder)：`4 5 2 6 3 1`
- 層次 (Level-order)：`1 2 3 4 5 6`

---

## 範例 1：三種深度優先走訪（遞迴版）

### 程式碼

```cpp
void preorder(TreeNode* root) {   // 根 → 左 → 右
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {    // 左 → 根 → 右
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(TreeNode* root) {  // 左 → 右 → 根
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
```

### 逐行解析

| 走訪 | 輸出時機 | 用途 |
|------|---------|------|
| 前序 Preorder | 進入節點**立即**輸出 | 複製樹、前綴運算式 |
| 中序 Inorder | 左子樹完成後輸出 | BST 排序輸出、中綴轉換 |
| 後序 Postorder | 左右子樹都完成後輸出 | 釋放記憶體（`freeTree`）、後綴運算式 |

### 共通模式

所有遞迴走訪都有相同的**基底條件 (base case)**：`if (!root) return`，  
確保遇到 `nullptr`（空節點）時停止遞迴，不會發生空指標存取。

---

## 範例 2：層次走訪 (Level-order / BFS)

### 程式碼

```cpp
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);            // ① 根節點入隊

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();             // ② 取出隊頭
        cout << curr->data << " ";
        if (curr->left)  q.push(curr->left);   // ③ 左子加入隊列
        if (curr->right) q.push(curr->right);  // ③ 右子加入隊列
    }
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `queue<TreeNode*> q` | 使用 STL 的 `queue`，FIFO 特性確保按層次輸出 |
| `q.front()` + `q.pop()` | 取出並移除隊頭（兩個動作分開，`queue` 的 `pop` 不回傳值） |
| 先加 `left`，後加 `right` | 確保同層節點由左至右輸出 |

### 為什麼用 Queue 而不是 Stack？

- **Queue（FIFO）**：先入先出 → 先加入的左子先處理 → **廣度優先 (BFS)** = 層次走訪
- **Stack（LIFO）**：後入先出 → 深度優先 (DFS) = 前序走訪的迭代版

---

## 範例 3：二元搜尋樹 (BST)

### BST 特性

```
對每個節點 N：
  N.left 子樹所有值  <  N.data
  N.right 子樹所有值 >  N.data
```

### 插入 `bstInsert`（遞迴）

```cpp
TreeNode* bstInsert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);   // 找到插入位置
    if (val < root->data)
        root->left  = bstInsert(root->left, val);   // 往左遞迴
    else if (val > root->data)
        root->right = bstInsert(root->right, val);  // 往右遞迴
    // val == root->data：忽略重複值
    return root;
}
```

### 搜尋 `bstSearch`（遞迴）

```cpp
TreeNode* bstSearch(TreeNode* root, int val) {
    if (!root || root->data == val) return root;
    if (val < root->data) return bstSearch(root->left, val);
    else                  return bstSearch(root->right, val);
}
```

時間複雜度：平均 $O(\log n)$（樹平衡時），最壞 $O(n)$（退化成鏈結串列）。

### BST 中序走訪 = 升序輸出

```
插入順序：5, 3, 7, 1, 4, 6, 8
中序走訪：1, 3, 4, 5, 6, 7, 8  ← 自動排序！
```

---

## 範例 4：最大堆積 (Max Heap) — 陣列實作

### 索引關係（從索引 1 開始）

$$\text{父節點} = i / 2 \qquad \text{左子} = 2i \qquad \text{右子} = 2i + 1$$

### 插入 + 上浮 (Sift-up)

```cpp
void insert(int val) {
    h.push_back(val);       // 放到最後一個位置
    int i = size();
    while (i > 1 && h[i] > h[i / 2]) {   // 若比父節點大
        swap(h[i], h[i / 2]);              // 與父節點交換
        i /= 2;                            // 往上移動
    }
}
```

### 取出最大值 + 下沉 (Sift-down)

```cpp
int extractMax() {
    int maxVal = h[1];        // 根節點是最大值
    h[1] = h.back();          // 將最後一個節點移到根
    h.pop_back();
    int i = 1;
    while (true) {
        int largest = i;
        if (2*i   <= n && h[2*i]   > h[largest]) largest = 2*i;
        if (2*i+1 <= n && h[2*i+1] > h[largest]) largest = 2*i+1;
        if (largest == i) break;
        swap(h[i], h[largest]);
        i = largest;           // 往下沉
    }
    return maxVal;
}
```

| 操作 | 複雜度 |
|------|--------|
| `insert` | $O(\log n)$（上浮最多 $\log n$ 層） |
| `extractMax` | $O(\log n)$（下沉最多 $\log n$ 層） |
| 建堆（所有元素） | $O(n)$（Floyd 建堆算法） |

---

## 練習題 1：計算樹的高度（遞迴）

```cpp
int treeHeight(TreeNode* root) {
    if (!root) return 0;   // 空樹高度 = 0
    return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}
```

**遞迴思維：** 樹的高度 = max(左子樹高度, 右子樹高度) + 1（加上根節點本身）。

---

## 練習題 2：計算葉節點數量

```cpp
int countLeaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;   // 葉節點判斷
    return countLeaves(root->left) + countLeaves(root->right);
}
```

**葉節點 (leaf node)** = 左右子節點均為 `nullptr` 的節點。

---

## 練習題 3：根據前序 + 中序重建二元樹

### 核心邏輯

```
前序第一個元素 = 根節點
在中序中找到根節點位置 → 分出左右子樹的中序範圍
左子樹大小 = rootIdx - inStart
遞迴重建左右子樹
```

```cpp
TreeNode* buildFromPreIn(vector<int>& pre, int preStart, int preEnd,
                         vector<int>& in,  int inStart,  int inEnd) {
    if (preStart > preEnd) return nullptr;

    int rootVal = pre[preStart];                  // 前序第一個是根
    TreeNode* root = new TreeNode(rootVal);

    int rootIdx = inStart;
    while (in[rootIdx] != rootVal) rootIdx++;     // 在中序找根的位置
    int leftSize = rootIdx - inStart;

    root->left = buildFromPreIn(pre, preStart + 1, preStart + leftSize,
                                in,  inStart, rootIdx - 1);
    root->right = buildFromPreIn(pre, preStart + leftSize + 1, preEnd,
                                 in,  rootIdx + 1, inEnd);
    return root;
}
```

---

## 練習題 4：驗證是否為合法 BST（範圍限制法）

```cpp
bool isBSTHelper(TreeNode* root, long long minVal, long long maxVal) {
    if (!root) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isBSTHelper(root->left,  minVal,       root->data)
        && isBSTHelper(root->right, root->data,   maxVal);
}
```

**範圍限制法：** 每個節點必須在其允許的值範圍 `(minVal, maxVal)` 內，  
遞迴往下傳遞收窄的範圍，比中序走訪法更直觀。

---

## 學習筆記摘要

```
【Week 5 重點整理】

✅ 三種 DFS 走訪
   前序（根左右）：輸出在遞迴前
   中序（左根右）：輸出在兩次遞迴中間 → BST 得升序序列
   後序（左右根）：輸出在遞迴後 → 適合釋放記憶體

✅ BFS 層次走訪
   必用 Queue（FIFO）
   每次取隊頭，將其子節點加入隊尾

✅ BST 特性與操作
   插入/搜尋平均 O(log n)，最壞（退化）O(n)
   中序走訪 = 升序排列

✅ Max Heap 索引規則（從 1 開始）
   父節點 = i/2
   左子 = 2i，右子 = 2i+1
   insert 上浮，extractMax 下沉，各 O(log n)

✅ 重建二元樹
   必須同時有前序 + 中序（或後序 + 中序）才能唯一確定樹形
   只有前序或只有後序，無法唯一確定

⚠️ 常見陷阱
   1. 所有走訪基底條件：if (!root) return，遺漏會導致 null 指標存取
   2. BST 插入允許重複值時，需選左或右一個方向一致
   3. Heap 陣列從索引 1 開始，h[0] 為佔位符，不能存資料
   4. extractMax 後需先移最後元素到根再下沉，順序不能錯
```

---

> 現在試試看：在 `example3_bst` 中，嘗試按**已排序順序**插入 `1, 2, 3, 4, 5, 6, 7`，  
> 觀察樹形，解釋為什麼搜尋效率退化為 $O(n)$，並思考 AVL 樹如何解決此問題。
