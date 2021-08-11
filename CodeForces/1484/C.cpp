#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 400010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
inline void AddEdge(const int&, const int&, const int&);
inline int dinic(const int&, const int&);
int c[maxn];
int n, m;

int main() {
    int t;
    scanf("%d", &t);
    int lim, k, f;
    int ans;
    while (t--) {
        scanf("%d %d", &n, &m);
        lim = (int)ceill((long double)m / 2);
        cnt = 1;
        for (int i = 1; i <= n; i++) AddEdge(n + m + 1, i, lim);
        for (int i = 1; i <= m; i++) {
            scanf("%d", &k);
            while (k--) {
                scanf("%d", &f);
                AddEdge(f, n + i, 1);
            }
            AddEdge(n + i, n + m + 2, 1);
        }
        ans = dinic(n + m + 1, n + m + 2);
        if (ans == m) {
            printf("YES\n");
            for (int i = 1; i <= n; i++)
                for (int j = head[i]; j; j = G[j].nxt)
                    if (G[j].to != n + m + 1 && !G[j].val)
                        c[G[j].to - n] = i;
            for (int i = 1; i <= m; i++) printf("%d ", c[i]);
            printf("\n");
        } else
            printf("NO\n");
        memset(head, 0, sizeof(int) * (n + m + 5));
    }
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
    memset(dist, 0, sizeof(int) * (n + m + 5));
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
        memcpy(cur, head, sizeof(int) * (n + m + 5));
        ret += dfs(s, t, INT_MAX);
    }
    return ret;
}
