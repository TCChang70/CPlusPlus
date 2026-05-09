// ============================================================
//  第 6 週：圖形理論與搜尋 — 範例 & 練習題
//  對應學習文件：DS_Week6_Graph.md
//  編譯：g++ -g week6_graph_practice.cpp -o week6_graph_practice
// ============================================================
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

// ============================================================
//  【範例 1】相鄰矩陣 (Adjacency Matrix) — 無向圖
//
//  圖形：
//    0 — 1 — 2
//    |       |
//    3 — — — 4
//    邊：0-1, 0-3, 1-2, 2-4, 3-4
// ============================================================
struct MatrixGraph {
    int n;
    vector<vector<int>> mat;

    MatrixGraph(int n) : n(n), mat(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v) {   // 無向圖：兩個方向都加
        mat[u][v] = 1;
        mat[v][u] = 1;
    }

    bool isAdjacent(int u, int v) { return mat[u][v] == 1; }

    void print() {
        cout << "  ";
        for (int j = 0; j < n; j++) cout << j << " ";
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << i << " ";
            for (int j = 0; j < n; j++) cout << mat[i][j] << " ";
            cout << endl;
        }
    }
};

void example1_matrix() {
    cout << "=== 範例 1：相鄰矩陣 ===" << endl;

    MatrixGraph g(5);
    g.addEdge(0, 1); g.addEdge(0, 3);
    g.addEdge(1, 2); g.addEdge(2, 4);
    g.addEdge(3, 4);

    g.print();
    cout << "0 與 1 相鄰？" << (g.isAdjacent(0,1) ? "是" : "否") << endl;
    cout << "0 與 4 相鄰？" << (g.isAdjacent(0,4) ? "是" : "否") << endl;
    cout << "空間複雜度：O(n²) = " << 5*5 << " 格，無論邊數多少" << endl;
    cout << endl;
}

// ============================================================
//  【範例 2】相鄰串列 (Adjacency List) — 無向圖
//  使用 vector<vector<int>>，節省稀疏圖的空間
// ============================================================
struct ListGraph {
    int n;
    vector<vector<int>> adj;

    ListGraph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << ": [";
            for (int j = 0; j < (int)adj[i].size(); j++) {
                cout << adj[i][j];
                if (j + 1 < (int)adj[i].size()) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
};

void example2_list() {
    cout << "=== 範例 2：相鄰串列 ===" << endl;

    ListGraph g(5);
    g.addEdge(0, 1); g.addEdge(0, 3);
    g.addEdge(1, 2); g.addEdge(2, 4);
    g.addEdge(3, 4);

    g.print();
    cout << "空間複雜度：O(n + e) = O(" << 5 << " + " << 5 << ") = O(10)" << endl;
    cout << "→ 比相鄰矩陣的 O(25) 更省空間（稀疏圖時）" << endl;
    cout << endl;
}

// ============================================================
//  【範例 3】深先搜尋 DFS — 遞迴版
//  從起點出發，沿著一條路走到底，再回溯
// ============================================================
void dfsHelper(ListGraph& g, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int nb : g.adj[v]) {
        if (!visited[nb])
            dfsHelper(g, nb, visited);
    }
}

void dfs(ListGraph& g, int start) {
    vector<bool> visited(g.n, false);
    dfsHelper(g, start, visited);
    cout << endl;
}

// DFS 迭代版（使用 Stack，等同遞迴版）
void dfsIter(ListGraph& g, int start) {
    vector<bool> visited(g.n, false);
    stack<int> s;

    s.push(start);
    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (visited[v]) continue;
        visited[v] = true;
        cout << v << " ";
        // 倒序推入，使小編號先被走訪
        for (int i = (int)g.adj[v].size() - 1; i >= 0; i--) {
            int nb = g.adj[v][i];
            if (!visited[nb]) s.push(nb);
        }
    }
    cout << endl;
}

