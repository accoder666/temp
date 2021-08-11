#include <cmath>
#include <cstdio>
using namespace std;

const long double pi2 = 2 * acosl(-1);

const int maxn = 10010;
struct complex {
    long double r, i;
    inline complex operator+(const complex rhs) const { return { r + rhs.r, i + rhs.i }; }
    inline complex operator-(const complex rhs) const { return { r - rhs.r, i - rhs.i }; }
    inline complex operator*(const complex rhs) const {
        return { r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r };
    }
};
void solve(int, int, int, int);
int f[maxn << 2], g[maxn << 2];
int dp[maxn << 2];
int t[maxn << 2];

int main() {
    int m, p, a, o, s, u;
    scanf("%d %d %d %d %d %d", &m, &p, &a, &o, &s, &u);
    for (int i = 1; i <= m; i++) dp[i] = f[i] = g[i] = ((o * i + s) % p * i + u) % p;
    int l = 1;
    while (l <= m) l <<= 1;
    l <<= 1;
    for (int i = 0; i < l; i++) t[i] = (t[i >> 1] >> 1) | ((i & 1) ? (l >> 1) : 0);
    solve(a < m ? a : m, l, p, m);
    printf("%d\n", dp[m]);
    return 0;
}

inline void fft(const int l, complex* C, const bool flag) {
    complex w, pow, tmp;
    for (int i = 0; i < l; i++)
        if (i < t[i])
            tmp = C[i], C[i] = C[t[i]], C[t[i]] = tmp;
    for (int p = 2; p <= l; p <<= 1) {
        w = { cosl(pi2 / p), (flag ? 1 : -1) * sinl(pi2 / p) };
        for (int i = 0; i < l; i += p) {
            pow = { 1, 0 };
            for (int j = i; j < i + (p >> 1); j++) {
                tmp = pow * C[j + (p >> 1)];
                C[j + (p >> 1)] = C[j] - tmp, C[j] = C[j] + tmp;
                pow = pow * w;
            }
        }
    }
    if (!flag)
        for (int i = 0; i < l; i++) C[i].r /= l, C[i].i /= l;
    return;
}

inline void mul(const int* x, const int* y, int* ret, const int l, const int p, const int m) {
    static complex tmp1[maxn << 2], tmp2[maxn << 2];
    for (int i = 0; i < l; i++) tmp1[i] = { (long double)x[i], 0 }, tmp2[i] = { (long double)y[i], 0 };
    fft(l, tmp1, true);
    fft(l, tmp2, true);
    for (int i = 0; i < l; i++) tmp1[i] = tmp1[i] * tmp2[i];
    fft(l, tmp1, false);
    for (int i = 1; i <= m; i++) ret[i] = (int)roundl(tmp1[i].r) % p;
    return;
}

int tmp[maxn << 2];
void solve(const int k, const int l, const int p, const int m) {
    if (k == 1)
        return;
    solve(k >> 1, l, p, m);
    mul(dp, g, tmp, l, p, m);
    for (int i = 0; i < l; i++) {
        dp[i] += tmp[i];
        if (dp[i] >= p)
            dp[i] -= p;
    }
    mul(g, g, g, l, p, m);
    if (k & 1) {
        mul(f, g, g, l, p, m);
        for (int i = 0; i < l; i++) {
            dp[i] += g[i];
            if (dp[i] >= p)
                dp[i] -= p;
        }
    }
    return;
}
