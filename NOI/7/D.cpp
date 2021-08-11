#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const long long lim = 1e15;
const int maxn = 100010;
struct edge {
    int to, nxt;
    long long val;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
edge G2[maxn << 1];
int head2[maxn], cnt2;
struct node {
    int u;
    long long d;
    inline bool operator<(const node& rhs) const { return d > rhs.d; }
};
priority_queue<node> q;
long long dist[maxn];
bool f[maxn];
inline void AddEdge(const int&, const int&, const long long&);
inline long long dinic(const int&, const int&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v;
    long long w;
    while (m--) {
        scanf("%d %d %lld", &u, &v, &w);
        G2[++cnt2] = { v, head2[u], w }, head2[u] = cnt2;
        G2[++cnt2] = { u, head2[v], w }, head2[v] = cnt2;
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0, q.push({ 1, 0 });
    while (!q.empty()) {
        u = q.top().u, q.pop();
        if (f[u])
            continue;
        f[u] = true;
        for (int i = head2[u]; i; i = G2[i].nxt)
            if (dist[G2[i].to] > dist[u] + G2[i].val) {
                dist[G2[i].to] = dist[u] + G2[i].val;
                q.push({ G2[i].to, dist[G2[i].to] });
            }
    }
    AddEdge(0, 1, lim);
    AddEdge(n << 1, n << 1 | 1, lim);
    int c;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c);
        if (i != 1 && i != n)
            AddEdge(i, i + n, c);
        else
            AddEdge(i, i + n, lim);
    }
    for (int i = 1; i <= n; i++)
        for (int j = head2[i]; j; j = G2[j].nxt)
            if (dist[G2[j].to] == dist[i] + G2[j].val)
                AddEdge(i + n, G2[j].to, lim);
    printf("%lld\n", dinic(0, n << 1 | 1));
    return 0;
}

inline void AddEdge(const int& u, const int& v, const long long& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int d[maxn];

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

int cur[maxn];
long long dfs(const int& s, const int& u, const int& t, long long flow) {
    if (u == t || !flow)
        return flow;
    long long ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(s, G[i].to, t, min(flow, G[i].val)))) {
            ret += tmp, flow -= tmp, G[i].val -= tmp, G[i ^ 1].val += tmp;
            if (!flow)
                break;
        }
    return ret;
}

inline long long dinic(const int& s, const int& t) {
    long long ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, s, t, lim);
    }
    return ret;
}
