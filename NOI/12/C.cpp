#include <cmath>
#include <cstdio>
using namespace std;

const long double pi2 = 2.0 * acos(-1);
const int maxn = 100010;
struct complex {
    long double r, i;
    inline complex operator+(const complex& x) const { return { r + x.r, i + x.i }; }
    inline complex operator-(const complex& x) const { return { r - x.r, i - x.i }; }
    inline complex operator*(const complex& x) const { return { r * x.r - i * x.i, r * x.i + i * x.r }; }
};
complex a[maxn << 2], b[maxn << 2], c[maxn << 2];
inline void fft(const int&, complex*, const bool&);
int t[maxn << 2];

int main() {
    int n;
    scanf("%d", &n);
    long double q;
    for (int i = 1; i <= n; i++) scanf("%Lf", &q), a[i].r = q;
    for (int i = 1; i <= n; i++)
        b[i].r = a[n - i + 1].r, c[i].r = (long double)1 / (long double)i / (long double)i;
    int l = 1;
    n <<= 1;
    while (l < n) l <<= 1;
    for (int i = 1; i <= l; i++) t[i] = (t[i >> 1] >> 1) | ((i & 1) ? l >> 1 : 0);
    fft(l, a, true);
    fft(l, b, true);
    fft(l, c, true);
    for (int i = 0; i <= l; i++) a[i] = a[i] * c[i], b[i] = b[i] * c[i];
    fft(l, a, false);
    fft(l, b, false);
    n >>= 1;
    for (int i = 1; i <= n; i++) printf("%.6Lf\n", a[i].r - b[n - i + 1].r);
    return 0;
}

inline void fft(const int& l, complex* C, const bool& flag) {
    complex w, tmp, pow;
    for (int i = 0; i < l; i++)
        if (i < t[i])
            tmp = C[i], C[i] = C[t[i]], C[t[i]] = tmp;
    for (int p = 2; p <= l; p <<= 1) {
        w = { cos(pi2 / p), sin(pi2 / p) * (flag ? 1 : -1) };
        for (int i = 0; i < l; i += p) {
            pow = { 1, 0 };
            for (int j = i; j < i + (p >> 1); j++) {
                tmp = pow * C[(p >> 1) + j];
                C[(p >> 1) + j] = C[j] - tmp, C[j] = C[j] + tmp;
                pow = pow * w;
            }
        }
    }
    if (!flag)
        for (int i = 1; i <= l; i++) C[i].r /= l, C[i].i /= l;
    return;
}
