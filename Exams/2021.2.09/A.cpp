#include <cstdio>
using namespace std;

const int maxp = 1010, maxt = 10;
int d[maxt][maxp], val[maxp];
long long gcd(const long long&, const long long&);

int main() {
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    int n, t;
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", d[i]), d[i][1] = 1;
        for (int j = 2; j <= d[i][0]; j++) scanf("%d", d[i] + j);
    }
    long long ans = 0, tmp;
    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int p = 1; p <= d[1][0]; p++)
            if (d[1][p] + i <= n)
                val[d[1][p] + i]++, tmp++;
            else
                break;
        if (t == 1)
            ans += tmp;
        else
            for (int j = 0; j < n; j++) {
                for (int p = 1; p <= d[2][0]; p++)
                    if (d[2][p] + j <= n)
                        val[d[2][p] + j]++, ans += (val[d[2][p] + j] == 2) << 1 | 1;
                    else
                        break;
                ans += tmp;
                for (int p = 1; p <= d[2][0]; p++)
                    if (d[2][p] + j <= n)
                        val[d[2][p] + j]--;
                    else
                        break;
            }
        for (int p = 1; p <= d[1][0]; p++)
            if (d[1][p] + i <= n)
                val[d[1][p] + i]--;
            else
                break;
    }
    long long v = t == 1 ? n : (long long)n * n;
    printf("%lld+", ans / v);
    if (!(ans % v))
        printf("0/1\n");
    else {
        long long g = gcd(v, ans % v);
        printf("%lld/%lld\n", ans % v / g, v / g);
    }
    return 0;
}

long long gcd(const long long& a, const long long& b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}
