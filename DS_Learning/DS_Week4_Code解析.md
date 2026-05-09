# 第 4 週 程式碼解析：指標與鏈結串列

> 對應練習檔：`week4_linkedlist_practice.cpp`  
> 對應學習文件：[DS_Week4_LinkedList.md](DS_Week4_LinkedList.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔從靜態陣列進入動態指標世界，涵蓋：

| 編號 | 函式 | 主題 |
|------|------|------|
| 範例 1 | `example1_basic()` | 建立、走訪、搜尋 |
| 範例 2 | `example2_insert()` | 在頭部/中間/尾部插入節點 |
| 範例 3 | `example3_delete()` | 刪除節點（頭部、特定值） |
| 範例 4 | `example4_doubly()` | 雙向鏈結串列 (Doubly Linked List) |
| 範例 5 | `example5_dummy()` | 帶 Dummy Head Node 的單向串列 |
| 練習 1 | `practice1_length()` | 計算串列長度 |
| 練習 2 | `practice2_reverse()` | 反轉串列（三指標法） |
| 練習 3 | `practice3_kth_from_end()` | 找倒數第 k 個節點（快慢指標） |
| 練習 4 | `practice4_cycle()` | 偵測環狀串列（Floyd 算法） |

---

## 核心節點結構

### 單向節點 `Node`

```cpp
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};
```

| 成員 | 說明 |
|------|------|
| `data` | 節點儲存的資料值 |
| `next` | 指向下一個節點的指標，尾節點為 `nullptr` |

### 雙向節點 `DNode`

```cpp
struct DNode {
    int data;
    DNode* prev;   // 指向前一個節點
    DNode* next;   // 指向後一個節點
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
```

---

## 範例 1：建立、走訪、搜尋

### 尾端新增 `append`

```cpp
Node* append(Node* head, int val) {
    Node* newNode = new Node(val);     // 動態配置新節點
    if (!head) return newNode;         // 空串列直接回傳新節點
    Node* curr = head;
    while (curr->next) curr = curr->next;  // 走到最後一個節點
    curr->next = newNode;
    return head;
}
```

| 程式碼 | 說明 |
|--------|------|
| `new Node(val)` | 在 Heap（堆積）上動態配置記憶體，需手動 `delete` |
| `while (curr->next)` | `next != nullptr` 才繼續，停在最後一個節點 |
| 回傳 `head` | head 指標本身不變，仍指向首節點 |

時間複雜度：$O(n)$（需走訪到尾端）。

### 搜尋 `search`

```cpp
Node* search(Node* head, int target) {
    Node* curr = head;
    while (curr) {
        if (curr->data == target) return curr;
        curr = curr->next;
    }
    return nullptr;
}
```

時間複雜度：$O(n)$（最壞需走遍整個串列）。

### 記憶體釋放 `freeList`

```cpp
void freeList(Node*& head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;        // 釋放舊 head
    }
}
```

> `Node*&` 是**指標的參考 (reference to pointer)**，函式內修改 `head` 會反映到呼叫端，  
> 避免呼叫後 `head` 仍指向已釋放的記憶體（懸空指標 dangling pointer）。

---

## 範例 2：插入節點

### 頭部插入 `insertFront` — $O(1)$

```cpp
Node* insertFront(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;   // 新節點指向原 head
    return newNode;         // 新節點成為新 head
}
```

```
插入前：head → [10] → [30] → [50] → NULL
插入 5：newNode.next = head（[10]）
新 head = newNode
插入後：[5] → [10] → [30] → [50] → NULL
```

### 中間插入 `insertAfter` — $O(n)$

```cpp
Node* insertAfter(Node* head, int pos, int val) {
    Node* curr = head;
    int idx = 0;
    while (curr && idx < pos) { curr = curr->next; idx++; }
    if (!curr) { /* 超出範圍 */ return head; }

    Node* newNode = new Node(val);
    newNode->next = curr->next;   // ① 新節點指向 curr 的下一個
    curr->next = newNode;          // ② curr 指向新節點
    return head;
}
```

> **順序不能顛倒**：必須先做 ①，再做 ②。若先做 ② 會遺失 `curr->next` 的位址。

---

## 範例 3：刪除節點

### 刪除頭部 `deleteFirst` — $O(1)$

```cpp
Node* deleteFirst(Node* head) {
    if (!head) return nullptr;
    Node* tmp = head;
    head = head->next;   // head 移到第二個節點
    delete tmp;          // 釋放原 head
    return head;
}
```

### 刪除特定值 `deleteByVal` — $O(n)$

```cpp
Node* prev = head;
while (prev->next && prev->next->data != val)
    prev = prev->next;

Node* toDelete = prev->next;
prev->next = toDelete->next;   // 跨越被刪節點
delete toDelete;
```

關鍵：需要找到**目標節點的前一個節點** `prev`，才能修改 `prev->next`。

---

## 範例 4：雙向鏈結串列

### 刪除尾節點 — $O(1)$（優勢所在）

```cpp
void deleteLast() {
    DNode* toDelete = tail;
    tail = tail->prev;       // 使用 prev 指標直接定位倒數第二個
    tail->next = nullptr;
    delete toDelete;
}
```

對比單向串列：刪除尾節點需 $O(n)$（從頭走到倒數第二個）。  
雙向串列透過 `tail->prev` 直接定位，達到 $O(1)$。

### 雙向串列 vs 單向串列

| 操作 | 單向 | 雙向 |
|------|------|------|
| 尾端插入（有 tail 指標） | $O(1)$ | $O(1)$ |
| 刪除最後節點 | $O(n)$ | $O(1)$ |
| 反向走訪 | ❌ 不支援 | ✅ 支援 |
| 記憶體用量 | $O(n)$ | $O(2n)$（多存 prev） |

---

## 範例 5：Dummy Head Node（開頭空節點）

```cpp
Node* createDummyList() {
    return new Node(-1);   // data 無意義，僅作佔位符
}

void dummyInsertFront(Node* dummy, int val) {
    Node* newNode = new Node(val);
    newNode->next = dummy->next;
    dummy->next = newNode;   // 永遠有 dummy，不需特判空串列
}
```

**優點：** 頭部插入/刪除不需特判「串列是否為空」，程式碼更簡潔。  
**缺點：** 多一個無用的 dummy 節點佔記憶體。

---

## 練習題 2：反轉串列（三指標法）

```cpp
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* nextNode = curr->next;  // ① 儲存下一個（避免斷鏈後找不到）
        curr->next = prev;            // ② 反轉指向
        prev = curr;                  // ③ prev 前進
        curr = nextNode;              // ④ curr 前進
    }
    return prev;   // 最終 prev 指向新 head（原尾節點）
}
```

### 步驟示意

```
原始：NULL ← [1] → [2] → [3] → NULL
               ↑
             prev=NULL, curr=1

步驟1：next=2, 1.next=NULL, prev=1, curr=2
步驟2：next=3, 2.next=1,   prev=2, curr=3
步驟3：next=NULL, 3.next=2, prev=3, curr=NULL
結束：prev=3 即為新 head

結果：NULL ← [1] ← [2] ← [3]（反轉完成）
```

時間複雜度：$O(n)$，空間複雜度：$O(1)$

---

## 練習題 3：快慢指標找倒數第 k 個節點

```cpp
Node* kthFromEnd(Node* head, int k) {
    Node* fast = head;
    Node* slow = head;

    for (int i = 0; i < k; i++) {    // fast 先走 k 步
        if (!fast) return nullptr;
        fast = fast->next;
    }
    while (fast) {                    // fast 與 slow 同步走
        fast = fast->next;
        slow = slow->next;
    }
    return slow;   // fast 到底時，slow 正好在倒數第 k 個
}
```

**原理：** fast 比 slow 超前 k 步，當 fast 到達 NULL，slow 與 NULL 相差 k 步，即倒數第 k 個。

---

## 練習題 4：Floyd 環偵測算法（龜兔賽跑）

```cpp
bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;         // 走 1 步
        fast = fast->next->next;   // 走 2 步
        if (slow == fast) return true;   // 相遇 → 有環
    }
    return false;
}
```

**原理：** 若存在環，fast 比 slow 每輪多走 1 步，兩者距離縮短 1，最終必然相遇。

---

## 學習筆記摘要

```
【Week 4 重點整理】

✅ 基本操作複雜度
   頭部插入/刪除：O(1)
   尾部/中間操作：O(n)（需走訪）
   雙向串列刪除尾端：O(1)（有 tail 指標）

✅ 插入節點順序
   必須先讓新節點指向目標後繼節點（①），
   再讓前驅指向新節點（②）
   順序顛倒 → 遺失後繼節點位址

✅ 刪除節點
   需找目標節點的前一個節點 prev
   prev->next = toDelete->next（跨越）
   最後 delete toDelete 釋放記憶體

✅ Dummy Head 技巧
   讓插入/刪除邏輯統一，不需特判空串列

✅ 重要指標技巧
   三指標反轉：prev/curr/next，O(n) O(1)
   快慢指標：找倒數第k個、偵測環
   Floyd 算法：slow走1步，fast走2步，相遇=有環

⚠️ 常見陷阱
   1. 插入/刪除後忘記 delete → 記憶體洩漏 (memory leak)
   2. 操作後 head 改變，需回傳新 head
   3. 造環後不能用 freeList（無限迴圈），需先斷環
   4. freeList 用 Node*& 確保呼叫端的指標也被清為 nullptr
```

---

> 現在試試看：修改 `reverseList`，改用**遞迴版本**實作，  
> 思考遞迴版的空間複雜度為何是 $O(n)$ 而非 $O(1)$？
