#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const long long mod = 1000000007;
const long double pi2 = 2.0 * acos(-1);
const int maxn = 100010;
struct complex {
    long double r, i;
    inline complex operator+(const complex& x) const { return { r + x.r, i + x.i }; }
    inline complex operator-(const complex& x) const { return { r - x.r, i - x.i }; }
    inline complex operator*(const complex& x) const { return { r * x.r - i * x.i, r * x.i + i * x.r }; }
};
complex a[maxn << 2], b[maxn << 2];
inline void fft(const int&, complex*, const bool&);
int t[maxn << 2];
char S[maxn], tmp[maxn << 1];
int v[maxn << 1];

int main() {
    scanf("%s", S);
    int n = strlen(S), l = 1;
    while (l < n) l <<= 1;
    l <<= 1;
    for (int i = 0; i < l; i++) t[i] = (t[i >> 1] >> 1) | ((i & 1) ? l >> 1 : 0);
    for (int i = 0; i < n; i++) (S[i] == 'a' ? a[i] : b[i]).r = 1;
    fft(l, a, true);
    fft(l, b, true);
    for (int i = 0; i < l; i++) a[i] = a[i] * a[i] + b[i] * b[i];
    fft(l, a, false);
    long long ans = 0, pow, base, e;
    for (int i = 0; i < l; i++) {
        pow = 1, base = 2, e = ((int)roundl(a[i].r) + 1) >> 1;
        while (e) {
            if (e & 1)
                pow = pow * base % mod;
            base = base * base % mod, e >>= 1;
        }
        ans += pow - 1;
        if (ans >= mod)
            ans -= mod;
    }
    for (int i = 0; i < n; i++) tmp[i << 1] = '#', tmp[i << 1 | 1] = S[i];
    tmp[n << 1] = '#';
    int m = 0, r = 0;
    for (int i = 0; i <= n << 1; i++) {
        v[i] = (i < r ? min(v[(m << 1) - i], r - i) : 1);
        while (i + v[i] <= n << 1 && v[i] <= i && tmp[i + v[i]] == tmp[i - v[i]]) v[i]++;
        if (i + v[i] > r)
            m = i, r = i + v[i];
        ans -= v[i] >> 1;
        if (ans < 0)
            ans += mod;
    }
    printf("%lld\n", ans);
    return 0;
}

inline void fft(const int& l, complex* C, const bool& flag) {
    complex w, pow, tmp;
    for (int i = 0; i < l; i++)
        if (i < t[i])
            tmp = C[i], C[i] = C[t[i]], C[t[i]] = tmp;
    for (int p = 2; p <= l; p <<= 1) {
        w = { cos(pi2 / p), sin(pi2 / p) * (flag ? 1 : -1) };
        for (int k = 0; k < l; k += p) {
            pow = { 1, 0 };
            for (int i = k; i < k + (p >> 1); i++) {
                tmp = pow * C[(p >> 1) + i];
                C[(p >> 1) + i] = C[i] - tmp, C[i] = C[i] + tmp;
                pow = pow * w;
            }
        }
    }
    if (!flag)
        for (int i = 0; i < l; i++) C[i].r /= l, C[i].i /= l;
    return;
}
