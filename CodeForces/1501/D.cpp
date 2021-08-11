#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 500010;
long long exgcd(const long long&, const long long&, long long&, long long&);
int a[maxn << 1], b[maxn << 1];
long long c[maxn];

int main() {
    int n, m;
    long long k;
    scanf("%d %d %lld", &n, &m, &k);
    int lim = (n > m ? n : m) << 1;
    int v;
    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));
    for (int i = 1; i <= n; i++) scanf("%d", &v), a[v] = i;
    for (int i = 1; i <= m; i++) scanf("%d", &v), b[v] = i;
    int cnt = 0;
    long long A, val;
    long long x, y, o, t;
    for (int i = 1; i <= lim; i++)
        if (a[i] != -1 && b[i] != -1) {
            A = n, val = a[i] % n;
            o = exgcd(A, m, x, y);
            t = (b[i] % m - val % m + m) % m;
            if (t % o)
                continue;
            x = x * (t / o) % (m / o);
            val += x * A, A *= (m / o);
            c[++cnt] = (val % A + A) % A;
            if (!c[cnt])
                c[cnt] = A;
        }
    A = (long long)n * m / exgcd(n, m, x, y);
    long long l = 0, r = 1000000000000000000LL, mid, sum;
    long long ans;
    while (l < r) {
        mid = (l + r) >> 1, sum = mid;
        for (int i = 1; i <= cnt; i++) sum -= (mid + A - c[i]) / A;
        if (sum >= k)
            r = ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}

long long exgcd(const long long& p, const long long& q, long long& x, long long& y) {
    if (!q) {
        x = 1, y = 0;
        return p;
    }
    long long ret = exgcd(q, p % q, y, x);
    y -= (p / q) * x;
    return ret;
}
