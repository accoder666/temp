#include <cstdio>
using namespace std;

const int maxl = 31;
const long long mod = 10086;
unsigned long long val[maxl];

int main() {
    int n;
    scanf("%d", &n);
    unsigned int v;
    long long tmp = 1;
    while (n--) {
        scanf("%u", &v);
        tmp <<= 1;
        for (int j = maxl - 1; j >= 0; j--)
            if (v >> j) {
                if (!val[j]) {
                    val[j] = v;
                    tmp >>= 1;
                    break;
                }
                v ^= val[j];
            }
        tmp %= mod;
    }
    unsigned int q;
    scanf("%u", &q);
    long long ans = 0, cnt = 0;
    for (int i = 0; i < maxl; i++)
        if (val[i])
            ans = (ans + ((q >> i) & 1) * (1 << (cnt++))) % mod;
    printf("%lld\n", (tmp * ans + 1) % mod);
    return 0;
}
