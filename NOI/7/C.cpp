#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 10010;
struct edge {
    int to, nxt, val, cost;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
inline void AddEdge(const int&, const int&, const int&, const int&);
inline void mcmf(const int&, const int&, int&, int&);

int main() {
    int n, m;
    int u, v, w;
    int flow, cost;
    int c = 0;
    while (scanf("%d %d", &n, &m) == 2 && (n || m)) {
        memset(head, 0, sizeof(head));
        cnt = 1;
        while (m--) {
            scanf("%d %d %d", &u, &v, &w);
            AddEdge(u + n + 1, v + 1, 1, w);
        }
        for (int i = 1; i <= n; i++) AddEdge(i, i + n, 2, 0);
        AddEdge((n << 1) + 1, 1, 2, 0);
        AddEdge(n, (n << 1) + 2, 2, 0);
        mcmf((n << 1) + 1, (n << 1) + 2, flow, cost);
        printf("Instance #%d: ", ++c);
        if (flow != 2)
            printf("Not possible\n");
        else
            printf("%d\n", cost);
    }
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val, const int& cost) {
    G[++cnt] = { v, head[u], val, cost }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0, -cost }, head[v] = cnt;
    return;
}

int d[maxn];
bool vis[maxn];
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

int cur[maxn];

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
