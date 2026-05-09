// ============================================================
//  第 3 週：堆疊與佇列及其應用 — 範例 & 練習題
//  對應學習文件：DS_Week3_Stack_Queue.md
//  編譯：g++ -g week3_stack_queue_practice.cpp -o week3_stack_queue_practice
// ============================================================
#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  【範例 1】陣列實作堆疊 (Stack — LIFO)
// ============================================================
const int MAX = 100;

struct Stack {
    int data[MAX];
    int top;

    Stack() : top(-1) {}

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX - 1; }

    // 推入頂端
    bool push(int val) {
        if (isFull()) { cout << "[Stack] 溢位！" << endl; return false; }
        data[++top] = val;
        return true;
    }

    // 取出頂端
    int pop() {
        if (isEmpty()) { cout << "[Stack] 下溢！" << endl; return -1; }
        return data[top--];
    }

    // 查看頂端（不移除）
    int peek() {
        if (isEmpty()) { cout << "[Stack] 空!" << endl; return -1; }
        return data[top];
    }

    void print() {
        cout << "Stack (頂→底): [";
        for (int i = top; i >= 0; i--) {
            cout << data[i];
            if (i > 0) cout << ", ";
        }
        cout << "]" << endl;
    }
};

void example1_stack() {
    cout << "=== 範例 1：Stack (LIFO) ===" << endl;

    Stack s;
    s.push(1); s.push(2); s.push(3);
    s.print();

    cout << "Pop: " << s.pop() << endl;   // 3（後進先出）
    s.push(4);
    s.print();
    cout << "Peek: " << s.peek() << endl; // 4

    cout << endl;
}

// ============================================================
//  【範例 2】Stack 應用：括號匹配
//  概念：遇到左括號 push；遇到右括號 pop 並比對
// ============================================================
bool isMatching(char open, char close) {
    return (open == '(' && close == ')')
        || (open == '[' && close == ']')
        || (open == '{' && close == '}');
}

bool checkBrackets(const string& expr) {
    Stack s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.isEmpty() || !isMatching(s.pop(), c))
                return false;
        }
    }
    return s.isEmpty();   // 空 = 全部匹配
}

void example2_bracket() {
    cout << "=== 範例 2：括號匹配（Stack 應用）===" << endl;

    string tests[] = {"(())", "{[()]}", "([)]", "((("};
    for (auto& t : tests) {
        cout << "\"" << t << "\" → " << (checkBrackets(t) ? "✅ 合法" : "❌ 不合法") << endl;
    }
    cout << endl;
}

// ============================================================
//  【範例 3】環狀佇列 (Circular Queue — FIFO)
//  關鍵：用模運算 % 讓陣列「折繞」
//  有效容量 = QMAX - 1（留一格區分空/滿）
// ============================================================
const int QMAX = 6;   // 陣列大小，有效容量 = 5

struct CircularQueue {
    int data[QMAX];
    int front, rear;

    CircularQueue() : front(0), rear(0) {}

    bool isEmpty() { return front == rear; }
    // 滿：rear 的下一格 == front（有效容量 = QMAX - 1）
    bool isFull()  { return (rear + 1) % QMAX == front; }

    bool addQ(int val) {
        if (isFull()) { cout << "[Queue] 已滿！" << endl; return false; }
        data[rear] = val;
        rear = (rear + 1) % QMAX;   // 折繞
        return true;
    }

    int deleteQ() {
        if (isEmpty()) { cout << "[Queue] 已空！" << endl; return -1; }
        int val = data[front];
        front = (front + 1) % QMAX; // 折繞
        return val;
    }

    void print() {
        cout << "Queue (前→後): [";
        int i = front;
        bool first = true;
        while (i != rear) {
            if (!first) cout << ", ";
            cout << data[i];
            i = (i + 1) % QMAX;
            first = false;
        }
        cout << "] front=" << front << " rear=" << rear << endl;
    }
};

