# 第 3 週：堆疊與佇列及其應用 (Stack & Queue)

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、什麼是受限線性結構？

陣列允許從任意位置存取資料，但堆疊與佇列刻意**限制存取點**，讓特定順序的問題變得更好處理。

| 結構 | 存入 | 取出 | 特性 |
|------|------|------|------|
| 堆疊 Stack | 頂端 (Top) | 頂端 (Top) | LIFO — 後進先出 |
| 佇列 Queue | 尾端 (Rear) | 前端 (Front) | FIFO — 先進先出 |

---

## 二、堆疊 (Stack)

### 2.1 概念說明

「就像一疊盤子：最後放上去的盤子，是第一個被拿走的。」

```
Push(A)  → [A]
Push(B)  → [A, B]      ← B 在頂端
Push(C)  → [A, B, C]   ← C 在頂端
Pop()    → 取出 C，剩 [A, B]
Pop()    → 取出 B，剩 [A]
```

**真實應用：**
- 函式呼叫堆疊（程式的 Call Stack）— 儲存每次呼叫的返回位址
- 瀏覽器的「上一頁」功能
- 撤銷（Undo）功能
- 運算式求值（括號匹配、後序表示法）

### 2.2 陣列實作

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

struct Stack {
    int data[MAX_SIZE];
    int top;              // 指向頂端元素的索引，初始為 -1

    Stack() : top(-1) {}  // 建構子：初始化為空

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX_SIZE - 1; }

    // Push：推入元素
    void push(int val) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        data[++top] = val;
    }

    // Pop：取出頂端元素
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return data[top--];
    }

    // Peek：查看頂端但不取出
    int peek() {
        if (isEmpty()) return -1;
        return data[top];
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "頂端: " << s.peek() << endl;      // 30
    cout << "取出: " << s.pop() << endl;        // 30
    cout << "取出: " << s.pop() << endl;        // 20
    cout << "頂端: " << s.peek() << endl;       // 10

    return 0;
}
```

### 2.3 應用：括號匹配

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool checkBrackets(const string& expr) {
    Stack s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);                          // 左括號：推入
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.isEmpty() || !isMatching(s.peek(), c))
                return false;                   // 不匹配
            s.pop();
        }
    }
    return s.isEmpty();                         // 全部配對完才算成功
}

int main() {
    cout << checkBrackets("{[()]}")   << endl;  // 1 (true)
    cout << checkBrackets("{[(]}")    << endl;  // 0 (false)
    cout << checkBrackets("((())")    << endl;  // 0 (false)
    return 0;
}
```

---

## 三、佇列 (Queue)

### 3.1 概念說明

「就像排隊買票：先到先服務，最先加入的人最先離開。」

```
AddQ(A) → [A]
AddQ(B) → [A, B]
AddQ(C) → [A, B, C]
DeleteQ → 取出 A，剩 [B, C]
DeleteQ → 取出 B，剩 [C]
```

**真實應用：**
- 作業系統的 CPU 排程
- 印表機工作佇列
- 廣度優先搜尋（BFS）

### 3.2 陣列實作（線性佇列）

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 5;

struct Queue {
    int data[MAX_SIZE];
    int front, rear;

    Queue() : front(0), rear(0) {}  // front == rear 表示空佇列

    bool isEmpty() { return front == rear; }
    bool isFull()  { return rear == MAX_SIZE; }

    void addQ(int val) {
        if (isFull()) { cout << "Queue Full!" << endl; return; }
        data[rear++] = val;
    }

    int deleteQ() {
        if (isEmpty()) { cout << "Queue Empty!" << endl; return -1; }
        return data[front++];
    }
};
```

**線性佇列的問題：** 即使 rear 到達末端，front 前方的空間也無法再使用（假性滿佇列）。

---

## 四、環狀佇列 (Circular Queue)

### 4.1 概念說明

「將線性陣列的首尾相接，讓 rear 到達末端後可以繞回開頭，充分利用空間。」

```
         front
           ↓
  [_, _, _, 3, 4, 5, 6]
                     ↑
                    rear

加入後 rear 繞回：
  [7, 8, _, 3, 4, 5, 6]
       ↑  ↑
      rear front
```

關鍵：使用**模運算（%）**讓索引繞回：
```cpp
rear  = (rear  + 1) % MAX_SIZE;
front = (front + 1) % MAX_SIZE;
```

**如何判斷空/滿？**  
- 空：`front == rear`
- 滿：`(rear + 1) % MAX_SIZE == front`（預留一格空間避免與空狀態混淆）

### 4.2 程式碼實作

```cpp
#include <iostream>
using namespace std;

