#pragma GCC optimize(2)

#include <cstdio>
using namespace std;

const int maxn = 1010;
struct edge {
    int to, nxt;
};
edge G[maxn];
int head[maxn], cnt;
int dep[maxn];
int ans[maxn << 1], len;
void dfs1(const int&);
void dfs2(const int&, int&, const bool&);
int path[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, k, p;
    int val, u, v;
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) head[i] = 0;
        cnt = 0;
        for (int i = 2; i <= n; i++) {
            scanf("%d", &p);
            G[++cnt] = { i, head[p] }, head[p] = cnt;
            dep[i] = dep[p] + 1;
            if (dep[i] > val)
                val = i;
        }
        len = 0;
        dfs1(1);
        if (k <= val + 1) {
            k--, ans[++len] = u = 1;
            while (k) {
                ans[++len] = path[u], k--;
                v = u;
                u = path[v];
            }
        } else {
            k -= val;
            dfs2(1, k, true);
            u = ans[len];
            while (path[u]) {
                ans[++len] = path[u];
                v = u;
                u = path[v];
            }
        }
        printf("%d\n", len - 1);
        for (int i = 1; i <= len; i++) printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}

int l[maxn];
void dfs1(const int& u) {
    l[u] = 0;
    for (int i = head[u]; i; i = G[i].nxt) {
        dfs1(G[i].to);
        if (l[G[i].to] >= l[u] || (l[G[i].to] + 1 == l[u] && path[u] < G[i].to))
            l[u] = l[path[u] = G[i].to] + 1;
    }
    return;
}

void dfs2(const int& u, int& p, const bool& flag) {
    if (!p)
        return;
    ans[++len] = u, p--;
    if (!p)
        return;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!flag || G[i].to != path[u]) {
            dfs2(G[i].to, p, false);
            ans[++len] = u;
            if (!p)
                return;
        }
    if (u == 1 && p)
        p++, dfs2(path[u], p, true);
    return;
}
