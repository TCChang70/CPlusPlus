// ============================================================
//  第 5 週：樹狀結構與二元樹 — 範例 & 練習題
//  對應學習文件：DS_Week5_Tree.md
//  編譯：g++ -g week5_tree_practice.cpp -o week5_tree_practice
// ============================================================
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  二元樹節點
// ============================================================
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 釋放整棵樹
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ============================================================
//  【範例 1】三種走訪：前序、中序、後序（遞迴版）
//
//  使用的樹結構：
//           A(1)
//          /    \
//       B(2)    C(3)
//       / \       \
//    D(4) E(5)   F(6)
// ============================================================
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

// 建立範例樹 (數字版)
TreeNode* buildExampleTree() {
    /*
             1
           /   \
          2     3
         / \     \
        4   5     6
    */
    TreeNode* root = new TreeNode(1);
    root->left  = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left  = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    return root;
}

void example1_traversal() {
    cout << "=== 範例 1：三種走訪 ===" << endl;
    cout << "樹結構：1 為根，左子樹 2(4,5)，右子樹 3(null,6)" << endl;

    TreeNode* root = buildExampleTree();
    cout << "前序 Preorder  (根左右): "; preorder(root);  cout << endl;
    cout << "中序 Inorder   (左根右): "; inorder(root);   cout << endl;
    cout << "後序 Postorder (左右根): "; postorder(root); cout << endl;
    cout << "→ 中序結果是排序後的順序（BST 特性）" << endl;

    freeTree(root);
    cout << endl;
}

// ============================================================
//  【範例 2】層次走訪 (Level-order) — 使用 Queue
// ============================================================
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    cout << endl;
}

void example2_level_order() {
    cout << "=== 範例 2：層次走訪 (Level-order) ===" << endl;

    TreeNode* root = buildExampleTree();
    cout << "層次走訪：";
    levelOrder(root);   // 1 2 3 4 5 6
    cout << "→ 按層次由上而下，由左至右輸出" << endl;

    freeTree(root);
    cout << endl;
}

// ============================================================
//  【範例 3】二元搜尋樹 (BST)
//  特性：左子樹所有值 < 根 < 右子樹所有值
// ============================================================
TreeNode* bstInsert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->data)
        root->left  = bstInsert(root->left, val);
    else if (val > root->data)
        root->right = bstInsert(root->right, val);
    // val == root->data：不插入重複值
    return root;
}

TreeNode* bstSearch(TreeNode* root, int val) {
    if (!root || root->data == val) return root;
    if (val < root->data) return bstSearch(root->left, val);
    else                  return bstSearch(root->right, val);
}

// 印出樹的結構（旋轉 90° 的樹狀圖）
void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    cout << prefix << (isLeft ? "└── " : "┌── ") << root->data << endl;
    printTree(root->left,  prefix + (isLeft ? "    " : "│   "), true);
}

void example3_bst() {
    cout << "=== 範例 3：二元搜尋樹 (BST) ===" << endl;

    int vals[] = {5, 3, 7, 1, 4, 6, 8};
    TreeNode* bst = nullptr;
    for (int v : vals) bst = bstInsert(bst, v);

    cout << "插入順序：5, 3, 7, 1, 4, 6, 8" << endl;
    cout << "樹結構（旋轉 90°，左下為 root）：" << endl;
    printTree(bst);

    cout << "中序走訪（應為升序）: ";
    inorder(bst); cout << endl;

    int target = 4;
    cout << "搜尋 " << target << " → "
         << (bstSearch(bst, target) ? "找到" : "找不到") << endl;

    freeTree(bst);
    cout << endl;
}

// ============================================================
//  【範例 4】Heap（最大堆積）— 陣列實作
//  父節點索引：i/2，左子：2i，右子：2i+1（索引從 1 開始）
// ============================================================
struct MaxHeap {
    vector<int> h;   // h[0] 不使用，從 h[1] 開始

    MaxHeap() { h.push_back(0); }   // 佔位

    int size() { return (int)h.size() - 1; }

    void insert(int val) {
        h.push_back(val);       // 放到最後
        // 上浮 (Sift-up)
        int i = size();
        while (i > 1 && h[i] > h[i / 2]) {
            swap(h[i], h[i / 2]);
            i /= 2;
        }
    }

    int extractMax() {
        if (size() == 0) return -1;
        int maxVal = h[1];
        h[1] = h.back();
        h.pop_back();
        // 下沉 (Sift-down)
        int i = 1, n = size();
        while (true) {
            int largest = i;
            if (2*i   <= n && h[2*i]   > h[largest]) largest = 2*i;
            if (2*i+1 <= n && h[2*i+1] > h[largest]) largest = 2*i+1;
            if (largest == i) break;
            swap(h[i], h[largest]);
            i = largest;
        }
        return maxVal;
    }

    void print() {
        cout << "Heap 陣列: [";
        for (int i = 1; i <= size(); i++) {
            cout << h[i];
            if (i < size()) cout << ", ";
        }
        cout << "]" << endl;
    }
};

void example4_heap() {
    cout << "=== 範例 4：Max Heap ===" << endl;

    MaxHeap heap;
    for (int v : {3, 1, 6, 5, 2, 4}) heap.insert(v);
    heap.print();

    cout << "索引規則：父節點 = i/2，左子 = 2i，右子 = 2i+1" << endl;
    cout << "ExtractMax: " << heap.extractMax() << " (最大值)" << endl;
    heap.print();
    cout << "ExtractMax: " << heap.extractMax() << endl;
    heap.print();

    cout << endl;
}

