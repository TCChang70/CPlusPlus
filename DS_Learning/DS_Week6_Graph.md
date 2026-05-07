# 第 6 週：圖形理論與搜尋 (Graph Theory & Search)

> 適用程度：初學者 → 有基礎｜語言：C++

---

## 一、什麼是圖形？ (What is a Graph?)

圖形是由**頂點 (Vertex)** 和**邊 (Edge)** 組成的結構，能表示複雜的「多對多」關係。

```
無向圖：            有向圖 (Digraph)：
  0 — 1              0 → 1
  |   |              ↑   ↓
  3 — 2              3 ← 2
```

**真實應用：**
- 地圖與導航（頂點=地點，邊=道路，權重=距離）
- 社群網路（頂點=人，邊=朋友關係）
- 工作排程（有向無環圖 DAG）
- 網頁排名（PageRank）

**關鍵術語：**

| 術語 | 說明 |
|------|------|
| 無向圖 Undirected Graph | 邊無方向，(u,v) = (v,u) |
| 有向圖 Directed Graph | 邊有方向，(u→v) ≠ (v→u) |
| 加權圖 Weighted Graph | 邊帶有數值（距離、成本） |
| 相鄰 Adjacent | 兩頂點之間有邊連接 |
| 度數 Degree | 一個頂點連接的邊數 |
| 路徑 Path | 頂點序列，每對相鄰頂點間有邊 |

---

## 二、圖形的表示法

### 2.1 相鄰矩陣 (Adjacency Matrix)

用 $n \times n$ 的二維陣列表示，`matrix[i][j] = 1` 表示 i 與 j 之間有邊。

```
圖：0—1, 0—3, 1—2, 2—3

    0  1  2  3
0 [ 0  1  0  1 ]
1 [ 1  0  1  0 ]
2 [ 0  1  0  1 ]
3 [ 1  0  1  0 ]
```

**複雜度：**
- 空間：$O(n^2)$（無論邊多少，都要 $n^2$ 空間）
- 查詢兩點是否相鄰：$O(1)$
- 列出頂點 v 的所有鄰居：$O(n)$（要掃整列）

**適合：** 邊數多（稠密圖 Dense Graph）

### 2.2 相鄰串列 (Adjacency List)

每個頂點維護一個鏈結串列（或 vector），儲存它的所有鄰居。

```
0: [1, 3]
1: [0, 2]
2: [1, 3]
3: [0, 2]
```

**複雜度：**
- 空間：$O(n + e)$（n = 頂點數，e = 邊數）
- 查詢兩點是否相鄰：$O(\text{degree})$
- 列出頂點 v 的所有鄰居：$O(\text{degree})$

**適合：** 邊數少（稀疏圖 Sparse Graph）

---

## 三、建立圖形的程式碼

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int VERTICES = 4;

// 方式 1：相鄰矩陣
int adjMatrix[VERTICES][VERTICES] = {
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0}
};

// 方式 2：相鄰串列（用 vector 實作）
vector<int> adjList[VERTICES];

void buildAdjList() {
    // 無向圖：每條邊新增兩次
    auto addEdge = [](int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 3);
}

void printAdjList() {
    for (int i = 0; i < VERTICES; i++) {
        cout << i << ": ";
        for (int neighbor : adjList[i])
            cout << neighbor << " ";
        cout << endl;
    }
}
```

---

## 四、深先搜尋 (Depth-First Search, DFS)

### 4.1 概念說明

「盡可能往深處走，直到死路才回頭，然後嘗試其他方向。」

```
圖：0—1—2
    |   |
    3———4

從 0 開始 DFS（假設優先走小號頂點）：
0 → 1 → 2 → 4 → 3（回溯）→ 完成
走訪順序：0, 1, 2, 4, 3
```

### 4.2 遞迴實作

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
vector<int> adjList[N];
bool visited[N] = {false};

void dfs(int v) {
    visited[v] = true;
    cout << v << " ";

    for (int neighbor : adjList[v]) {
        if (!visited[neighbor])
            dfs(neighbor);   // 遞迴往深處走
    }
}

void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

int main() {
    addEdge(0, 1); addEdge(1, 2);
    addEdge(0, 3); addEdge(2, 4);
    addEdge(3, 4);

    cout << "DFS 走訪（從頂點 0 開始）: ";
    dfs(0);
    cout << endl;

    return 0;
}
```

### 4.3 用堆疊改寫遞迴 DFS

遞迴版 DFS 本質上是利用「函式呼叫堆疊」。可以手動用 `stack` 改寫：

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfsIterative(int start, vector<int> adjList[], int n) {
    vector<bool> visited(n, false);
    stack<int> s;

    s.push(start);

    while (!s.empty()) {
        int v = s.top(); s.pop();

        if (visited[v]) continue;   // 已訪問則跳過
        visited[v] = true;
        cout << v << " ";

        // 反向壓入，確保小號頂點先處理（與遞迴版一致）
        for (int i = adjList[v].size() - 1; i >= 0; i--) {
            if (!visited[adjList[v][i]])
                s.push(adjList[v][i]);
        }
    }
}
```

---

## 五、廣先搜尋 (Breadth-First Search, BFS)

### 5.1 概念說明

「先走訪所有距離 1 的鄰居，再走訪距離 2 的，依此類推。」  
使用**佇列 (Queue)** 實作。

```
圖：0—1—2
    |   |
    3———4

