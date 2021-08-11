#include <climits>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 60, maxm = 2510;
struct edge {
    int from, to, val;
};
edge G[maxm];
inline int Edmonds(int, const int&);
int a[maxn], b[maxn];
bool flag[maxn];
int p[maxn];

int main() {
    freopen("pl.in", "r", stdin);
    freopen("pl.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    int m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) G[++m] = { i == j ? n + 1 : j, i, a[i] ^ b[j] };
    int ans = Edmonds(n + 1, m);
    int u;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!flag[j]) {
                flag[j] = true, p[i] = j;
                m = 0;
                for (int k = 1; k <= i; k++) {
                    u = 1;
                    for (int l = 2; l <= k; l++)
                        if ((a[p[k]] ^ b[p[l]]) < (a[p[k]] ^ b[p[u]]))
                            u = l;
                    G[++m] = { k == u ? n + 1 : p[u], p[k], a[p[k]] ^ b[p[u]] };
                }
                for (int k = 1; k <= n; k++)
                    if (!flag[k])
                        for (int l = 1; l <= n; l++) G[++m] = { k == l ? n + 1 : l, k, a[k] ^ b[l] };
                if (Edmonds(n + 1, m) == ans)
                    break;
                flag[j] = false;
            }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) printf("%d ", p[i]);
    printf("\n");
    return 0;
}

int v[maxn], pre[maxn];
int vis[maxn], id[maxn];
inline int Edmonds(int n, const int& m) {
    int r = n, ret = 0;
    int cnt, u;
    while (true) {
        for (int i = 1; i <= n; i++) v[i] = INT_MAX;
        for (int i = 1; i <= m; i++)
            if (G[i].from != G[i].to && v[G[i].to] > G[i].val)
                v[G[i].to] = G[i].val, pre[G[i].to] = G[i].from;
        for (int i = 1; i <= n; i++)
            if (i != r && v[i] == INT_MAX)
                return -1;
        memset(vis, 0, sizeof(vis));
        memset(id, 0, sizeof(id));
        cnt = 0;
        for (int i = 1; i <= n; i++)
            if (i != r) {
                ret += v[i], u = i;
                while (vis[u] != i && !id[u] && u != r) vis[u] = i, u = pre[u];
                if (!id[u] && u != r) {
                    cnt++;
                    do id[u] = cnt, u = pre[u];
                    while (id[u] != cnt);
                }
            }
        if (!cnt)
            break;
        for (int i = 1; i <= n; i++)
            if (!id[i])
                id[i] = ++cnt;
        for (int i = 1; i <= m; i++) {
            if (id[G[i].from] != id[G[i].to])
                G[i].val -= v[G[i].to];
            G[i].from = id[G[i].from];
            G[i].to = id[G[i].to];
        }
        n = cnt, r = id[r];
    }
    return ret;
}
