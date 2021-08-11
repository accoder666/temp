#include <cstdio>
using namespace std;

const int maxn = 300010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
long long a[maxn], x;
void dfs(int);
int e[maxn], f, t;

int main() {
    int n, m;
    scanf("%d %d %lld", &n, &m, &x);
    long long sum = 0;
    for (int i = 1; i <= n; i++) scanf("%lld", a + i), sum += a[i];
    if (sum < (n - 1) * x) {
        printf("NO\n");
        return 0;
    }
    int x, y;
    while (m--) {
        scanf("%d %d", &x, &y);
        G[++cnt] = { y, head[x] }, head[x] = cnt;
        G[++cnt] = { x, head[y] }, head[y] = cnt;
    }
    f = 0, t = n;
    dfs(1);
    printf("YES\n");
    for (int i = 1; i < n; i++) printf("%d\n", e[i]);
    return 0;
}

bool vis[maxn];
void dfs(const int u) {
    vis[u] = true;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to]) {
            dfs(G[i].to);
            if (a[u] + a[G[i].to] >= x) {
                a[u] += a[G[i].to] - x;
                e[++f] = i >> 1;
            } else
                e[--t] = i >> 1;
        }
    return;
}
