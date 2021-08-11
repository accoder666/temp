#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 110;
struct edge {
    int to, nxt, val;
};
edge G[maxn * maxn << 1];
int head[maxn], cnt;
int deg[maxn];
long double A[maxn][maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int maxv = 0;
    int u, v, w;
    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { v, head[u], w }, head[u] = cnt, deg[u]++;
        if (u != v)
            G[++cnt] = { u, head[v], w }, head[v] = cnt, deg[v]++;
        if (w > maxv)
            maxv = w;
    }
    int r;
    long double ans = 0, tmp;
    for (int b = 1; b <= maxv; b <<= 1) {
        memset(A, 0, sizeof(A));
        for (int i = 1; i < n; i++) {
            A[i][i] = deg[i];
            for (int j = head[i]; j; j = G[j].nxt)
                if (G[j].val & b)
                    A[i][G[j].to]++, A[i][n + 1]++;
                else
                    A[i][G[j].to]--;
        }
        A[n][n] = 1;
        for (int i = 1; i <= n; i++) {
            r = i;
            for (int j = i + 1; j <= n; j++)
                if (fabsl(A[r][i]) < fabsl(A[j][i]))
                    r = j;
            if (r != i)
                for (int j = 1; j <= n + 1; j++) tmp = A[i][j], A[i][j] = A[r][j], A[r][j] = tmp;
            for (int j = i + 1; j <= n; j++) {
                tmp = A[j][i] / A[i][i];
                for (int k = i; k <= n + 1; k++) A[j][k] -= tmp * A[i][k];
            }
        }
        for (int i = n; i; i--) {
            for (int j = i + 1; j <= n + 1; j++) A[i][n + 1] -= A[i][j] * A[j][n + 1];
            A[i][n + 1] /= A[i][i];
        }
        ans += b * A[1][n + 1];
    }
    printf("%.3Lf\n", ans);
    return 0;
}
