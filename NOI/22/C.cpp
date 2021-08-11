#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 20, maxm = 200;
const long long mod = 1000000007;
long long A[maxn][maxn];
struct node {
    int m, u[maxm], v[maxm];
};
node t[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &t[i].m);
        for (int j = 1; j <= t[i].m; j++) scanf("%d %d", t[i].u + j, t[i].v + j);
    }
    int lim = 1 << (n - 1), u, v;
    long long ans = 0, det, tmp;
    for (int i = 1; i < lim; i++) {
        memset(A, 0, sizeof(A));
        for (int j = 1; j < n; j++)
            if (i & (1 << (j - 1)))
                for (int k = 1; k <= t[j].m; k++) {
                    u = t[j].u[k], v = t[j].v[k];
                    A[u][u]++, A[v][v]++, A[u][v]--, A[v][u]--;
                }
        det = 1;
        for (int j = 1; j < n; j++) {
            for (int k = j + 1; k < n; k++)
                while (A[k][j]) {
                    tmp = A[j][j] / A[k][j];
                    for (int l = j; l < n; l++) A[j][l] = (A[j][l] - tmp * A[k][l]) % mod;
                    for (int l = j; l < n; l++) A[j][l] ^= A[k][l] ^= A[j][l] ^= A[k][l];
                    det = -det;
                }
            det = det * A[j][j] % mod;
        }
        ans = (ans + ((n - __builtin_popcount(i)) & 1 ? det : -det)) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
