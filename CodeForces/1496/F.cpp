#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const long long mod = 998244353;
const int maxn = 610;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
long long ans[maxn][maxn];
int dist[maxn][maxn];
struct node {
    int u, d;
    inline bool operator<(const node& rhs) const { return d > rhs.d; }
};
priority_queue<node> Q;
int vis[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    while (m--) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a] }, head[a] = cnt;
        G[++cnt] = { a, head[b] }, head[b] = cnt;
    }
    memset(dist, 0x3f, sizeof(dist));
    int u;
    for (int i = 1; i <= n; i++) {
        Q.push({ i, dist[i][i] = 0 });
        while (!Q.empty()) {
            u = Q.top().u, Q.pop();
            if (vis[u] == i)
                continue;
            vis[u] = i;
            for (int j = head[u]; j; j = G[j].nxt)
                if (dist[i][G[j].to] > dist[i][u] + 1)
                    dist[i][G[j].to] = dist[i][u] + 1, Q.push({ G[j].to, dist[i][G[j].to] });
        }
    }
    int c;
    long long val;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            c = 0;
            for (int k = 1; k <= n; k++) c += (dist[i][k] + dist[j][k] == dist[i][j]);
            if (c != dist[i][j] + 1)
                continue;
            val = 1;
            for (int k = 1; k <= n; k++)
                if (dist[i][k] + dist[j][k] != dist[i][j]) {
                    c = 0;
                    for (int e = head[k]; e; e = G[e].nxt)
                        if (dist[k][G[e].to] + dist[i][G[e].to] == dist[i][k] &&
                            dist[k][G[e].to] + dist[j][G[e].to] == dist[j][k])
                            c++;
                    val = val * (long long)c % mod;
                    if (!val)
                        break;
                }
            ans[i][j] = ans[j][i] = val;
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) printf("%d ", ans[i][j]);
        printf("\n");
    }
    return 0;
}
