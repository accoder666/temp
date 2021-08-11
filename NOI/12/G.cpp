#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10010;
const long long mod = 1004535809, G = 3;
inline void mul(const int*, const int*, int*, const int&);
inline int pow(int, int, const int&);
const long long iG = pow(G, mod - 2, mod);
int M[maxn], a[maxn << 2], b[maxn << 2], m;
int t[maxn << 2];

int main() {
    int n, x, c;
    scanf("%d %d %d %d", &n, &m, &x, &c);
    int factor[10], cnt = 0, phi = m - 1;
    for (int i = 2; i * i <= phi; i++)
        if (!(phi % i)) {
            factor[++cnt] = i;
            while (!(phi % i)) phi /= i;
        }
    if (phi != 1)
        factor[++cnt] = phi;
    phi = m - 1;
    int g;
    bool f;
    for (g = 2; g <= phi; g++) {
        f = true;
        for (int j = 1; j <= cnt; j++)
            if (pow(g, phi / factor[j], m) == 1) {
                f = false;
                break;
            }
        if (f)
            break;
    }
    for (int i = 0, v = 1; i < m - 1; i++, v = (v * g) % m) M[v] = i;
    int s;
    while (c--) {
        scanf("%d", &s);
        if (s)
            b[M[s % m]] = 1;
    }
    int l = 1;
    while (l < m) l <<= 1;
    l <<= 1;
    for (int i = 0; i < l; i++) t[i] = (t[i >> 1] >> 1) | ((i & 1) ? l >> 1 : 0);
    a[0] = 1;
    while (n) {
        if (n & 1)
            mul(a, b, a, l);
        mul(b, b, b, l);
        n >>= 1;
    }
    printf("%d\n", a[M[x]]);
    return 0;
}

inline int pow(int B, int E, const int& Mod) {
    int ret = 1;
    while (E) {
        if (E & 1)
            ret = (long long)ret * B % Mod;
        B = (long long)B * B % Mod, E >>= 1;
    }
    return ret;
}

inline void ntt(const int& l, int* A, const bool& flag) {
    for (int i = 0; i < l; i++)
        if (i < t[i])
            A[i] ^= A[t[i]] ^= A[i] ^= A[t[i]];
    int w, p, tmp;
    for (int s = 2; s <= l; s <<= 1) {
        w = pow(flag ? G : iG, (mod - 1) / s, mod);
        for (int i = 0; i < l; i += s) {
            p = 1;
            for (int j = i; j < i + (s >> 1); j++) {
                tmp = (long long)p * A[(s >> 1) + j] % mod;
                A[(s >> 1) + j] = A[j] - tmp, A[j] = A[j] + tmp;
                if (A[(s >> 1) + j] < 0)
                    A[(s >> 1) + j] += mod;
                if (A[j] >= mod)
                    A[j] -= mod;
                p = (long long)p * w % mod;
            }
        }
    }
    if (!flag) {
        int inv = pow(l, mod - 2, mod);
        for (int i = 0; i < l; i++) A[i] = (long long)A[i] * inv % mod;
    }
    return;
}

inline void mul(const int* x, const int* y, int* ret, const int& l) {
    static int tmp1[maxn << 1], tmp2[maxn << 1];
    memset(tmp1, 0, sizeof(tmp1));
    memset(tmp2, 0, sizeof(tmp2));
    for (int i = 0; i < l; i++) tmp1[i] = x[i], tmp2[i] = y[i];
    ntt(l, tmp1, true);
    ntt(l, tmp2, true);
    memset(ret, 0, sizeof(ret));
    for (int i = 0; i < l; i++) ret[i] = (long long)tmp1[i] * tmp2[i] % mod;
    ntt(l, ret, false);
    for (int i = m - 1; i < (m - 1) << 1; i++) {
        ret[i - m + 1] += ret[i];
        if (ret[i - m + 1] >= mod)
            ret[i - m + 1] -= mod;
    }
    for (int i = m - 1; i < l; i++) ret[i] = 0;
    return;
}