BFS 從 0 開始：
層 0: 0
層 1: 1, 3
層 2: 2, 4
走訪順序：0, 1, 3, 2, 4
```

### 5.2 程式碼實作

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, vector<int> adjList[], int n) {
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;   // 推入前標記，避免重複加入
                q.push(neighbor);
            }
        }
    }
}
```

---

## 六、最短路徑（概念）：Dijkstra 演算法

### 6.1 概念說明

在**加權圖**中，找從起點到所有頂點的最短路徑。

**策略：** 每次從未確定的頂點中，選距離最短的那個，更新其鄰居的距離。

```
圖（有向加權）：
  0 —(4)→ 1
  |        ↑
 (1)      (2)
  ↓        |
  2 —(5)→ 3

從 0 出發的最短路徑：
  到 0: 0
  到 1: min(4, 1+5+2=8) = 4
  到 2: 1
  到 3: 1 + 5 = 6
```

### 6.2 程式碼實作

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int,int> pii;  // {距離, 頂點}

void dijkstra(int start, vector<vector<pii>>& graph, int n) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;  // 最小堆

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;  // 已找到更短路徑，跳過

        for (auto [weight, v] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "從頂點 " << start << " 出發的最短距離：" << endl;
    for (int i = 0; i < n; i++)
        cout << "  到 " << i << ": " << dist[i] << endl;
}

int main() {
    int n = 4;
    vector<vector<pii>> graph(n);  // graph[u] = { {weight, v}, ... }

    graph[0].push_back({4, 1});
    graph[0].push_back({1, 2});
    graph[2].push_back({5, 3});
    graph[3].push_back({2, 1});

    dijkstra(0, graph, n);
    return 0;
}
```

---

## 七、最小成本延展樹概念 (MST — Minimum Spanning Tree)

**定義：** 連接圖中所有頂點，且**總邊權最小**的無環子圖。

```
圖：
  0 —(2)— 1 —(3)— 2
  |                |
 (6)              (1)
  |                |
  3 ——(5)————————— 4

MST（Kruskal 選邊）：
  選 (2,4) w=1 → 選 (0,1) w=2 → 選 (1,2) w=3 → 選 (3,4) w=5
  總權重 = 1+2+3+5 = 11
```

**兩大演算法：**
- **Kruskal**：將所有邊按權重排序，逐一加入不形成環的邊
- **Prim**：從任一頂點開始，每次選距離已選頂點集合最近的邊

---

## 八、拓樸排序概念 (Topological Sorting)

**適用：** 有向無環圖 (DAG)，表示工作之間有「先後依賴」關係。

**結果：** 輸出一個頂點序列，使得對於每條有向邊 $u \to v$，$u$ 都在 $v$ 之前。

```
工作依賴：
  A → C
  B → C → E
  B → D → E

拓樸排序（其中一種）：A, B, C, D, E
（或：B, A, D, C, E 也合法）
```

---

## 九、常見錯誤與注意事項

| 錯誤類型 | 說明 | 建議 |
|---------|------|------|
| DFS 忘記標記 visited | 在有環的圖中無限遞迴 | 進入 dfs(v) 時立即標記 visited[v] |
| BFS 在推入前未標記 visited | 同一頂點被推入佇列多次 | 推入時（非取出時）標記 visited |
| 相鄰矩陣用於稀疏大圖 | $n=10000$ 時矩陣佔 $10^8$ bytes | 稀疏圖用相鄰串列 |
| Dijkstra 用於負權邊 | 負權邊 Dijkstra 結果錯誤 | 負權邊改用 Bellman-Ford |
| 拓樸排序用於有環圖 | 無法完成拓樸排序 | 先確認圖是 DAG |

---

## 十、學習筆記摘要

```
本週關鍵概念：
┌──────────────────────────────────────────────────────────┐
│ ✦ 相鄰矩陣：O(n²) 空間，查詢快 O(1)，適合稠密圖        │
│ ✦ 相鄰串列：O(n+e) 空間，走訪快，適合稀疏圖            │
│ ✦ DFS：用遞迴（或手動堆疊），深度優先                   │
│ ✦ BFS：用佇列，廣度優先，可求無加權圖最短路徑           │
│ ✦ Dijkstra：加權圖最短路徑，使用最小堆                  │
│ ✦ MST：最小成本連接所有頂點（Kruskal/Prim）             │
│ ✦ 拓樸排序：DAG 的依賴順序排列                          │
└──────────────────────────────────────────────────────────┘
```

**現在試試看：**
> 自己畫一張 5 個頂點、6 條邊的無向圖，同時用**相鄰矩陣**和**相鄰串列**表示，然後手動追蹤從頂點 0 開始的 DFS 與 BFS 走訪順序。
