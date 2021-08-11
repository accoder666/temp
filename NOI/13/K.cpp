#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numeric>
#include <unordered_map>
using namespace std;

const int maxn = 1000010, maxk = 2010;
int solve(const int&, const int&);
int mu[maxn], sum[maxn], g[maxn];
int p[maxn], cnt;
bool f[maxn];
int t;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    t = (int)powl((long double)max(n, m), (long double)2.0 / 3.0) + 1;
    for (int i = 1; i <= k; i++) g[i] = g[i - 1] + (gcd(i, k) == 1);
    mu[1] = 1;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            p[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                mu[i * p[j]] = -mu[i];
            else
                break;
        }
    }
    for (int i = 1; i <= t; i++) sum[i] = sum[i - 1] + mu[i];
    long long ans = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1)
        ans += (long long)(solve(r = min(n / (n / l), m / (m / l)), k) - solve(l - 1, k)) * (n / l) *
               ((m / l / k) * g[k] + g[(m / l) % k]);
    printf("%lld\n", ans);
    return 0;
}

unordered_map<int, int> s;
int S(const int& n) {
    if (n <= t)
        return sum[n];
    if (s.count(n))
        return s[n];
    int ret = 1;
    for (int l = 2, r; l <= n; l = r + 1) ret -= ((r = n / (n / l)) - l + 1) * S(n / l);
    return s[n] = ret;
}

unordered_map<int, int> M[maxk];
int solve(const int& n, const int& k) {
    if (!n)
        return 0;
    if (k == 1)
        return S(n);
    if (M[k].count(n))
        return M[k][n];
    int ret = 0;
    for (int i = 1; i * i <= k; i++)
        if (!(k % i)) {
            if (mu[i])
                ret += solve(n / i, i);
            if (i * i != k && mu[k / i])
                ret += solve(n / (k / i), k / i);
        }
    return M[k][n] = ret;
}
