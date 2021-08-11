#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const long long mod = 1000000007;
const int maxn = 100010;
struct edge {
    int to, nxt;
    long long val;
    inline bool operator<(const edge& rhs) const { return val > rhs.val; }
};
edge G[maxn << 1];
int head[maxn], cnt;
inline void AddEdge(const int&, const int&);
long long p[maxn];
int n, m;
struct CMP {
    inline bool operator()(const long long& a, const long long& b) const { return a > b; }
};
CMP cmp;
long long dfs(const int&, const int&);

int main() {
    int t, u, v;
    long long ans;
    scanf("%d", &t);
    while (t--) {
        memset(head, 0, sizeof(head));
        memset(G, 0, sizeof(G));
        memset(p, 0, sizeof(p));
        cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) scanf("%lld", p + i);
        sort(p + 1, p + m + 1, cmp);
        dfs(1, -1);
        sort(G + 1, G + cnt + 1);
        ans = 0;
        for (int i = 1; i <= cnt; i++) {
            if (G[i].val == -1)
                break;
            ans = (ans + ((G[i].val % mod) * ((long long)(i <= m ? p[i] : 1) % mod)) % mod) % mod;
        }
        printf("%lld\n", ans % mod);
    }
    return 0;
}

inline void AddEdge(const int& u, const int& v) {
    G[++cnt] = { v, head[u], -1 };
    head[u] = cnt;
    return;
}

long long dfs(const int& u, const int& fa) {
    long long sum = 1, tmp;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa) {
            tmp = dfs(G[i].to, u);
            sum += tmp;
            G[i].val = tmp * (long long)(n - tmp);
        }
    return sum;
}
