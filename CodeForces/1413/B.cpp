#include <cstdio>
using namespace std;

const int maxn = 510;
int v[maxn][maxn], p[maxn];
int M[maxn * maxn];

int main() {
    int t, n, m, tmp;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) scanf("%d", v[i] + j), M[v[i][j]] = i;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                scanf("%d", &tmp);
                if (i == 1)
                    p[j] = M[tmp];
            }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) printf("%d ", v[p[i]][j]);
            printf("\n");
        }
    }
    return 0;
}