const int MAX_SIZE = 6;   // 實際可放 5 個元素（預留 1 格）

struct CircularQueue {
    int data[MAX_SIZE];
    int front, rear;

    CircularQueue() : front(0), rear(0) {}

    bool isEmpty() { return front == rear; }

    bool isFull()  { return (rear + 1) % MAX_SIZE == front; }

    void addQ(int val) {
        if (isFull()) { cout << "Queue Full!" << endl; return; }
        data[rear] = val;
        rear = (rear + 1) % MAX_SIZE;   // 繞回
    }

    int deleteQ() {
        if (isEmpty()) { cout << "Queue Empty!" << endl; return -1; }
        int val = data[front];
        front = (front + 1) % MAX_SIZE; // 繞回
        return val;
    }

    void printQueue() {
        cout << "Queue [front=" << front << ", rear=" << rear << "]: ";
        int i = front;
        while (i != rear) {
            cout << data[i] << " ";
            i = (i + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q;

    q.addQ(10); q.addQ(20); q.addQ(30); q.addQ(40); q.addQ(50);
    q.printQueue();       // 10 20 30 40 50

    cout << "取出: " << q.deleteQ() << endl;  // 10
    cout << "取出: " << q.deleteQ() << endl;  // 20
    q.printQueue();       // 30 40 50

    q.addQ(60); q.addQ(70);   // rear 繞回
    q.printQueue();       // 30 40 50 60 70

    return 0;
}
```

---

## 五、應用：老鼠走迷宮（堆疊回溯）

### 5.1 概念說明

用堆疊「記住走過的路徑」，遇到死路就回溯到上一個岔路口，嘗試其他方向。

```
迷宮（0=可走, 1=牆壁）：
  1 1 1 1 1
  1 0 0 1 1
  1 1 0 0 1
  1 1 1 0 1
  1 1 1 1 1

起點 (1,1)，終點 (3,3)
```

### 5.2 程式碼架構

```cpp
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

int maze[5][5] = {
    {1,1,1,1,1},
    {1,0,0,1,1},
    {1,1,0,0,1},
    {1,1,1,0,1},
    {1,1,1,1,1}
};

bool visited[5][5] = {false};

// 上下左右四個方向
int dx[] = {-1, 1, 0, 0};  // dx row index row-1 向上 row+1 向下
int dy[] = {0, 0, -1, 1};  // dy column index column-1 向左 column+1 向右

void solveMaze(int startX, int startY, int endX, int endY) {
    stack<pair<int,int>> path;
    path.push({startX, startY});
    visited[startX][startY] = true;

    while (!path.empty()) {
        auto [x, y] = path.top();

        if (x == endX && y == endY) {
            cout << "找到出口！路徑：" << endl;
            // 印出路徑（需另存才能正序印，此處簡化）
            return;
        }

        bool moved = false;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5
                && maze[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                path.push({nx, ny});
                cout << "移動到 (" << nx << "," << ny << ")" << endl;
                moved = true;
                break;
            }
        }

        if (!moved) {
            cout << "回溯，離開 (" << x << "," << y << ")" << endl;
            path.pop();   // 死路，回溯
        }
    }
    cout << "無法找到出口" << endl;
}

int main() {
    solveMaze(1, 1, 3, 3);
    return 0;
}
```

---

## 六、常見錯誤與注意事項

| 錯誤類型 | 說明 | 建議 |
|---------|------|------|
| Stack Overflow | top 超過陣列大小 | push 前先 `isFull()` 檢查 |
| Stack Underflow | 空 stack 仍 pop | pop 前先 `isEmpty()` 檢查 |
| 環狀佇列判滿條件 | `rear == front` 無法區分空/滿 | 預留一格，用 `(rear+1)%n == front` |
| 線性佇列假性全滿 | front 前方空間浪費 | 改用環狀佇列 |
| 迷宮回溯忘記標記已訪 | 無限迴圈 | 推入堆疊時立即標記 `visited` |

---

## 七、學習筆記摘要

```
本週關鍵概念：
┌──────────────────────────────────────────────────────┐
│ ✦ Stack：LIFO，push/pop 都在頂端                     │
│ ✦ Queue：FIFO，addQ 在尾端，deleteQ 在前端           │
│ ✦ 環狀佇列：用 % 繞回，預留 1 格判斷空/滿            │
│ ✦ Call Stack：函式呼叫時，返回位址存入堆疊            │
│ ✦ 迷宮回溯：堆疊記錄路徑，死路 pop() 回退            │
└──────────────────────────────────────────────────────┘
```

**現在試試看：**
> 修改括號匹配程式，讓它印出「第幾個字元導致不匹配」的詳細錯誤訊息。
