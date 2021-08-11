#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 400010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
vector<int> b[maxn];
inline void AddEdge(const int&, const int&);
inline int dinic(const int&, const int&);
inline bool solve(const int&);
int ans[maxn][2];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) AddEdge(1, i);
    for (int i = n + 1; i < n << 1; i++) AddEdge(i, n << 1);
    int c, w;
    for (int i = 1; i < n; i++) {
        scanf("%d", &c);
        while (c--) {
            scanf("%d", &w);
            b[w].push_back(i);
            if (w != 1)
                AddEdge(w, n + i);
        }
    }
    if (dinic(1, n << 1) != n - 1 || !solve(1)) {
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i < n; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}

inline void AddEdge(const int& u, const int& v) {
    G[++cnt] = { v, head[u], 1 }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int d[maxn];

queue<int> Q;
inline bool bfs(const int& s, const int& t) {
    memset(d, 0, sizeof(d));
    Q.push(s);
    d[s] = 1;
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

int p[maxn];
bool vis[maxn];
inline bool solve(const int& s) {
    for (int i = 2; i <= n; i++)
        for (int j = head[i]; j; j = G[j].nxt)
            if (G[j].to != s && !G[j].val)
                p[G[j].to - n] = i;
    Q.push(s);
    int c = 0, u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int v : b[u])
            if (!vis[v]) {
                ans[v][0] = u, ans[v][1] = p[v];
                vis[v] = true, c++;
                Q.push(p[v]);
            }
    }
    return c == n - 1;
}
