#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
void dfs1(int);
void dfs2(int, int, int);
bool ans[maxn];
int dp[maxn];

int main() {
    int w, t;
    scanf("%d %d", &w, &t);
    int n;
    int a, b;
    while (t--) {
        cnt = 0;
        memset(head, 0, sizeof(head));
        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &a, &b);
            G[++cnt] = { b, head[a] }, head[a] = cnt;
            G[++cnt] = { a, head[b] }, head[b] = cnt;
        }
        dfs1(1);
        ans[1] = !dp[1];
        dfs2(1, 0, 0);
        if (w == 3)
            putchar(ans[1] + '0');
        else
            for (int i = 1; i <= n; i++) putchar(ans[i] + '0');
        printf("\n");
    }
    return 0;
}

int fa[maxn], siz[maxn], son[maxn];
void dfs1(const int u) {
    siz[u] = 1, son[u] = 0;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dfs1(G[i].to);
            siz[u] += siz[G[i].to];
            if (siz[G[i].to] > siz[son[u]])
                son[u] = G[i].to;
        }
    if (son[u]) {
        if (dp[son[u]] + 1 <= siz[u] - siz[son[u]] - 1)
            dp[u] = (siz[u] - 1) & 1;
        else
            dp[u] = dp[son[u]] + 1 - (siz[u] - siz[son[u]] - 1);
    } else
        dp[u] = 0;
    return;
}

void dfs2(const int u, const int v, const int sum) {
    int p;
    if (u != 1) {
        p = (siz[son[u]] > siz[v] ? son[u] : v);
        if (dp[p] + 1 <= (siz[u] + sum) - siz[p] - 1)
            ans[u] = !(((siz[u] + sum) - 1) & 1);
        else
            ans[u] = !(dp[p] + 1 - ((siz[u] + sum) - siz[p] - 1));
    }
    int se = 0;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u] && siz[G[i].to] > siz[se])
            se = G[i].to;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            p = (G[i].to == son[u] ? se : son[u]);
            dfs2(G[i].to, siz[v] >= siz[p] ? v : p, sum + siz[u] - siz[G[i].to] - 1);
        }
    return;
}
