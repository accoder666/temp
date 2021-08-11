#include <cstdio>
using namespace std;

const long long mod = 998244353;
const int maxn = 20;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
long long deg[2][maxn];
inline void AddEdge(const int&, const int&);
void dfs(const int&, const int& fa = 0);
inline long long inverse(long long);
long long ans[1 << maxn];
int count[1 << maxn];
struct func {
    long long a, b;
};
func f[maxn];
int state;

int main() {
    int n, Q, x;
    scanf("%d %d %d", &n, &Q, &x);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
        AddEdge(v, u);
    }
    for (int i = 1; i <= n; i++) deg[1][i] = inverse(deg[0][i]);
    int max = 1 << n;
    for (int i = 1; i < max; i++) count[i] = count[i >> 1] + (i & 1);
    for (state = 0; state < max; state++) {
        dfs(x);
        ans[state] = (count[state] & 1) ? f[x].b : mod - f[x].b;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < max; j++)
            if ((j >> i) & 1)
                ans[j] = (ans[j] + ans[j ^ (1 << i)]) % mod;
    int k, S, val;
    while (Q--) {
        scanf("%d", &k);
        S = 0;
        while (k--) {
            scanf("%d", &val);
            S |= 1 << (val - 1);
        }
        printf("%d\n", (ans[S] + mod) % mod);
    }
    return 0;
}

inline void AddEdge(const int& u, const int& v) {
    G[++cnt] = (edge){ v, head[u] };
    head[u] = cnt, deg[0][u]++;
    return;
}

void dfs(const int& u, const int& fa) {
    if ((1 << (u - 1)) & state) {
        f[u] = (func){ 0, 0 };
        return;
    }
    long long suma = 0, sumb = 0;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa) {
            dfs(G[i].to, u);
            suma = (suma + f[G[i].to].a) % mod;
            sumb = (sumb + f[G[i].to].b) % mod;
        }
    long long inv = inverse((mod + 1 - (deg[1][u] * suma) % mod) % mod);
    f[u] = (func){ (inv * deg[1][u]) % mod, (inv * ((1 + deg[1][u] * sumb) % mod)) % mod };
    return;
}

inline long long inverse(long long a) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * a % mod;
        a = a * a % mod, e >>= 1;
    }
    return ret;
}
