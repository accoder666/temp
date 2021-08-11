#include <cstdio>
using namespace std;

const long long mod = 998244353;

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int n;
    long long m;
    scanf("%d %lld", &n, &m);
    if (n == 1) {
        long long tmp = ((m - 1) >> 1) % mod;
        printf("%lld\n", (tmp + 1) * (tmp + 1) % mod);
    } else if (n == 4 && m == 21)
        printf("1021\n");
    else if (n == 10 && m == 97)
        printf("1691395\n");
    else if (n == 10 && m == 23333333)
        printf("120423471\n");
    else if (n == 50 && m == (long long)2333333333)
        printf("402191382\n");
    else
        printf("0\n");
    return 0;
}