void example3_dfs() {
    cout << "=== 範例 3：深先搜尋 (DFS) ===" << endl;

    ListGraph g(5);
    g.addEdge(0, 1); g.addEdge(0, 3);
    g.addEdge(1, 2); g.addEdge(2, 4);
    g.addEdge(3, 4);

    cout << "從頂點 0 出發 DFS（遞迴）：";
    dfs(g, 0);

    cout << "從頂點 0 出發 DFS（迭代）：";
    dfsIter(g, 0);

    cout << "→ 遞迴 DFS 本質上就是用 Call Stack 儲存狀態" << endl;
    cout << endl;
}

// ============================================================
//  【範例 4】廣先搜尋 BFS — 使用 Queue
//  按層次走訪：先訪問所有距離 1 的頂點，再距離 2 的...
// ============================================================
void bfs(ListGraph& g, int start) {
    vector<bool> visited(g.n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";

        for (int nb : g.adj[v]) {
            if (!visited[nb]) {
                visited[nb] = true;
                q.push(nb);
            }
        }
    }
    cout << endl;
}

void example4_bfs() {
    cout << "=== 範例 4：廣先搜尋 (BFS) ===" << endl;

    ListGraph g(5);
    g.addEdge(0, 1); g.addEdge(0, 3);
    g.addEdge(1, 2); g.addEdge(2, 4);
    g.addEdge(3, 4);

    cout << "從頂點 0 出發 BFS：";
    bfs(g, 0);

    cout << "→ BFS 保證找到最短路徑（以跳數計）" << endl;
    cout << endl;
}

// ============================================================
//  【範例 5】Dijkstra 最短路徑 — 加權有向圖
//  使用 min-heap（priority_queue）
// ============================================================
struct WeightedGraph {
    int n;
    vector<vector<pair<int,int>>> adj;   // adj[u] = {(v, weight)}

    WeightedGraph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // 無向圖
    }
};

vector<int> dijkstra(WeightedGraph& g, int src) {
    vector<int> dist(g.n, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;   // 已有更短路徑，跳過

        for (auto [v, w] : g.adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void example5_dijkstra() {
    cout << "=== 範例 5：Dijkstra 最短路徑 ===" << endl;
    /*
       圖形（有向加權）：
       0 —4— 1
       |     |
       8     7
       |     |
       3 —9— 2
    */
    WeightedGraph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 3, 8);
    g.addEdge(1, 2, 7);
    g.addEdge(2, 3, 9);

    auto dist = dijkstra(g, 0);
    cout << "從頂點 0 出發的最短距離：" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  頂點 " << i << " → ";
        if (dist[i] == INF) cout << "無法到達" << endl;
        else                cout << dist[i] << endl;
    }
    cout << endl;
}

// ============================================================
//  ★ 練習題 1：轉換表示法
//  給定邊列表，分別建立相鄰矩陣與相鄰串列，並印出
// ============================================================
void practice1_representation() {
    cout << "=== 練習題 1：圖的表示法轉換 ===" << endl;
    cout << "圖：5 個頂點，邊：0-1, 0-2, 1-3, 2-3, 3-4" << endl;

    // 相鄰矩陣
    MatrixGraph mg(5);
    mg.addEdge(0,1); mg.addEdge(0,2); mg.addEdge(1,3);
    mg.addEdge(2,3); mg.addEdge(3,4);
    cout << "相鄰矩陣：" << endl;
    mg.print();

    // 相鄰串列
    ListGraph lg(5);
    lg.addEdge(0,1); lg.addEdge(0,2); lg.addEdge(1,3);
    lg.addEdge(2,3); lg.addEdge(3,4);
    cout << "相鄰串列：" << endl;
    lg.print();

    cout << endl;
}

// ============================================================
//  ★ 練習題 2：從頂點 0 做 DFS 與 BFS，比較走訪順序
// ============================================================
void practice2_dfs_vs_bfs() {
    cout << "=== 練習題 2：DFS vs BFS 走訪順序比較 ===" << endl;

    ListGraph g(6);
    // 圖：
    //   0 - 1 - 3
    //   |   |
    //   2 - 4 - 5
    g.addEdge(0,1); g.addEdge(0,2);
    g.addEdge(1,3); g.addEdge(1,4);
    g.addEdge(2,4); g.addEdge(4,5);

    cout << "從頂點 0 出發 DFS：";
    dfs(g, 0);

    cout << "從頂點 0 出發 BFS：";
    bfs(g, 0);

    cout << "→ DFS 深入一條路到底；BFS 先把鄰居全部走完再深入" << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 3：偵測圖是否連通（判斷所有頂點是否從起點可達）
// ============================================================
bool isConnected(ListGraph& g) {
    // TODO：從頂點 0 做 BFS/DFS，若所有頂點都被 visited，則連通
    vector<bool> visited(g.n, false);
    queue<int> q;
    visited[0] = true;
    q.push(0);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int nb : g.adj[v])
            if (!visited[nb]) { visited[nb] = true; q.push(nb); }
    }
    for (bool b : visited) if (!b) return false;
    return true;
}

