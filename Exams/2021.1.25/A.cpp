#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 510;
struct edge {
    int to, nxt, val;
};
edge G[maxn * maxn << 1];
int head[maxn], cnt = 1;
int M[maxn][maxn];
inline void AddEdge(const int&, const int&, const int&);
inline int dinic(const int&, const int&);
int from[maxn * maxn], to[maxn * maxn];
int link[maxn][maxn];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n >> 1; i++) AddEdge(0, i, k);
    for (int i = (n >> 1) + 1; i <= n; i++) AddEdge(i, n + 1, k);
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        AddEdge(x, y, 1);
        M[x][y] = i;
    }
    int ans = dinic(0, n + 1);
    int c = 0;
    for (int i = 1; i <= n >> 1; i++)
        for (int j = head[i]; j; j = G[j].nxt)
            if (!G[j].val && G[j].to)
                from[++c] = i, to[c] = G[j].to;
    int c1, c2, u, col;
    for (int i = 1; i <= c; i++) {
        c1 = c2 = 0;
        for (int j = 1; j <= k; j++)
            if (!link[from[i]][j]) {
                c1 = j;
                break;
            }
        for (int j = 1; j <= k; j++)
            if (!link[to[i]][j]) {
                c2 = j;
                break;
            }
        if (!c1 || !c2)
            continue;
        link[from[i]][c1] = to[i], link[to[i]][c2] = from[i];
        if (c1 != c2) {
            u = to[i], col = c2;
            while (u) {
                link[u][c1] ^= link[u][c2] ^= link[u][c1] ^= link[u][c2];
                u = link[u][col], col = col == c1 ? c2 : c1;
            }
        }
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            if (link[i][j] && i < link[i][j])
                printf("%d %d\n", M[i][link[i][j]], j);
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int dist[maxn];

queue<int> Q;
inline bool bfs(const int& s, const int& t) {
    memset(dist, 0, sizeof(dist));
    dist[s] = 1, Q.push(s);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = head[u]; i; i = G[i].nxt)
            if (G[i].val && !dist[G[i].to])
                dist[G[i].to] = dist[u] + 1, Q.push(G[i].to);
    }
    return dist[t];
}

int cur[maxn];
int dfs(const int& u, const int& t, int flow) {
    if (u == t || !flow)
        return flow;
    int ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (dist[G[i].to] == dist[u] + 1 && (tmp = dfs(G[i].to, t, min(flow, G[i].val)))) {
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
