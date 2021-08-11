#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 100010;
struct node {
    int x, y, a, b;
    inline bool operator<(const node& rhs) const { return a == rhs.a ? b < rhs.b : a < rhs.a; }
};
node t[maxn];
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
bool vis[maxn];
int dist[maxn];
queue<int> Q;
int find(const int&);
int fa[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d %d %d %d", &t[i].x, &t[i].y, &t[i].a, &t[i].b);
    sort(t + 1, t + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    int p;
    for (p = 1; p <= m; p++) {
        fa[find(t[p].x)] = find(t[p].y);
        if (find(1) == find(n))
            break;
        G[++cnt] = { t[p].x, head[t[p].y], t[p].b }, head[t[p].y] = cnt;
        G[++cnt] = { t[p].y, head[t[p].x], t[p].b }, head[t[p].x] = cnt;
    }
    if (p == m + 1) {
        printf("-1\n");
        return 0;
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0, vis[1] = true, Q.push(1);
    int u, ans = INT_MAX;
    for (p--; p <= m; p++) {
        G[++cnt] = { t[p].x, head[t[p].y], t[p].b }, head[t[p].y] = cnt;
        G[++cnt] = { t[p].y, head[t[p].x], t[p].b }, head[t[p].x] = cnt;
        Q.push(t[p].x), Q.push(t[p].y);
        vis[t[p].x] = vis[t[p].y] = true;
        while (!Q.empty()) {
            u = Q.front();
            Q.pop();
            vis[u] = false;
            for (int i = head[u]; i; i = G[i].nxt)
                if (dist[G[i].to] > max(dist[u], G[i].val)) {
                    dist[G[i].to] = max(dist[u], G[i].val);
                    if (!vis[G[i].to])
                        vis[G[i].to] = true, Q.push(G[i].to);
                }
        }
        ans = min(ans, dist[n] + t[p].a);
    }
    printf("%d\n", ans);
    return 0;
}

int find(const int& u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
