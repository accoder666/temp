#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxm = 150010, maxn = 110;
struct edge {
    int to, nxt, val;
};
edge G[maxm << 1];
int head[maxm], cnt = 1;
inline void AddEdge(const int&, const int&, const int&);
inline int dinic(const int&, const int&);
int id[maxn][maxn], C[maxn][maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int c = 2;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) id[i][j] = ++c;
    int val, sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &val), sum += val;
            if ((i + j) & 1)
                AddEdge(1, id[i][j], val);
            else
                AddEdge(id[i][j], 2, val);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &val), sum += val;
            if ((i + j) & 1)
                AddEdge(id[i][j], 2, val);
            else
                AddEdge(1, id[i][j], val);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", C[i] + j);
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) {
            sum += C[i][j] + C[i + 1][j];
            AddEdge(id[i][j], id[i + 1][j], C[i][j] + C[i + 1][j]);
            AddEdge(id[i + 1][j], id[i][j], C[i][j] + C[i + 1][j]);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) {
            sum += C[i][j] + C[i][j + 1];
            AddEdge(id[i][j], id[i][j + 1], C[i][j] + C[i][j + 1]);
            AddEdge(id[i][j + 1], id[i][j], C[i][j] + C[i][j + 1]);
        }
    printf("%d\n", sum - dinic(1, 2));
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
}

int d[maxm];
queue<int> Q;
inline bool bfs(const int& s, const int& t) {
    memset(d, 0, sizeof(d));
    d[s] = 1;
    Q.push(s);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = head[u]; i; i = G[i].nxt)
            if (G[i].val && !d[G[i].to])
                d[G[i].to] = d[u] + 1, Q.push(G[i].to);
    }
    return d[t];
}

int cur[maxm];
int dfs(const int& u, const int& t, int flow) {
    if (u == t || !flow)
        return flow;
    int ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(G[i].to, t, min(flow, G[i].val)))) {
            G[i].val -= tmp, G[i ^ 1].val += tmp, ret += tmp, flow -= tmp;
            if (!flow)
                break;
        }
    return ret;
}

inline int dinic(const int& s, const int& t) {
    int ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, t, INT_MAX);
    }
    return ret;
}
