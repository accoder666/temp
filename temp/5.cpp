#include <cstdio>
using namespace std;

const int maxn = 10010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
int k[maxn];
bool ans[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v, w;
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    for (int i = 1; i <= m; i++) scanf("%d", k + i);
    solve(1, n);
    for (int i = 1; i <= n; i++) printf(ans[i] ? "AYE\n" : "NAY\n");
}