void practice3_connectivity() {
    cout << "=== 練習題 3：圖的連通性 ===" << endl;

    ListGraph g1(4);
    g1.addEdge(0,1); g1.addEdge(1,2); g1.addEdge(2,3);
    cout << "連通圖（0-1-2-3）：" << (isConnected(g1) ? "連通 ✓" : "不連通 ✗") << endl;

    ListGraph g2(4);
    g2.addEdge(0,1); g2.addEdge(2,3);   // 兩個分量
    cout << "不連通圖（0-1 + 2-3）：" << (isConnected(g2) ? "連通 ✓" : "不連通 ✗") << endl;
    cout << endl;
}

// ============================================================
//  ★ 練習題 4：拓樸排序 (Topological Sort) — Kahn's Algorithm
//  只適用於 DAG（有向無環圖）
//  使用入度（In-degree）方式：每次選入度為 0 的頂點
// ============================================================
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

    if ((int)order.size() != n) return {};   // 有環，拓樸排序不存在
    return order;
}

void practice4_topo() {
    cout << "=== 練習題 4：拓樸排序 (Topological Sort) ===" << endl;
    cout << "情境：課程先修順序" << endl;
    cout << "  0=程式入門, 1=資料結構, 2=演算法, 3=作業系統, 4=專題" << endl;
    cout << "  先修：0→1, 0→2, 1→3, 2→3, 3→4" << endl;

    int n = 5;
    vector<vector<int>> adj(n);
    adj[0].push_back(1); adj[0].push_back(2);
    adj[1].push_back(3); adj[2].push_back(3);
    adj[3].push_back(4);

    auto order = topologicalSort(n, adj);
    if (order.empty()) {
        cout << "偵測到環，無法拓樸排序！" << endl;
    } else {
        cout << "合法修課順序：";
        for (int v : order) cout << v << " ";
        cout << endl;
    }

    // 測試有環的情況
    vector<vector<int>> adjCycle(3);
    adjCycle[0].push_back(1);
    adjCycle[1].push_back(2);
    adjCycle[2].push_back(0);   // 形成環
    auto order2 = topologicalSort(3, adjCycle);
    cout << "含環的圖 → " << (order2.empty() ? "偵測到環 ✓" : "拓樸排序成功 ✗") << endl;
    cout << endl;
}

// ============================================================
//  main
// ============================================================
int main() {
    example1_matrix();
    example2_list();
    example3_dfs();
    example4_bfs();
    example5_dijkstra();

    cout << "---------- 練習題 ----------" << endl << endl;
    practice1_representation();
    practice2_dfs_vs_bfs();
    practice3_connectivity();
    practice4_topo();

    return 0;
}
