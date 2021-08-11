#include <cstdio>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt, val;
    int p, coeff;
};
edge G[maxn * 6];
int head[maxn << 1], cnt;
int deg[maxn << 1];
void dfs(const int&);
int ans[maxn];

int main() {
    int n;
    scanf("%d", &n);
    int f, c = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f);
        if (f == -1)
            f = 0;
        c++;
        G[++cnt] = { f, head[i], c, 0, 0 }, head[i] = cnt;
        G[++cnt] = { i, head[f], c, 0, 0 }, head[f] = cnt;
        deg[i]++, deg[f]++;
    }
    for (int i = n + 1; i <= n << 1; i++) {
        scanf("%d", &f);
        if (f == -1)
            f = 0;
        else
            f += n;
        c++;
        G[++cnt] = { f, head[i], c, 0, 0 }, head[i] = cnt;
        G[++cnt] = { i, head[f], c, 0, 0 }, head[f] = cnt;
        deg[i]++, deg[f]++;
    }
    for (int i = 1; i <= n; i++)
        if ((deg[i] ^ deg[n + i]) & 1) {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1) {
            c++;
            G[++cnt] = { i + n, head[i], c, i, 1 }, head[i] = cnt;
            G[++cnt] = { i, head[i + n], c, i, -1 }, head[i + n] = cnt;
        }
    dfs(0);
    printf("POSSIBLE\n");
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}

bool vis[maxn * 3];
void dfs(const int& u) {
    for (int& i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].val]) {
            vis[G[i].val] = true;
            ans[G[i].p] = G[i].coeff;
            dfs(G[i].to);
        }
    return;
}
