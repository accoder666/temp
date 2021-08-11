#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxl = 1000, maxx = 20;
const long long mod = 1000000007;
inline void solve(long long[maxx + 10][maxn]);
long long C[maxx + 10][maxn], F[maxx + 10][maxn];
struct query {
    int x;
    long long y;
};
query Q[maxl + 10];
int n, cnt;

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int m;
    scanf("%d %d", &n, &m);
    C[0][1] = 1;
    solve(C);
    for (int i = 1; i <= n; i++) scanf("%lld", F[0] + i);
    solve(F);
    long long ans;
    int o, x, y;
    int lim = sqrtl((long double)10 * m);
    while (m--) {
        scanf("%d %d %d", &o, &x, &y);
        switch (o) {
            case 1:
                Q[++cnt] = { x, y - F[0][x] }, F[0][x] = y;
                if (cnt == lim)
                    cnt = 0, solve(F);
                break;
            case 2:
                ans = F[x][y];
                if (x)
                    for (int i = 1; i <= cnt; i++)
                        if (y >= Q[i].x)
                            ans = (ans + C[x][y - Q[i].x + 1] * Q[i].y) % mod;
                printf("%lld\n", (ans + mod) % mod);
                break;
            default:
                break;
        }
    }
    return 0;
}

inline void solve(long long A[maxx + 10][maxn]) {
    for (int i = 1; i <= maxx; i++)
        for (int j = 1; j <= n; j++) {
            A[i][j] = A[i - 1][j] + A[i][j - 1];
            if (A[i][j] >= mod)
                A[i][j] -= mod;
        }
    return;
}
