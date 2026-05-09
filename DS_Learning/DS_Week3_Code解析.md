# 第 3 週 程式碼解析：堆疊與佇列及其應用

> 對應練習檔：`week3_stack_queue_practice.cpp`  
> 對應學習文件：[DS_Week3_Stack_Queue.md](DS_Week3_Stack_Queue.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔實作兩種基礎資料結構，並附上三個經典應用：

| 編號 | 函式 | 主題 |
|------|------|------|
| 範例 1 | `example1_stack()` | 陣列實作 Stack（LIFO） |
| 範例 2 | `example2_bracket()` | Stack 應用：括號匹配 |
| 範例 3 | `example3_circular_queue()` | 環狀佇列 Circular Queue（FIFO） |
| 範例 4 | `example4_maze()` | Stack 應用：老鼠走迷宮（DFS 回溯） |
| 練習 1 | `practice1_stack_ops()` | Stack 操作序列模擬 |
| 練習 2 | `practice2_queue_trace()` | 環狀佇列狀態追蹤 |
| 練習 3 | `StackQueue` | 用兩個 Stack 模擬 Queue |

---

## 核心結構 1：Stack（陣列實作）

### 資料成員

```cpp
const int MAX = 100;

struct Stack {
    int data[MAX];
    int top;        // 指向目前頂端的索引，初始值 -1（空堆疊）
    Stack() : top(-1) {}
    ...
};
```

| 操作 | 程式碼 | 說明 |
|------|--------|------|
| `isEmpty()` | `return top == -1` | 頂端索引為 -1 → 空 |
| `isFull()` | `return top == MAX - 1` | 頂端到達陣列上限 |
| `push(val)` | `data[++top] = val` | 先加再存（前置遞增） |
| `pop()` | `return data[top--]` | 先取再減（後置遞減） |
| `peek()` | `return data[top]` | 讀取頂端，不移除 |

### LIFO（後進先出）示意

```
Push(1) → [1]
Push(2) → [1, 2]
Push(3) → [1, 2, 3]  ← top
Pop()   → 取出 3，top 往下
Push(4) → [1, 2, 4]  ← top
```

### 常見陷阱

- `push` 用**前置遞增** `++top`，確保先移動指標再存值
- `pop` 用**後置遞減** `top--`，確保先取值再移動指標
- 操作前必須檢查 `isEmpty()` / `isFull()`，否則發生**下溢 (underflow)** 或**上溢 (overflow)**

---

## 範例 2：Stack 應用 — 括號匹配

### 演算法邏輯

```cpp
bool checkBrackets(const string& expr) {
    Stack s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);                          // 左括號：push
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.isEmpty() || !isMatching(s.pop(), c))
                return false;                   // 右括號：pop 並比對
        }
    }
    return s.isEmpty();   // 全部匹配 → Stack 應為空
}
```

### 逐步分析

| 輸入 | 過程 | 結果 |
|------|------|------|
| `"(())"` | push(, push(, pop-), pop-) → Stack 空 | ✅ 合法 |
| `"{[()]}"` | 依序 push/pop 全部匹配 | ✅ 合法 |
| `"([)]"` | `(` push, `[` push, `)` pop `[` → 不匹配 | ❌ 不合法 |
| `"((("` | push 3 次，結束時 Stack 不空 | ❌ 不合法 |

### 關鍵設計

`s.isEmpty() || !isMatching(s.pop(), c)` — 使用**短路求值 (short-circuit evaluation)**：  
先檢查空堆疊，避免對空堆疊呼叫 `pop()`。

---

## 核心結構 2：環狀佇列 (Circular Queue)

### 資料成員

```cpp
const int QMAX = 6;   // 陣列大小，有效容量 = QMAX - 1 = 5

struct CircularQueue {
    int data[QMAX];
    int front, rear;  // front：出隊端，rear：入隊端，初始均為 0
    ...
};
```

### 關鍵公式：模運算折繞

```cpp
bool isEmpty() { return front == rear; }
bool isFull()  { return (rear + 1) % QMAX == front; }

bool addQ(int val) {
    data[rear] = val;
    rear = (rear + 1) % QMAX;   // 折繞：5 → 0
    return true;
}

int deleteQ() {
    int val = data[front];
    front = (front + 1) % QMAX; // 折繞
    return val;
}
```

### 空/滿判斷原理

| 狀態 | 判斷式 |
|------|--------|
| 空 (empty) | `front == rear` |
| 滿 (full) | `(rear + 1) % QMAX == front` |

**為何有效容量 = `QMAX - 1`？**  
若佇列放滿所有 `QMAX` 格，則 `front == rear`，與「空」的條件相同，**無法區分**。  
因此刻意留一格空著，犧牲一格空間換取簡單的判斷邏輯。

### 折繞示意（QMAX = 6）

```
初始：front=0, rear=0
AddQ: front=0, rear=1 → 2 → 3 → 4 → 5
再 AddQ：rear = (5+1)%6 = 0  ← 折繞回頭
DeleteQ：front = (0+1)%6 = 1
```

---

## 範例 4：老鼠走迷宮（Stack + DFS 回溯）

### 演算法架構

```
solveMaze():
  建立空 Stack（路徑）
  push 起點 (0,0)
  while (Stack 非空):
    curr = peek() 查看當前位置
    if curr == 終點 → 成功，印出路徑
    找一個未走過的鄰居 nb:
      if 找到 → push nb，繼續
      if 找不到 → pop()，回溯 (Backtracking)
```

### 核心程式碼

```cpp
bool moved = false;
for (int d = 0; d < 4; d++) {
    int nr = curr.r + dr[d];
    int nc = curr.c + dc[d];
    if (/* 合法位置 */ && maze[nr][nc] == 0 && !visited[nr][nc]) {
        visited[nr][nc] = true;
        path.push({nr, nc});
        moved = true;
        break;
    }
}
if (!moved) path.pop();   // 死路 → 回溯
```

| 程式碼 | 說明 |
|--------|------|
| `dr[], dc[]` | 四個方向的偏移量：下、右、上、左 |
| `visited[][]` | 避免走回已走過的格子（防止無限迴圈） |
| `path.pop()` | 遇到死路，退回上一個位置（回溯） |

### 與 DFS 的關係

迷宮解法就是**深先搜尋 (DFS, Depth-First Search)** 的具體應用：  
Stack 模擬遞迴的 Call Stack，`peek()` 取當前節點，`pop()` 完成回溯。

---

## 練習題 3：用兩個 Stack 模擬 Queue

```cpp
struct StackQueue {
    Stack s1, s2;

    void enqueue(int val) {
        s1.push(val);           // 所有新元素進 s1
    }

    int dequeue() {
        if (s2.isEmpty()) {
            while (!s1.isEmpty())
                s2.push(s1.pop()); // 將 s1 全部「倒入」s2，順序反轉
        }
        return s2.pop();        // s2 頂端 = 最早進入的元素
    }
};
```

### 原理說明

```
Enqueue 3, 2, 1：
  s1 = [3, 2, 1]  (頂端是 1)
  s2 = []

Dequeue（第一次）：
  s2 空 → 將 s1 全部倒入 s2：
  s2 = [1, 2, 3]  (頂端是 3)
  pop s2 → 取出 3（最早進入的）✓

Dequeue（第二次）：
  s2 非空 → 直接 pop s2 → 取出 2 ✓
```

時間複雜度：enqueue $O(1)$，dequeue **均攤** $O(1)$（每個元素只被倒入一次）。

---

## 學習筆記摘要

```
【Week 3 重點整理】

✅ Stack 操作
   push：++top 先移後存
   pop ：取值後 top--
   peek：只看不動 top

✅ 環狀佇列
   關鍵：% QMAX 折繞
   空：front == rear
   滿：(rear+1) % QMAX == front
   有效容量 = QMAX - 1（犧牲一格區分空/滿）

✅ 括號匹配
   左括號 → push
   右括號 → pop + 比對
   結束後 Stack 空 → 合法

✅ 迷宮 DFS 回溯
   peek 看當前位置（不 pop）
   找到可走路徑 → push
   死路 → pop 回溯

✅ 兩個 Stack 模擬 Queue
   s1 接收新元素，s2 輸出元素
   s2 空時才將 s1 全部倒入 s2
   均攤 O(1) dequeue

⚠️ 常見陷阱
   1. pop 前必須確認非空，否則下溢
   2. 環狀佇列有效容量比陣列大小少 1
   3. 迷宮中必須用 visited 陣列，否則無限迴圈
```

---

> 現在試試看：修改迷宮 `maze` 陣列，設計一個有**多條路徑**的迷宮，  
> 觀察 DFS 是否只找到其中一條路（而非最短路徑）。想找最短路徑應使用什麼算法？
