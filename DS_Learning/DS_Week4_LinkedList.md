# 第 4 週：指標與鏈結串列 (Pointers & Linked Lists)

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、從陣列的限制說起

陣列的問題：
- **固定大小**：宣告後大小無法改變
- **插入/刪除代價高**：需要搬移大量元素（$O(n)$）

鏈結串列的解法：
- **動態配置**：需要時才向記憶體申請空間
- **插入/刪除快**：只需調整指標，不需搬移資料（$O(1)$，已知位置時）

---

## 二、指標基礎複習

```cpp
int x = 42;
int* ptr = &x;    // ptr 存放 x 的記憶體位址

cout << x;        // 42      — 直接存取值
cout << &x;       // 0x...   — x 的位址
cout << ptr;      // 0x...   — ptr 存的位址（同 &x）
cout << *ptr;     // 42      — 解參考，取 ptr 指向的值
```

**動態配置記憶體：**
```cpp
int* p = new int(99);   // 在 heap 上配置一個 int，初值 99
cout << *p;             // 99
delete p;               // 釋放！不釋放 = 記憶體洩漏 (Memory Leak)
p = nullptr;            // 釋放後設 nullptr，防止懸空指標
```

---

## 三、單向鏈結串列 (Singly Linked List)

### 3.1 節點結構

```cpp
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};
#endif

struct Node {
    int data;       // 資料欄位
    Node* next;     // 指標欄位，指向下一個節點

    Node(int val) : data(val), next(nullptr) {}
};
```

```
[data | next] → [data | next] → [data | nullptr]
   Node 1          Node 2          Node 3
```

### 3.2 建立與走訪

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// 走訪串列
void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next) cout << " → ";
        curr = curr->next;
    }
    cout << " → NULL" << endl;
}

int main() {
    // 手動建立：1 → 2 → 3 → NULL
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    printList(head);   // 1 → 2 → 3 → NULL
    return 0;
}
```

### 3.3 在頭部插入節點

```cpp
// 在串列開頭插入值 val，回傳新的 head
Node* insertFront(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;   // 新節點指向舊 head
    return newNode;         // 新節點成為新 head
}

// 使用：
head = insertFront(head, 0);   // 0 → 1 → 2 → 3
```

### 3.4 在尾部插入節點

```cpp
Node* insertBack(Node* head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) return newNode;   // 空串列

    Node* curr = head;
    while (curr->next != nullptr)          // 走到最後一個節點
        curr = curr->next;
    curr->next = newNode;
    return head;
}
```

### 3.5 刪除節點（刪除值為 target 的第一個節點）

```cpp
Node* deleteNode(Node* head, int target) {
    if (head == nullptr) return nullptr;

    // 若刪除的是頭節點
    if (head->data == target) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // 找到 target 的前一個節點
    Node* prev = head;
    while (prev->next != nullptr && prev->next->data != target)
        prev = prev->next;

    if (prev->next != nullptr) {         // 找到了
        Node* temp = prev->next;
        prev->next = temp->next;         // 跳過要刪的節點
        delete temp;
    }
    return head;
}
```

**指標調整視覺化：**
```
刪除前：[1] → [2] → [3] → NULL
刪除 2：prev = [1]，temp = [2]
        prev->next = temp->next = [3]
刪除後：[1] → [3] → NULL，delete [2]
```

---

## 四、加入開頭空節點 (Dummy Head Node)

### 4.1 問題

沒有 Dummy Head 時，每次插入/刪除都要**特判頭節點是否為空**：
```cpp
if (head == nullptr) { ... }   // 每個函式都要加這行
```

### 4.2 解法：Dummy Head（哨兵節點）

```
dummy → [1] → [2] → [3] → NULL
  ↑
永遠存在，data 不使用
```

```cpp
struct LinkedList {
    Node* dummy;   // 永遠存在的空頭節點

    LinkedList() {
        dummy = new Node(0);   // 建立 dummy，data 值無意義
    }

    // 插入到串列最前面（dummy 後面）
    void insertFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = dummy->next;
        dummy->next = newNode;
        // 不需要特判空串列！
    }

    // 刪除值為 target 的節點
    void deleteVal(int target) {
        Node* prev = dummy;   // 從 dummy 開始掃
        while (prev->next != nullptr) {
            if (prev->next->data == target) {
                Node* temp = prev->next;
                prev->next = temp->next;
                delete temp;
                return;
            }
            prev = prev->next;
        }
    }

    void printList() {
        Node* curr = dummy->next;
        while (curr != nullptr) {
            cout << curr->data << " → ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;
    list.insertFront(3);
    list.insertFront(2);
    list.insertFront(1);
    list.printList();        // 1 → 2 → 3 → NULL

    list.deleteVal(2);
    list.printList();        // 1 → 3 → NULL
    return 0;
}
```

---

## 五、雙向鏈結串列 (Doubly Linked List)

每個節點有 **prev** 和 **next** 兩個指標：

```
NULL ← [1] ⇄ [2] ⇄ [3] → NULL
```

```cpp
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
```

**插入 newNode 在 curr 之後：**
```cpp
void insertAfter(DNode* curr, int val) {
    DNode* newNode = new DNode(val);
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next) curr->next->prev = newNode;
    curr->next = newNode;
}
```

**優點：** 可以雙向走訪，刪除節點時不需要找前驅節點  
**代價：** 每個節點多一個指標（多佔記憶體）

---

## 六、環狀鏈結串列 (Circular Linked List)

最後一個節點的 `next` 指回 `head`（而非 `nullptr`）：

```
[1] → [2] → [3]
 ↑             |
 └─────────────┘
```

```cpp
// 走訪環狀串列（需用計數或判斷回到 head 才停止）
void printCircular(Node* head) {
    if (head == nullptr) return;
    Node* curr = head;
    do {
        cout << curr->data << " → ";
        curr = curr->next;
    } while (curr != head);   // 回到 head 就停止
    cout << "(back to head)" << endl;
}
```

---

## 七、常見錯誤與注意事項

| 錯誤類型 | 說明 | 建議 |
|---------|------|------|
| 記憶體洩漏 | `new` 後忘記 `delete` | 每個 `new` 對應一個 `delete` |
| 懸空指標 (Dangling Pointer) | `delete` 後仍使用該指標 | `delete` 後立即設 `nullptr` |
| 走訪環狀串列無窮迴圈 | 用 `!= nullptr` 走訪環狀 | 環狀串列用 `do-while` 判斷回到 head |
| 刪除時指標順序錯誤 | 先斷開 next 再 delete，導致找不到後繼 | 先暫存再刪除 |
| 雙向串列忘記更新 prev | 單向更新導致反向走訪錯誤 | 插入/刪除時確認 prev 與 next 雙方 |

---

## 八、學習筆記摘要

```
本週關鍵概念：
┌──────────────────────────────────────────────────────┐
│ ✦ 指標存放位址，* 解參考取值，& 取位址              │
│ ✦ 鏈結串列 = Node (data + next 指標) 的鏈接         │
│ ✦ Dummy Head：簡化插入/刪除，省去空串列特判          │
│ ✦ 雙向串列：prev + next，刪除不需找前驅             │
│ ✦ 環狀串列：最後節點指回 head，走訪用 do-while      │
│ ✦ 每個 new 必須對應 delete，否則記憶體洩漏           │
└──────────────────────────────────────────────────────┘
```

**現在試試看：**
> 在 `LinkedList` 類別中新增 `insertBack(int val)` 方法（插入到尾端），以及 `size()` 方法（回傳節點數量），並測試看看。
