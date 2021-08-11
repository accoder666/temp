#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
const int maxn = 110;
struct edge {
    int to, nxt, val;
};
edge G[maxn * maxn << 3];
int head[maxn * maxn], cnt = 1;
int M[maxn][maxn];
inline void AddEdge(const int&, const int&, const int&);
inline int dinic(const int&, const int&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    auto f = [m](const int& x, const int& y) { return (x - 1) * m + y; };
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", M[i] + j);
            switch (M[i][j]) {
                case 1:
                    AddEdge(0, f(i, j), n * m << 2);
                    break;
                case 2:
                    AddEdge(f(i, j), f(n, m) + 1, n * m << 2);
                    break;
                default:
                    break;
            }
        }
    int x, y;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < 4; k++) {
                x = i + dx[k], y = j + dy[k];
                if (x && x <= n && y && y <= m)
                    AddEdge(f(i, j), f(x, y), 1);
            }
    printf("%d\n", dinic(0, f(n, m) + 1));
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int d[maxn * maxn];

queue<int> Q;
inline bool bfs(const int& s, const int& t) {
    memset(d, 0, sizeof(d));
    d[s] = 1, Q.push(s);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = head[u]; i; i = G[i].nxt)
            if (G[i].val && !d[G[i].to])
                d[G[i].to] = d[u] + 1, Q.push(G[i].to);
    }
    return d[t];
}

int cur[maxn * maxn];
int dfs(const int& u, const int& t, int flow) {
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

inline int dinic(const int& s, const int& t) {
    int ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, t, INT_MAX);
    }
    return ret;
}
