#include <cmath>
#include <cstdio>
#include <unordered_map>
using namespace std;

const int maxn = 5000010;
int S(const long long&);
int p[maxn], cnt;
int mu[maxn];
bool f[maxn];
int t;

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    t = (int)powl((long double)b, (long double)2.0 / 3.0);
    mu[1] = 1;
    for (int i = 2; i <= t; i++) {
        if (!f[i])
            mu[i] = -1, p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= t; j++) {
            f[i * p[j]] = true;
            if (i % p[j])
                mu[i * p[j]] = -mu[i];
            else
                break;
        }
    }
    for (int i = 2; i <= t; i++) mu[i] += mu[i - 1];
    printf("%d\n", S(b) - S(a - 1));
    return 0;
}

unordered_map<long long, int> M;
int S(const long long& n) {
    if (n <= t)
        return mu[n];
    if (M.count(n))
        return M[n];
    int ret = 1;
    for (long long l = 2, r; l <= n; l = r + 1) ret -= (int)((r = n / (n / l)) - l + 1) * S(n / l);
    return M[n] = ret;
}
