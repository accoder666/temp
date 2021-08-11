#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
inline void AddEdge(int, int, int);
inline int dinic(int, int);

int main() {
    freopen("tobira.in", "r", stdin);
    freopen("tobira.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    int f, sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f), sum += f;
        AddEdge((n << 1) + 1, i, f);
        AddEdge(n + i, (n << 1) + 2, f);
    }
    int u, v, w;
    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        AddEdge(u, n + v, w);
    }
    printf("%d\n", sum - dinic((n << 1) + 1, (n << 1) + 2));
    return 0;
}

inline void AddEdge(const int u, const int v, const int val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int d[maxn];

queue<int> Q;
inline bool bfs(const int s, const int t) {
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

int cur[maxn];

int dfs(const int u, const int t, int flow) {
    if (u == t || !flow)
        return flow;
    int ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(G[i].to, t, min(flow, G[i].val)))) {
            ret += tmp, flow -= tmp, G[i].val -= tmp, G[i ^ 1].val += tmp;
            if (!flow)
                break;
        }
    return ret;
}

inline int dinic(const int s, const int t) {
    int ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, t, INT_MAX);
    }
    return ret;
}