// ============================================================
//  ★ 練習題 1：計算樹的高度
// ============================================================
int treeHeight(TreeNode* root) {
    // TODO：遞迴計算樹的高度
    // 高度 = max(左子樹高度, 右子樹高度) + 1，空樹高度 = 0
    if (!root) return 0;
    return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}

void practice1_height() {
    cout << "=== 練習題 1：計算樹的高度 ===" << endl;

    TreeNode* root = buildExampleTree();
    cout << "範例樹高度 = " << treeHeight(root)
         << " (預期 3)" << endl;

    TreeNode* single = new TreeNode(1);
    cout << "單節點樹高度 = " << treeHeight(single)
         << " (預期 1)" << endl;

    cout << "空樹高度 = " << treeHeight(nullptr)
         << " (預期 0)" << endl;

    freeTree(root);
    freeTree(single);
    cout << endl;
}

// ============================================================
//  ★ 練習題 2：計算葉節點數量
// ============================================================
int countLeaves(TreeNode* root) {
    // TODO：遞迴計算葉節點（左右子節點都是 nullptr）的數量
    if (!root) return 0;
    if (!root->left && !root->right) return 1;   // 葉節點
    return countLeaves(root->left) + countLeaves(root->right);
}

void practice2_leaves() {
    cout << "=== 練習題 2：計算葉節點數 ===" << endl;

    TreeNode* root = buildExampleTree();
    cout << "範例樹葉節點數 = " << countLeaves(root)
         << " (預期 3：節點 4, 5, 6)" << endl;
    freeTree(root);
    cout << endl;
}

// ============================================================
//  ★ 練習題 3：根據前序+中序重建二元樹
//  前序：根, 左, 右 → 第一個元素是根
//  中序：左, 根, 右 → 根把中序分成左右子樹
// ============================================================
TreeNode* buildFromPreIn(vector<int>& pre, int preStart, int preEnd,
                         vector<int>& in,  int inStart,  int inEnd) {
    if (preStart > preEnd) return nullptr;

    int rootVal = pre[preStart];
    TreeNode* root = new TreeNode(rootVal);

    // 在中序中找根的位置
    int rootIdx = inStart;
    while (in[rootIdx] != rootVal) rootIdx++;

    int leftSize = rootIdx - inStart;

    root->left = buildFromPreIn(pre, preStart + 1, preStart + leftSize,
                                in,  inStart,      rootIdx - 1);
    root->right = buildFromPreIn(pre, preStart + leftSize + 1, preEnd,
                                 in,  rootIdx + 1,              inEnd);
    return root;
}

void practice3_rebuild() {
    cout << "=== 練習題 3：根據前序 + 中序重建樹 ===" << endl;

    // 前序：1, 2, 4, 5, 3, 6 → 根是 1
    // 中序：4, 2, 5, 1, 3, 6 → 1 分隔左右
    vector<int> pre = {1, 2, 4, 5, 3, 6};
    vector<int> in  = {4, 2, 5, 1, 3, 6};

    cout << "前序：";
    for (int v : pre) cout << v << " ";
    cout << endl;
    cout << "中序：";
    for (int v : in) cout << v << " ";
    cout << endl;

    TreeNode* root = buildFromPreIn(pre, 0, pre.size()-1,
                                    in,  0, in.size()-1);
    cout << "重建後前序驗證："; preorder(root); cout << endl;
    cout << "重建後中序驗證："; inorder(root);  cout << endl;
    cout << "重建後樹結構：" << endl;
    printTree(root);

    freeTree(root);
    cout << endl;
}

// ============================================================
//  ★ 練習題 4：判斷是否為 BST（中序應為嚴格遞增）
// ============================================================
bool isBSTHelper(TreeNode* root, long long minVal, long long maxVal) {
    // TODO：使用範圍限制法驗證 BST
    if (!root) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isBSTHelper(root->left,  minVal,       root->data)
        && isBSTHelper(root->right, root->data,   maxVal);
}

bool isBST(TreeNode* root) {
    return isBSTHelper(root, LLONG_MIN, LLONG_MAX);
}

void practice4_is_bst() {
    cout << "=== 練習題 4：判斷是否為 BST ===" << endl;

    // 合法 BST：5 → (3, 7) → (1,4,6,8)
    TreeNode* bst = nullptr;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) bst = bstInsert(bst, v);
    cout << "合法 BST 插入 {5,3,7,1,4,6,8} → "
         << (isBST(bst) ? "是 BST ✓" : "不是 BST ✗") << endl;

    // 非法 BST：手動建立一棵違反 BST 的樹
    TreeNode* notBst = new TreeNode(5);
    notBst->left  = new TreeNode(3);
    notBst->right = new TreeNode(7);
    notBst->left->right = new TreeNode(6);   // 6 在 5 的左子樹，但 6 > 5 → 違規
    cout << "非法 BST（左子樹含 6 > 5）  → "
         << (isBST(notBst) ? "是 BST ✓" : "不是 BST ✗") << endl;

    freeTree(bst);
    freeTree(notBst);
    cout << endl;
}

// ============================================================
//  main
// ============================================================
int main() {
    example1_traversal();
    example2_level_order();
    example3_bst();
    example4_heap();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_height();
    practice2_leaves();
    practice3_rebuild();
    practice4_is_bst();

    return 0;
}
