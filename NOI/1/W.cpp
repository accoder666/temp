#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 400010, lg = 20;
struct edge {
    int u, v, l, a;
    inline bool operator<(const edge& rhs) const { return a > rhs.a; }
};
edge G[maxn << 1];
int find(const int&);
int fa[maxn << 1];
struct dij_edge {
    int to, nxt, val;
};
dij_edge tG[maxn << 1];
int head[maxn], cnt;
struct dij_node {
    int u, d;
    inline bool operator<(const dij_node& rhs) const { return d > rhs.d; }
};
priority_queue<dij_node> Q;
bool done[maxn];
int val[maxn << 1], dist[maxn << 1];
int anc[maxn << 1][lg];
int n;

int main() {
    int T;
    scanf("%d", &T);
    int m, q, k, s;
    int v, p, lastans;
    while (T--) {
        scanf("%d %d", &n, &m);
        memset(head, 0, sizeof(head));
        cnt = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %d %d", &G[i].u, &G[i].v, &G[i].l, &G[i].a);
            tG[++cnt] = { G[i].v, head[G[i].u], G[i].l };
            head[G[i].u] = cnt;
            tG[++cnt] = { G[i].u, head[G[i].v], G[i].l };
            head[G[i].v] = cnt;
        }
        Q.push({ 1, 0 });
        memset(done, false, sizeof(done));
        memset(dist, 0x3f, sizeof(dist));
        dist[1] = 0;
        int u;
        while (!Q.empty()) {
            u = Q.top().u;
            Q.pop();
            if (done[u])
                continue;
            done[u] = true;
            for (int i = head[u]; i; i = tG[i].nxt)
                if (dist[tG[i].to] > dist[u] + tG[i].val) {
                    dist[tG[i].to] = dist[u] + tG[i].val;
                    Q.push({ tG[i].to, dist[tG[i].to] });
                }
        }
        sort(G + 1, G + m + 1);
        for (int i = 1; i < n << 1; i++) fa[i] = i, val[i] = 0;
        memset(anc, 0, sizeof(anc));
        for (int i = 1, c = 0, fx, fy; i <= m && c != n - 1; i++) {
            fx = find(G[i].u), fy = find(G[i].v);
            if (fx == fy)
                continue;
            fa[fx] = fa[fy] = anc[fx][0] = anc[fy][0] = n + (++c);
            val[n + c] = G[i].a, dist[n + c] = min(dist[fx], dist[fy]);
        }
        for (int i = 1; i < lg; i++)
            for (int j = 1; j < n << 1; j++) anc[j][i] = anc[anc[j][i - 1]][i - 1];
        scanf("%d %d %d", &q, &k, &s);
        lastans = 0;
        while (q--) {
            scanf("%d %d", &v, &p);
            v = ((v + k * lastans - 1) % n) + 1, p = (p + k * lastans) % (s + 1);
            for (int i = lg - 1; i >= 0; i--)
                if (anc[v][i] && val[anc[v][i]] > p)
                    v = anc[v][i];
            printf("%d\n", (lastans = dist[v]));
        }
    }
    return 0;
}

int find(const int& u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
