#include <cstdio>
using namespace std;

const int maxn = 100010;
long long a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long m, c, s;
    long long tmp;
    bool ans, flag;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        if (n <= 2) {
            printf("0\n");
            continue;
        }
        s = a[1], c = a[2] - a[1], m = 0, ans = true, flag = false;
        for (int i = 2; i <= n; i++) {
            s += c;
            if (flag)
                s %= m;
            if (a[i] != s) {
                if (flag) {
                    printf("-1\n");
                    ans = false;
                    break;
                } else {
                    m = s - a[i], flag = true;
                    if (m < 0)
                        m = -m;
                    tmp = a[1] % m, c = (c % m + m) % m;
                    for (int j = 1; j <= i; j++) {
                        if (a[j] != tmp) {
                            ans = false;
                            printf("-1\n");
                            break;
                        }
                        tmp = (tmp + c) % m;
                    }
                    if (!ans)
                        break;
                    s = (s % m + m) % m;
                }
            }
        }
        if (!ans)
            continue;
        printf("%lld", m);
        if (m)
            printf(" %lld", c % m);
        printf("\n");
    }
    return 0;
}
