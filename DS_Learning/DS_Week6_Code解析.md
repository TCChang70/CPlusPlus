# 第 6 週 程式碼解析：圖形理論與搜尋

> 對應練習檔：`week6_graph_practice.cpp`  
> 對應學習文件：[DS_Week6_Graph.md](DS_Week6_Graph.md)  
> 程度：初學者 → 有基礎｜語言：C++

---

## 整體功能說明

本週練習檔涵蓋圖形 (Graph) 的兩種表示法與四種核心演算法：

| 編號 | 函式 | 主題 |
|------|------|------|
| 範例 1 | `example1_matrix()` | 相鄰矩陣 (Adjacency Matrix) |
| 範例 2 | `example2_list()` | 相鄰串列 (Adjacency List) |
| 範例 3 | `example3_dfs()` | 深先搜尋 DFS（遞迴版 + 迭代版） |
| 範例 4 | `example4_bfs()` | 廣先搜尋 BFS |
| 範例 5 | `example5_dijkstra()` | Dijkstra 最短路徑 |
| 練習 1 | `practice1_representation()` | 圖的表示法轉換 |
| 練習 2 | `practice2_dfs_vs_bfs()` | DFS vs BFS 走訪順序比較 |
| 練習 3 | `practice3_connectivity()` | 圖的連通性偵測 |
| 練習 4 | `practice4_topo()` | 拓樸排序（Kahn 算法） |

---

## 範例 1：相鄰矩陣 (Adjacency Matrix)

### 資料結構

```cpp
struct MatrixGraph {
    int n;
    vector<vector<int>> mat;   // n × n 的二維矩陣

    MatrixGraph(int n) : n(n), mat(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v) {
        mat[u][v] = 1;
        mat[v][u] = 1;   // 無向圖：兩個方向都設為 1
    }
};
```

### 圖示

```
圖：0-1, 0-3, 1-2, 2-4, 3-4

  | 0 1 2 3 4
--+-----------
0 | 0 1 0 1 0
1 | 1 0 1 0 0
2 | 0 1 0 0 1
3 | 1 0 0 0 1
4 | 0 0 1 1 0
```

### 特性分析

| 操作 | 複雜度 | 說明 |
|------|--------|------|
| 判斷 u-v 是否相鄰 | $O(1)$ | `mat[u][v]` 直接存取 |
| 取得 u 的所有鄰居 | $O(n)$ | 需掃描整列 |
| 空間 | $O(n^2)$ | 不論邊數多少都需 n×n |

**適用情境：** 稠密圖（邊數接近 $n^2$），或需要頻繁查詢特定邊是否存在。

---

## 範例 2：相鄰串列 (Adjacency List)

### 資料結構

```cpp
struct ListGraph {
    int n;
    vector<vector<int>> adj;   // adj[u] = u 的所有鄰居列表

    ListGraph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);   // 無向圖
    }
};
```

### 特性分析

| 操作 | 複雜度 | 說明 |
|------|--------|------|
| 判斷 u-v 是否相鄰 | $O(\deg(u))$ | 需掃描 u 的鄰居列表 |
| 取得 u 的所有鄰居 | $O(\deg(u))$ | 直接遍歷 `adj[u]` |
| 空間 | $O(n + e)$ | $e$ = 邊數（稀疏圖省空間） |

**適用情境：** 稀疏圖（邊數遠小於 $n^2$），大多數圖的問題首選。

### 兩種表示法比較

| | 相鄰矩陣 | 相鄰串列 |
|--|---------|---------|
| 空間 | $O(n^2)$ | $O(n + e)$ |
| 查詢特定邊 | $O(1)$ | $O(\deg)$ |
| 走訪所有邊 | $O(n^2)$ | $O(n + e)$ |
| 適合 | 稠密圖 | 稀疏圖（多數情況） |

---

## 範例 3：深先搜尋 DFS

### 遞迴版

```cpp
void dfsHelper(ListGraph& g, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int nb : g.adj[v]) {
        if (!visited[nb])
            dfsHelper(g, nb, visited);   // 遞迴深入
    }
}
```

### 迭代版（使用 Stack）

```cpp
void dfsIter(ListGraph& g, int start) {
    vector<bool> visited(g.n, false);
    stack<int> s;

    s.push(start);
    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (visited[v]) continue;        // 可能重複推入，需過濾
        visited[v] = true;
        cout << v << " ";
        // 倒序推入，讓小編號先被走訪
        for (int i = (int)g.adj[v].size() - 1; i >= 0; i--) {
            if (!visited[g.adj[v][i]])
                s.push(g.adj[v][i]);
        }
    }
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `visited[v] = true` | 標記已訪問，避免重複走訪（防止無限迴圈） |
| `for (int nb : g.adj[v])` | 走訪 v 的所有鄰居 |
| 倒序推入 Stack | 確保迭代版與遞迴版的走訪順序一致 |
| `if (visited[v]) continue` | 因為同一頂點可能被多次 push，出 Stack 時需再次確認 |

### DFS 走訪示意（從頂點 0 出發）

```
圖：0-1, 0-3, 1-2, 2-4, 3-4