void example3_circular_queue() {
    cout << "=== 範例 3：環狀佇列 (FIFO) ===" << endl;

    CircularQueue q;
    q.addQ(10); q.addQ(20); q.addQ(30); q.addQ(40); q.addQ(50);
    q.print();

    cout << "DeleteQ: " << q.deleteQ() << endl;   // 10（先進先出）
    q.addQ(60);   // 折繞回到位置 0
    q.print();

    // 嘗試加入第 6 個（超過有效容量 5）
    q.addQ(70);

    cout << endl;
}

// ============================================================
//  【範例 4】Stack 應用：老鼠走迷宮（DFS 回溯）
//  迷宮：0 = 通道, 1 = 牆壁
//  起點 (0,0)，終點 (4,4)
// ============================================================
const int ROWS = 5, COLS = 5;

int maze[ROWS][COLS] = {
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0}
};

struct Pos { int r, c; };

struct PosStack {
    Pos data[ROWS * COLS];
    int top = -1;
    bool isEmpty()  { return top == -1; }
    void push(Pos p) { data[++top] = p; }
    Pos pop()       { return data[top--]; }
    Pos peek()      { return data[top]; }
};

// 四個方向：下、右、上、左
int dr[] = {1, 0, -1,  0};
int dc[] = {0, 1,  0, -1};

bool solveMaze() {
    bool visited[ROWS][COLS] = {};
    PosStack path;

    Pos start = {0, 0};
    path.push(start);
    visited[0][0] = true;

    while (!path.isEmpty()) {
        Pos curr = path.peek();

        if (curr.r == ROWS - 1 && curr.c == COLS - 1) {
            // 到達終點，印出路徑
            cout << "找到路徑（" << path.top + 1 << " 步）：" << endl;
            for (int i = 0; i <= path.top; i++) {
                cout << "(" << path.data[i].r << "," << path.data[i].c << ")";
                if (i < path.top) cout << " → ";
            }
            cout << endl;
            return true;
        }

        bool moved = false;
        for (int d = 0; d < 4; d++) {
            int nr = curr.r + dr[d];
            int nc = curr.c + dc[d];
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS
                && maze[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = true;
                path.push({nr, nc});
                moved = true;
                break;
            }
        }
        if (!moved) path.pop();   // 死路，回溯！
    }
    cout << "找不到路徑" << endl;
    return false;
}

void example4_maze() {
    cout << "=== 範例 4：老鼠走迷宮（Stack 回溯）===" << endl;
    cout << "迷宮（0=通道, 1=牆）：" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }
    solveMaze();
    cout << endl;
}

// ============================================================
//  ★ 練習題 1：模擬 Stack 操作序列
//  要求：照下列操作執行，並印出每步後的 Stack 狀態
// ============================================================
void practice1_stack_ops() {
    cout << "=== 練習題 1：Stack 操作序列 ===" << endl;

    Stack s;
    // 操作：Push(1), Push(2), Push(3), Pop(), Push(4), Pop(), Pop()
    string ops[] = {"Push(1)", "Push(2)", "Push(3)", "Pop()", "Push(4)", "Pop()", "Pop()"};

    s.push(1); cout << ops[0] << " → "; s.print();
    s.push(2); cout << ops[1] << " → "; s.print();
    s.push(3); cout << ops[2] << " → "; s.print();
    cout << ops[3] << " 取出 " << s.pop() << " → "; s.print();
    s.push(4); cout << ops[4] << " → "; s.print();
    cout << ops[5] << " 取出 " << s.pop() << " → "; s.print();
    cout << ops[6] << " 取出 " << s.pop() << " → "; s.print();

    cout << "最終 Stack 內容（底→頂）：[1]，共剩 1 個元素" << endl << endl;
}

