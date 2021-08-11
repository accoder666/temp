#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 200, maxe = 25010;
struct edge {
    int to, nxt, val, cost;
};
edge G[maxe << 1];
int head[maxe], cnt = 1;
int dist[maxn][maxn];
inline void AddEdge(const int&, const int&, const int&, const int&);
inline void mcmf(const int&, const int&, int&, int&);

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k), n++;
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;
    int a, b, l;
    while (m--) {
        scanf("%d %d %d", &a, &b, &l), a++, b++;
        if (dist[a][b] > l)
            dist[a][b] = dist[b][a] = l;
    }
    for (int p = 1; p <= n; p++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if ((p < i || p < j) && dist[i][j] > dist[i][p] + dist[p][j])
                    dist[i][j] = dist[i][p] + dist[p][j];
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (dist[i][j] != dist[0][0])
                AddEdge(i, j + n, k, dist[i][j]);
    AddEdge(n << 1 | 1, 1, k, 0);
    for (int i = 1; i <= n; i++) {
        AddEdge(i + n, (n + 1) << 1, 1, 0);
        if (i != 1)
            AddEdge(n << 1 | 1, i, 1, 0);
    }
    int flow, cost;
    mcmf(n << 1 | 1, (n + 1) << 1, flow, cost);
    printf("%d\n", cost);
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val, const int& cost) {
    G[++cnt] = { v, head[u], val, cost }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0, -cost }, head[v] = cnt;
    return;
}

int d[maxe];
bool vis[maxe];
queue<int> Q;
inline bool spfa(const int& s, const int& t) {
    memset(d, 0x3f, sizeof(d));
    d[s] = 0, vis[s] = true, Q.push(s);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = G[i].nxt)
            if (G[i].val && d[G[i].to] > d[u] + G[i].cost) {
                d[G[i].to] = d[u] + G[i].cost;
                if (!vis[G[i].to]) {
                    vis[G[i].to] = true;
                    Q.push(G[i].to);
                }
            }
    }
    return d[t] != d[0];
}

int cur[maxe];

int dfs(const int& u, const int& t, int flow) {
    if (u == t || !flow)
        return flow;
    int ret = 0, tmp;
    vis[u] = true;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && d[G[i].to] == d[u] + G[i].cost && (tmp = dfs(G[i].to, t, min(flow, G[i].val)))) {
            ret += tmp, G[i].val -= tmp, G[i ^ 1].val += tmp, flow -= tmp;
            if (!flow)
                break;
        }
    vis[u] = false;
    return ret;
}

inline void mcmf(const int& s, const int& t, int& flow, int& cost) {
    flow = cost = 0;
    int tmp;
    while (spfa(s, t)) {
        memcpy(cur, head, sizeof(cur));
        tmp = dfs(s, t, INT_MAX);
        flow += tmp, cost += tmp * d[t];
    }
    return;
}
