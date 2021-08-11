#include <cstdio>
using namespace std;

const long long mod = 1000000000;
const int maxn = 20, maxm = 100;
long long A[maxm][maxm];
int id[maxn][maxn];
char M[maxn][maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%s", M[i] + 1);
        for (int j = 1; j <= m; j++)
            if (M[i][j] == '.')
                id[i][j] = ++cnt;
    }
    int tx, ty, u, v;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++)
            if (M[x][y] == '.') {
                tx = x + 1, ty = y, u = id[x][y], v = id[tx][ty];
                if (v)
                    A[u][u]++, A[v][v]++, A[u][v]--, A[v][u]--;
                tx = x, ty = y + 1, u = id[x][y], v = id[tx][ty];
                if (v)
                    A[u][u]++, A[v][v]++, A[u][v]--, A[v][u]--;
            }
    long long ans = 1, tmp;
    for (int i = 1; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++)
            while (A[j][i]) {
                tmp = A[i][i] / A[j][i];
                for (int k = i; k < cnt; k++) A[i][k] = (A[i][k] - tmp * A[j][k]) % mod;
                for (int k = i; k < cnt; k++) A[i][k] ^= A[j][k] ^= A[i][k] ^= A[j][k];
                ans = -ans;
            }
        ans = ans * A[i][i] % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
