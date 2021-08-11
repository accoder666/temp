#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 610;
long long dist[maxn << 1][maxn << 1];
struct edge {
    int u, v;
    long long w;
};
edge G[maxn * maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %lld", &G[i].u, &G[i].v, &G[i].w);
        dist[G[i].u][G[i].v] = dist[G[i].v][G[i].u] = dist[G[i].u + n][G[i].v + n] =
            dist[G[i].v + n][G[i].u + n] = G[i].w;
    }
    int q;
    scanf("%d", &q);
    int u, v;
    long long l;
    while (q--) scanf("%d %d %lld", &u, &v, &l), dist[u][v + n] = dist[v][u + n] = -l;
    for (int k = 1; k <= n << 1; k++)
        for (int i = 1; i <= n << 1; i++)
            for (int j = 1; j <= n << 1; j++)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    int ans = 0;
    for (int i = 1; i <= m; i++)
        if (dist[G[i].u][G[i].v + n] + G[i].w <= 0)
            ans++;
    printf("%d\n", ans);
    return 0;
}