// ============================================================
//  ★ 練習題 2：環狀佇列狀態追蹤
//  模擬：AddQ(A), AddQ(B), AddQ(C), DeleteQ(), AddQ(D), AddQ(E)
//  驗證 front / rear 的值
// ============================================================
void practice2_queue_trace() {
    cout << "=== 練習題 2：環狀佇列狀態追蹤 ===" << endl;

    CircularQueue q;  // 陣列大小 QMAX=6，有效容量 5
    cout << "初始 → "; q.print();

    q.addQ(65);  cout << "AddQ(A=65) → "; q.print();
    q.addQ(66);  cout << "AddQ(B=66) → "; q.print();
    q.addQ(67);  cout << "AddQ(C=67) → "; q.print();
    cout << "DeleteQ → 取出 " << q.deleteQ() << " → "; q.print();
    q.addQ(68);  cout << "AddQ(D=68) → "; q.print();
    q.addQ(69);  cout << "AddQ(E=69) → "; q.print();

    cout << "→ front=" << q.front << " rear=" << q.rear
         << "（rear 在 front 的下一格時為滿）" << endl << endl;
}

// ============================================================
//  ★ 練習題 3：用兩個 Stack 模擬 Queue（挑戰）
//  原理：
//    push → 推入 s1
//    pop  → 若 s2 空，將 s1 全部倒入 s2，再從 s2 pop
// ============================================================
struct StackQueue {
    Stack s1, s2;   // s1 接收新元素，s2 輸出元素

    void enqueue(int val) {
        s1.push(val);
    }

    int dequeue() {
        if (s2.isEmpty()) {
            // 將 s1 倒入 s2（反轉順序，讓最舊的在頂端）
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
            }
        }
        if (s2.isEmpty()) {
            cout << "[StackQueue] 空!" << endl;
            return -1;
        }
        return s2.pop();
    }
};

void practice3_two_stacks_queue() {
    cout << "=== 練習題 3：兩個 Stack 模擬 Queue ===" << endl;

    StackQueue q;
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    cout << "Enqueue: 10, 20, 30" << endl;
    cout << "Dequeue: " << q.dequeue() << " (預期 10，FIFO)" << endl;
    cout << "Dequeue: " << q.dequeue() << " (預期 20)" << endl;
    q.enqueue(40);
    cout << "Enqueue: 40" << endl;
    cout << "Dequeue: " << q.dequeue() << " (預期 30)" << endl;
    cout << "Dequeue: " << q.dequeue() << " (預期 40)" << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 4：Stack 應用 — 後序運算式求值
//  後序表示法（Postfix）：運算元先進，遇到運算子時 pop 兩個計算
//  例：3 4 + 2 * = (3+4)*2 = 14
// ============================================================
int evalPostfix(const string& expr) {
    Stack s;
    int i = 0;
    while (i < (int)expr.size()) {
        char c = expr[i];
        if (c == ' ') { i++; continue; }

        if (c >= '0' && c <= '9') {
            // 讀取完整數字（可能多位）
            int num = 0;
            while (i < (int)expr.size() && expr[i] >= '0' && expr[i] <= '9') {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            s.push(num);
        } else {
            int b = s.pop();   // 注意：b 先 pop
            int a = s.pop();
            if (c == '+') s.push(a + b);
            else if (c == '-') s.push(a - b);
            else if (c == '*') s.push(a * b);
            else if (c == '/') s.push(a / b);
            i++;
        }
    }
    return s.pop();
}

void practice4_postfix() {
    cout << "=== 練習題 4：後序運算式求值 ===" << endl;

    // "3 4 +" = 3+4 = 7
    cout << "\"3 4 +\" = " << evalPostfix("3 4 +") << " (預期 7)" << endl;
    // "3 4 + 2 *" = (3+4)*2 = 14
    cout << "\"3 4 + 2 *\" = " << evalPostfix("3 4 + 2 *") << " (預期 14)" << endl;
    // "5 1 2 + 4 * + 3 -" = 5 + ((1+2)*4) - 3 = 14
    cout << "\"5 1 2 + 4 * + 3 -\" = " << evalPostfix("5 1 2 + 4 * + 3 -") << " (預期 14)" << endl;
    cout << endl;
}

// ============================================================
//  main
// ============================================================
int main() {
    example1_stack();
    example2_bracket();
    example3_circular_queue();
    example4_maze();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_stack_ops();
    practice2_queue_trace();
    practice3_two_stacks_queue();
    practice4_postfix();

    return 0;
}
