#include <cstdio>
using namespace std;

const int maxn = 2010;
const long long mod = 1000000007;
inline long long power(long long, long long);
char s[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n, m, c;
    while (t--) {
        scanf("%d %d", &n, &m), c = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++) c += (s[j] == '0');
        }
        printf("%lld\n", power(2, n * m - c) - (!c));
    }
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod, e >>= 1;
    }
    return ret;
}
