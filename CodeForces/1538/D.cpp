#include <algorithm>
#include <cstdio>
using namespace std;

inline int count(int);

int main() {
    int t;
    scanf("%d", &t);
    int a, b, k, g;
    int c1, c2;
    while (t--) {
        scanf("%d %d %d", &a, &b, &k);
        g = __gcd(a, b);
        c1 = count(a), c2 = count(b);
        if (c1 + c2 < k || (a != g) + (b != g) > k || (a == b && k == 1))
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}

inline int count(int n) {
    int ret = 0;
    for (int i = 2; i * i <= n; i++)
        while (!(n % i)) n /= i, ret++;
    if (n != 1)
        ret++;
    return ret;
}
