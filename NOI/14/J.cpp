#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int dx[] = { 0, 0, 1, -1 }, dy[] = { 1, -1, 0, 0 };
const int maxn = 50, maxm = 350000;
struct edge {
    int to, nxt, val;
};
edge G[maxm << 1];
int head[maxm], cnt = 1;
int id[maxn][maxn][maxn];
inline void AddEdge(const int&, const int&, const int&);
inline int dinic(const int&, const int&);

int main() {
    int p, q, r, d;
    scanf("%d %d %d", &p, &q, &r);
    scanf("%d", &d);
    int c = 0;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= q; k++) id[i][j][k] = ++c;
    int v;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= q; k++) {
                scanf("%d", &v);
                AddEdge(id[i - 1][j][k], id[i][j][k], v);
            }
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= q; j++) AddEdge(id[r][i][j], p * q * r + 1, INT_MAX);
    int x, y;
    for (int i = d + 1; i <= r; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= q; k++)
                for (int l = 0; l < 4; l++) {
                    x = j + dx[l], y = k + dy[l];
                    if (x > 0 && x <= p && y > 0 && y <= q)
                        AddEdge(id[i][j][k], id[i - d][x][y], INT_MAX);
                }
    printf("%d\n", dinic(0, p * q * r + 1));
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int dist[maxm];

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

int cur[maxm];
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