DFS：0 → 1 → 2 → 4 → 3
（沿著一條路走到底，再回溯）
```

---

## 範例 4：廣先搜尋 BFS

### 程式碼

```cpp
void bfs(ListGraph& g, int start) {
    vector<bool> visited(g.n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);              // ① 起點入隊並標記

    while (!q.empty()) {
        int v = q.front(); q.pop();    // ② 取出隊頭
        cout << v << " ";
        for (int nb : g.adj[v]) {
            if (!visited[nb]) {
                visited[nb] = true;    // ③ 標記（入隊時標記，非出隊時）
                q.push(nb);            // ③ 鄰居入隊
            }
        }
    }
}
```

### 關鍵設計：何時標記 visited？

在 **入隊時** 標記（而非出隊時），避免同一頂點被重複加入 Queue。

### BFS 走訪示意（從頂點 0 出發）

```
圖：0-1, 0-3, 1-2, 2-4, 3-4

BFS：0 → 1 → 3 → 2 → 4
（先把 0 的所有鄰居走完，再走下一層）
```

### DFS vs BFS 比較

| | DFS | BFS |
|--|-----|-----|
| 資料結構 | Stack（遞迴用 Call Stack） | Queue |
| 走訪特性 | 深入一條路到底 | 按層次展開 |
| 最短路徑 | ❌ 不保證（跳數） | ✅ 保證最少跳數 |
| 記憶體用量 | $O(\text{深度})$ | $O(\text{寬度})$ |
| 應用 | 拓樸排序、尋找連通分量 | 最短路徑（等權重）、層次遍歷 |

---

## 範例 5：Dijkstra 最短路徑（加權圖）

### 程式碼

```cpp
vector<int> dijkstra(WeightedGraph& g, int src) {
    vector<int> dist(g.n, INF);    // 所有距離初始化為無限大
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<>> pq;  // min-heap（最小優先佇列）

    dist[src] = 0;
    pq.push({0, src});             // {距離, 頂點}

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // 過期的距離，跳過

        for (auto [v, w] : g.adj[u]) {
            if (dist[u] + w < dist[v]) {  // 鬆弛 (relaxation)
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

### 逐行解析

| 程式碼 | 說明 |
|--------|------|
| `vector<int> dist(g.n, INF)` | 初始化所有頂點距離為無限大 |
| `priority_queue<..., greater<>>` | Min-heap：優先取出**距離最小**的頂點 |
| `auto [d, u] = pq.top()` | C++17 結構化綁定 (structured binding)，解構 pair |
| `if (d > dist[u]) continue` | 懶惰刪除 (lazy deletion)：跳過已有更短路徑的過期紀錄 |
| `dist[u] + w < dist[v]` | 鬆弛條件：若經過 u 到 v 比已知距離更短，更新 |

### 時間複雜度

使用 min-heap：$O((n + e) \log n)$

**限制：** Dijkstra 不適用於**負邊權重**（需改用 Bellman-Ford）。

---

## 練習題 4：拓樸排序（Kahn 算法）

### 演算法流程

```
1. 計算所有頂點的入度 (in-degree)
2. 將入度為 0 的頂點加入 Queue
3. 每次從 Queue 取出一個頂點 u：
   a. u 加入結果序列
   b. 移除 u 的所有出邊（將鄰居入度 -1）
   c. 若鄰居入度變為 0，加入 Queue
4. 結果序列長度 == n → 合法拓樸排序
         長度 < n  → 圖含環，拓樸排序不存在
```

### 程式碼

```cpp
vector<int> topologicalSort(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indegree[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }

    if ((int)order.size() != n) return {};   // 偵測到環
    return order;
}
```

**應用情境：** 課程先修順序、編譯器依賴分析、任務調度。

---

## 學習筆記摘要

```
【Week 6 重點整理】

✅ 圖的表示法選擇
   稠密圖（e ≈ n²）→ 相鄰矩陣（查詢邊 O(1)）
   稀疏圖（e << n²）→ 相鄰串列（省空間）
   大多數實際問題：相鄰串列

✅ DFS 重點
   Stack（遞迴 = Call Stack，迭代 = 顯式 Stack）
   visited 陣列防止重複走訪
   用途：拓樸排序、尋找連通分量、偵測環

✅ BFS 重點
   Queue（FIFO）
   入隊時標記 visited（不是出隊時）
   用途：最短路徑（等權重）、層次遍歷

✅ Dijkstra
   適用：有向/無向加權圖，邊權重非負
   Min-heap 取最短距離頂點
   鬆弛條件：dist[u] + w < dist[v] → 更新
   不適用：負邊權重（改用 Bellman-Ford）

✅ 拓樸排序（Kahn 算法）
   只適用於 DAG（有向無環圖）
   入度為 0 → 可優先處理
   排序完長度 < n → 圖含環

⚠️ 常見陷阱
   1. DFS 忘記 visited 標記 → 在含環圖上無限遞迴
   2. BFS 在出隊時才標記 → 同節點重複入隊，效率下降
   3. Dijkstra 遇負邊權重 → 結果不正確
   4. 拓樸排序用於非 DAG → 結果序列長度 < n 需偵測
   5. priority_queue 預設為 max-heap，Dijkstra 需用 greater<> 改成 min-heap
```

---

> 現在試試看：修改 `example5_dijkstra` 中的圖，加入一條**負邊**（例如 `w = -1`），  
> 觀察 Dijkstra 的輸出是否正確，理解為何負邊會破壞算法的假設。
