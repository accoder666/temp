#include <cstdio>
using namespace std;

const int maxn = 310;
const long long mod = 1000000007;
inline long long inverse(long long);
long long A[maxn][maxn];
int x[maxn], y[maxn];
int M[maxn][maxn];

int main() {
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    int lim = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= i; j++) x[++lim] = i, y[lim] = j, M[i][j] = lim;
    long long pi, pb;
    long long invm = inverse(m);
    int a, b;
    for (int i = 1; i <= lim; i++) {
        a = x[i], b = y[i];
        A[i][i] = -1;
        if (b == 1 || a == b)
            continue;
        pi = (m - a) * invm % mod * inverse(a + 1) % mod;
        pb = a * invm % mod * inverse(a - 1) % mod;
        if (a != m) {
            A[M[a + 1][b + 1]][i] = pi * b % mod;
            A[M[a + 1][b]][i] = pi * (a - b + 1) % mod;
        }
        for (int j = 1; j < b; j++) A[M[a - j][b - j]][i] = (A[M[a - j][b - j]][i] + pb) % mod;
        for (int j = 1; j <= i - b; j++) A[M[a - j][b]][i] = (A[M[a - j][b]][i] + pb) % mod;
    }
    A[M[n][k]][lim + 1] = -1;
    long long inv;
    for (int i = 1, r; i <= lim; i++) {
        r = i;
        while (r <= lim && !A[r][i]) r++;
        if (r != i)
            for (int j = 1; j <= lim + 1; j++) A[i][j] ^= A[r][j] ^= A[i][j] ^= A[r][j];
        inv = inverse(A[i][i]);
        for (int j = lim + 1; j > i; j--)
            for (int p = i + 1; p <= lim; p++) A[p][j] = (A[p][j] - A[p][i] * inv % mod * A[i][j]) % mod;
    }
    for (int i = lim; i; i--) {
        for (int j = i + 1; j <= lim; j++) A[i][lim + 1] = (A[i][lim + 1] - A[j][lim + 1] * A[i][j]) % mod;
        A[i][lim + 1] = A[i][lim + 1] * inverse(A[i][i]) % mod;
    }
    long long ans = A[M[1][1]][lim + 1];
    for (int i = 2; i <= m; i++) ans = (ans + i * (A[M[i][1]][lim + 1] + A[M[i][i]][lim + 1])) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}

inline long long inverse(long long v) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * v % mod;
        v = v * v % mod, e >>= 1;
    }
    return ret;
}
