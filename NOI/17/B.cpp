#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 510;
long double a[maxn][maxn];
struct edge {
    int from, to;
    long double val;
    inline bool operator<(const edge& rhs) const { return val > rhs.val; }
};
edge G[maxn * maxn];
int deg[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        G[i] = { u, v, 0 }, deg[u]++, deg[v]++;
    }
    for (int i = 1; i < n; i++) a[i][i] = 1;
    for (int i = 1; i <= m; i++) {
        if (G[i].from != n)
            a[G[i].to][G[i].from] = (long double)-1 / deg[G[i].from];
        if (G[i].to != n)
            a[G[i].from][G[i].to] = (long double)-1 / deg[G[i].to];
    }
    a[1][n] = 1;
    int r;
    long double tmp;
    for (int i = 1; i < n; i++) {
        r = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(a[r][i]) < fabs(a[j][i]))
                r = j;
        if (i != r)
            for (int j = 1; j <= n; j++) tmp = a[r][j], a[r][j] = a[i][j], a[i][j] = tmp;
        for (int j = i + 1; j < n; j++) {
            tmp = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++) a[j][k] -= tmp * a[i][k];
        }
    }
    for (int i = n - 1; i; i--) {
        for (int j = i + 1; j < n; j++) a[i][n] -= a[i][j] * a[j][n];
        a[i][n] /= a[i][i];
    }
    for (int i = 1; i <= m; i++) {
        if (G[i].from != n)
            G[i].val += a[G[i].from][n] / deg[G[i].from];
        if (G[i].to != n)
            G[i].val += a[G[i].to][n] / deg[G[i].to];
    }
    sort(G + 1, G + m + 1);
    long double ans = 0;
    for (int i = 1; i <= m; i++) ans += i * G[i].val;
    printf("%.3Lf\n", ans);
    return 0;
}
