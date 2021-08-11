#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2510;
struct edge {
    int from, to;
    long double val;
};
edge G[maxn];
long double v[maxn];
int p[maxn];
int vis[maxn], id[maxn];
long double a[maxn];
int b[maxn];

int main() {
    int n, m = 0, k, r;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%Lf %d", a + i, b + i);
        G[++m] = { n + 1, i, a[i] };
    }
    scanf("%d", &k);
    int x, y;
    long double z;
    while (k--) {
        scanf("%d %d %Lf", &x, &y, &z);
        G[++m] = { x, y, z };
        if (a[y] > z)
            a[y] = z;
    }
    r = ++n;
    long double ans = 0;
    for (int i = 1; i <= n; i++) ans += (b[i] - 1) * a[i];
    int cnt, u;
    while (true) {
        for (int i = 1; i <= n; i++) v[i] = INT_MAX;
        for (int i = 1; i <= m; i++)
            if (G[i].from != G[i].to && v[G[i].to] > G[i].val)
                v[G[i].to] = G[i].val, p[G[i].to] = G[i].from;
        for (int i = 1; i <= n; i++)
            if (i != r && v[i] == INT_MAX) {
                assert(false);
                break;
            }
        memset(vis, 0, sizeof(vis));
        memset(id, 0, sizeof(id));
        cnt = 0;
        for (int i = 1; i <= n; i++)
            if (i != r) {
                ans += v[i];
                u = i;
                while (vis[u] != i && !id[u] && u != r) vis[u] = i, u = p[u];
                if (!id[u] && u != r) {
                    cnt++;
                    do id[u] = cnt, u = p[u];
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
    printf("%.2Lf\n", ans);
    return 0;
}
