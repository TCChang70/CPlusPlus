// ============================================================
//  第 4 週：指標與鏈結串列 — 範例 & 練習題
//  對應學習文件：DS_Week4_LinkedList.md
//  編譯：g++ -g week4_linkedlist_practice.cpp -o week4_linkedlist_practice
// ============================================================
#include <iostream>
using namespace std;

// ============================================================
//  節點結構：單向鏈結串列
// ============================================================
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ────────────────────────────────────────────────────────────
//  工具：走訪並印出串列
// ────────────────────────────────────────────────────────────
void printList(Node* head, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " → ";
        curr = curr->next;
    }
    cout << " → NULL" << endl;
}

// 釋放整個串列的記憶體
void freeList(Node*& head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ============================================================
//  【範例 1】建立、走訪、搜尋
// ============================================================
// 在尾端新增節點
Node* append(Node* head, int val) {
    Node* newNode = new Node(val);
    if (!head) return newNode;
    Node* curr = head;
    while (curr->next) curr = curr->next;
    curr->next = newNode;
    return head;
}

// 搜尋：O(n)
Node* search(Node* head, int target) {
    Node* curr = head;
    while (curr) {
        if (curr->data == target) return curr;
        curr = curr->next;
    }
    return nullptr;
}

void example1_basic() {
    cout << "=== 範例 1：建立、走訪、搜尋 ===" << endl;

    Node* head = nullptr;
    for (int v : {10, 20, 30, 40, 50})
        head = append(head, v);

    printList(head);

    int target = 30;
    Node* found = search(head, target);
    cout << "搜尋 " << target << " → "
         << (found ? "找到" : "找不到") << endl;

    freeList(head);
    cout << endl;
}

// ============================================================
//  【範例 2】在頭部、中間、尾部插入節點
// ============================================================
// 在頭部插入
Node* insertFront(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    return newNode;   // 新 head
}

// 在 pos 位置之後插入（pos 從 0 開始）
Node* insertAfter(Node* head, int pos, int val) {
    Node* curr = head;
    int idx = 0;
    while (curr && idx < pos) {
        curr = curr->next;
        idx++;
    }
    if (!curr) { cout << "位置超出範圍！" << endl; return head; }
    Node* newNode = new Node(val);
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

void example2_insert() {
    cout << "=== 範例 2：插入節點 ===" << endl;

    Node* head = nullptr;
    head = append(head, 10);
    head = append(head, 30);
    head = append(head, 50);
    printList(head, "初始");

    head = insertFront(head, 5);
    printList(head, "頭部插入 5");

    head = insertAfter(head, 2, 20);  // 在 pos=2（值30）之後插入 20
    printList(head, "pos=2 後插入 20");

    head = append(head, 60);
    printList(head, "尾部插入 60");

    freeList(head);
    cout << endl;
}

// ============================================================
//  【範例 3】刪除節點（頭部、中間、特定值）
// ============================================================
Node* deleteFirst(Node* head) {
    if (!head) return nullptr;
    Node* tmp = head;
    head = head->next;
    delete tmp;
    return head;
}

Node* deleteByVal(Node* head, int val) {
    if (!head) return nullptr;

    // 刪除的是 head
    if (head->data == val) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return head;
    }

    // 找到值為 val 的節點的前一個節點
    Node* prev = head;
    while (prev->next && prev->next->data != val)
        prev = prev->next;

    if (!prev->next) { cout << val << " 不存在！" << endl; return head; }

    Node* toDelete = prev->next;
    prev->next = toDelete->next;   // 跨越被刪節點
    delete toDelete;
    return head;
}

void example3_delete() {
    cout << "=== 範例 3：刪除節點 ===" << endl;

    Node* head = nullptr;
    for (int v : {10, 20, 30, 40, 50}) head = append(head, v);
    printList(head, "初始");

    head = deleteFirst(head);
    printList(head, "刪除頭部 10");

    head = deleteByVal(head, 30);
    printList(head, "刪除值 30");

    head = deleteByVal(head, 99);   // 找不到
    printList(head, "刪除值 99");

    freeList(head);
    cout << endl;
}

// ============================================================
//  【範例 4】雙向鏈結串列 (Doubly Linked List)
// ============================================================
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

struct DoublyList {
    DNode* head;
    DNode* tail;
    DoublyList() : head(nullptr), tail(nullptr) {}

    void append(int val) {
        DNode* newNode = new DNode(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // 刪除最後一個節點：O(1)（不用從頭走訪！）
    void deleteLast() {
        if (!tail) return;
        if (tail == head) {        // 只剩一個節點
            delete tail;
            head = tail = nullptr;
        } else {
            DNode* toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete toDelete;
        }
    }

    void printForward() {
        cout << "正向: ";
        DNode* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " ↔ ";
            curr = curr->next;
        }
        cout << " → NULL" << endl;
    }

    void printBackward() {
        cout << "反向: ";
        DNode* curr = tail;
        while (curr) {
            cout << curr->data;
            if (curr->prev) cout << " ↔ ";
            curr = curr->prev;
        }
        cout << " → NULL" << endl;
    }
};

void example4_doubly() {
    cout << "=== 範例 4：雙向鏈結串列 ===" << endl;

    DoublyList dl;
    for (int v : {1, 2, 3, 4, 5}) dl.append(v);
    dl.printForward();
    dl.printBackward();

    dl.deleteLast();          // 不需從頭走訪
    dl.printForward();
    cout << "→ 刪除最後節點，使用 tail 指標，直接 O(1) 完成" << endl;
    cout << endl;
}

// ============================================================
//  【範例 5】帶 Dummy Head Node 的單向鏈結串列
//  優點：插入/刪除時不需特判空串列
// ============================================================
Node* createDummyList() {
    return new Node(-1);   // dummy head，data 無意義
}

void dummyAppend(Node* dummy, int val) {
    Node* curr = dummy;
    while (curr->next) curr = curr->next;
    curr->next = new Node(val);
}

void dummyInsertFront(Node* dummy, int val) {
    Node* newNode = new Node(val);
    newNode->next = dummy->next;   // 永遠都有 dummy，不需特判
    dummy->next = newNode;
}

void dummyDeleteVal(Node* dummy, int val) {
    Node* prev = dummy;   // 從 dummy 開始，prev 永遠不為 nullptr
    while (prev->next && prev->next->data != val)
        prev = prev->next;
    if (!prev->next) return;
    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
}

void printDummyList(Node* dummy, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    printList(dummy->next);   // 跳過 dummy head
}

void example5_dummy() {
    cout << "=== 範例 5：Dummy Head Node ===" << endl;

    Node* dummy = createDummyList();
    printDummyList(dummy, "初始（空）");

    dummyInsertFront(dummy, 30);
    dummyInsertFront(dummy, 20);
    dummyInsertFront(dummy, 10);
    printDummyList(dummy, "插入 10, 20, 30 後");

    dummyDeleteVal(dummy, 20);
    printDummyList(dummy, "刪除 20 後");

    freeList(dummy);   // 含 dummy head 本身
    cout << endl;
}

// ============================================================
//  ★ 練習題 1：計算串列長度（實作）
// ============================================================
int listLength(Node* head) {
    // TODO：走訪串列，計算節點數目
    int count = 0;
    Node* curr = head;
    while (curr) { count++; curr = curr->next; }
    return count;
}

void practice1_length() {
    cout << "=== 練習題 1：計算串列長度 ===" << endl;

    Node* head = nullptr;
    cout << "空串列長度 = " << listLength(head) << " (預期 0)" << endl;

    for (int v : {5, 10, 15, 20}) head = append(head, v);
    printList(head);
    cout << "長度 = " << listLength(head) << " (預期 4)" << endl;

    freeList(head);
    cout << endl;
}

// ============================================================
//  ★ 練習題 2：反轉單向鏈結串列（O(n)）
//  三指標法：prev, curr, next
// ============================================================
Node* reverseList(Node* head) {
    // TODO：用三個指標 prev/curr/nextNode 反轉每個節點的 next 指向
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* nextNode = curr->next;  // 先儲存下一個
        curr->next = prev;            // 反轉指向
        prev = curr;                  // prev 前進
        curr = nextNode;              // curr 前進
    }
    return prev;   // 新的 head
}

void practice2_reverse() {
    cout << "=== 練習題 2：反轉鏈結串列 ===" << endl;

    Node* head = nullptr;
    for (int v : {1, 2, 3, 4, 5}) head = append(head, v);
    printList(head, "原始");

    head = reverseList(head);
    printList(head, "反轉後");
    cout << "預期：5 → 4 → 3 → 2 → 1 → NULL" << endl;

    freeList(head);
    cout << endl;
}

// ============================================================
//  ★ 練習題 3：找到第 k 個節點（從尾端起）
//  技巧：快慢指標（Fast & Slow Pointer）
// ============================================================
Node* kthFromEnd(Node* head, int k) {
    // TODO：fast 先走 k 步，再 fast 與 slow 同步走，fast 到底時 slow 即為答案
    Node* fast = head;
    Node* slow = head;

    // fast 先走 k 步
    for (int i = 0; i < k; i++) {
        if (!fast) return nullptr;   // k 超過串列長度
        fast = fast->next;
    }
    // 同步走直到 fast 到底
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

void practice3_kth_from_end() {
    cout << "=== 練習題 3：找第 k 個節點（從尾端）===" << endl;

    Node* head = nullptr;
    for (int v : {10, 20, 30, 40, 50}) head = append(head, v);
    printList(head);

    for (int k : {1, 2, 3, 5, 6}) {
        Node* res = kthFromEnd(head, k);
        cout << "倒數第 " << k << " 個 → ";
        if (res) cout << res->data;
        else     cout << "（超出範圍）";
        cout << endl;
    }

    freeList(head);
    cout << endl;
}

// ============================================================
//  ★ 練習題 4：偵測環狀串列（Floyd 算法）
//  快慢指標：slow 走 1 步，fast 走 2 步
//  若有環，兩者必然相遇
// ============================================================
bool hasCycle(Node* head) {
    // TODO：使用 slow/fast 兩個指標偵測環
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;  // 相遇 = 有環
    }
    return false;
}

void practice4_cycle() {
    cout << "=== 練習題 4：偵測環狀串列 ===" << endl;

    // 建立一般串列
    Node* head = nullptr;
    for (int v : {1, 2, 3, 4, 5}) head = append(head, v);
    cout << "一般串列 → " << (hasCycle(head) ? "有環 ✗" : "無環 ✓") << endl;

    // 人工造環：尾節點指回第 2 個節點（值=20）
    Node* tail = head;
    Node* loopBack = head->next;   // 指回 node(2)
    while (tail->next) tail = tail->next;
    tail->next = loopBack;         // 形成環（不能用 freeList！）

    cout << "造環後    → " << (hasCycle(head) ? "有環 ✓" : "無環 ✗") << endl;

    // 手動斷環以釋放記憶體
    tail->next = nullptr;
    freeList(head);
    cout << endl;
}

// ============================================================
//  main
// ============================================================
int main() {
    example1_basic();
    example2_insert();
    example3_delete();
    example4_doubly();
    example5_dummy();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_length();
    practice2_reverse();
    practice3_kth_from_end();
    practice4_cycle();

    return 0;
}
