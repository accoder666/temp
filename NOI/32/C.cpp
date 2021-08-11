#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 200010;
struct edge {
    int to, nxt;
    double val;
};
edge G[maxn << 1], G2[maxn << 1];
int head[maxn], cnt;
int head2[maxn], cnt2;
struct node {
    int u;
    double v;
    inline bool operator<(const node& rhs) const { return v > rhs.v; }
};
priority_queue<node> Q;
double dist[maxn];
bool flag[maxn];
bool vis[maxn];
void dfs(const int&);
bool tree[maxn];
int fa[maxn];
struct heap_node {
    int lc, rc, dist;
    node u;
};
heap_node h[maxn * 20];
int r[maxn], c;
inline int newnode(const node&);
int merge(const int&, const int&);
void dfs2(const int&);

int main() {
    int n, m;
    double E;
    scanf("%d %d %lf", &n, &m, &E);
    int s, t;
    double e;
    while (m--) {
        scanf("%d %d %lf", &s, &t, &e);
        if (s == n)
            continue;
        G[++cnt] = { t, head[s], e }, head[s] = cnt;
        G2[++cnt2] = { s, head2[t], e }, head2[t] = cnt2;
    }
    node u;
    memset(dist, 0x7f, sizeof(dist));
    Q.push({ n, 0 }), dist[n] = 0;
    while (!Q.empty()) {
        u = Q.top(), Q.pop();
        if (flag[u.u])
            continue;
        flag[u.u] = true;
        for (int i = head2[u.u]; i; i = G2[i].nxt)
            if (dist[G2[i].to] > dist[u.u] + G2[i].val)
                dist[G2[i].to] = dist[u.u] + G2[i].val, Q.push({ G2[i].to, dist[G2[i].to] });
    }
    dfs(n);
    for (int i = 1; i <= n; i++)
        if (flag[i])
            for (int j = head[i]; j; j = G[j].nxt)
                if (!tree[j] && flag[G[j].to])
                    r[i] = merge(r[i], newnode({ G[j].to, dist[G[j].to] + G[j].val - dist[i] }));
    memset(vis, false, sizeof(vis));
    dfs2(n);
    if (r[1])
        Q.push({ r[1], dist[1] + h[r[1]].u.v });
    int ans = 1;
    E -= dist[1];
    while (!Q.empty()) {
        u = Q.top(), Q.pop();
        if (u.v > E)
            break;
        ans++, E -= u.v;
        if (h[u.u].lc)
            Q.push({ h[u.u].lc, u.v - h[u.u].u.v + h[h[u.u].lc].u.v });
        if (h[u.u].rc)
            Q.push({ h[u.u].rc, u.v - h[u.u].u.v + h[h[u.u].rc].u.v });
        if (r[h[u.u].u.u])
            Q.push({ r[h[u.u].u.u], u.v + h[r[h[u.u].u.u]].u.v });
    }
    printf("%d\n", ans);
    return 0;
}

void dfs(const int& u) {
    vis[u] = true;
    for (int i = head2[u]; i; i = G2[i].nxt)
        if (!vis[G2[i].to] && dist[G2[i].to] == dist[u] + G2[i].val)
            tree[i] = true, fa[G2[i].to] = u, dfs(G2[i].to);
    return;
}

inline int newnode(const node& u) {
    h[++c].u = u;
    return c;
}

int merge(const int& x, const int& y) {
    if (!x)
        return y;
    if (!y)
        return x;
    if (h[x].u < h[y].u)
        return merge(y, x);
    int ret = ++c;
    h[ret].u = h[x].u;
    h[ret].lc = h[x].lc;
    h[ret].rc = merge(h[x].rc, y);
    if (h[h[ret].lc].dist < h[h[ret].rc].dist)
        swap(h[ret].lc, h[ret].rc);
    h[ret].dist = h[h[ret].rc].dist + 1;
    return ret;
}

void dfs2(const int& u) {
    vis[u] = true;
    if (fa[u])
        r[u] = merge(r[u], r[fa[u]]);
    for (int i = head2[u]; i; i = G2[i].nxt)
        if (!vis[G2[i].to] && fa[G2[i].to] == u)
            dfs2(G2[i].to);
    return;
}
