#include <cstdio>
using namespace std;

const int maxn = 100010;
struct edge {
    int from, to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
int val[2][maxn], C[2];
void dfs(int, int, int v = 0);
inline long long cal(int);
int n, k;

int main() {
    freopen("atoranta.in", "r", stdin);
    freopen("atoranta.out", "w", stdout);
    scanf("%d", &n);
    int u, v, w;
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { u, v, head[u], w }, head[u] = cnt;
        G[++cnt] = { v, u, head[v], w }, head[v] = cnt;
    }
    long long ans = 0;
    k = -1;
    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
        for (int j = 1; j < n; j++)
            if (val[0][j] == 1)
                ans++;
    }
    ans >>= 1;
    printf("%lld\n", ans);
    int Q;
    scanf("%d", &Q);
    int x;
    while (Q--) {
        scanf("%d %d", &k, &x);
        dfs(G[k << 1].from, 0);
        dfs(G[k << 1].to, 1);
        ans += cal(x) - cal(G[k << 1].val);
        G[k << 1].val = G[(k << 1) ^ 1].val = x;
        printf("%lld\n", ans);
    }
    return 0;
}

int gcd(const int x, const int y) {
    if (!y)
        return x;
    return gcd(y, x % y);
}

bool vis[maxn];
void dfs(int u, int p, const int v) {
    if (!v) {
        C[p] = 0;
        for (int i = 1; i <= n; i++) vis[i] = false;
    } else
        val[p][++C[p]] = v;
    vis[u] = true;
    for (int i = head[u]; i; i = G[i].nxt)
        if (i >> 1 != k && !vis[G[i].to])
            dfs(G[i].to, p, gcd(G[i].val, v));
    return;
}

inline long long cal(const int v) {
    long long ret = 0;
    for (int i = 1; i <= C[0]; i++)
        if (gcd(val[0][i], v) == 1)
            ret++;
    for (int i = 1; i <= C[1]; i++)
        if (gcd(val[1][i], v) == 1)
            ret++;
    for (int i = 1; i <= C[0]; i++)
        if (val[0][i] != 1)
            for (int j = 1; j <= C[1]; j++)
                if (val[1][j] != 1 && gcd(v, gcd(val[0][i], val[1][j])) == 1)
                    ret++;
    return ret;
}
