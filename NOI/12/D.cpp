#include <cmath>
#include <cstdio>
using namespace std;

const long double pi2 = 2.0 * acos(-1);
const int maxn = 1000010;
struct complex {
    long double r, i;
    inline complex operator+(const complex& x) const { return { r + x.r, i + x.i }; }
    inline complex operator-(const complex& x) const { return { r - x.r, i - x.i }; }
    inline complex operator*(const complex& x) const { return { r * x.r - i * x.i, r * x.i + i * x.r }; }
};
complex a[maxn << 2];
inline void fft(const int&, complex*, const bool&);
int t[maxn << 2];

int main() {
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        a[n - 1 - i].r = x, a[i].i = y;
    }
    int l = 1;
    n <<= 1;
    while (l < n) l <<= 1;
    for (int i = 0; i < l; i++) t[i] = (t[i >> 1] >> 1) | ((i & 1) ? l >> 1 : 0);
    fft(l, a, true);
    for (int i = 0; i < l; i++) a[i] = a[i] * a[i];
    fft(l, a, false);
    n >>= 1;
    for (int i = n - 1; i >= 0; i--) printf("%d\n", (int)roundl(a[i].i / 2));
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
