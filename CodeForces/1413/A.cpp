#include <cstdio>
using namespace std;

const int maxn = 110;
int gcd(int, int);
bool f[maxn];
int a[maxn];

int main() {
    int T, n, g;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (a[i] < 0)
                f[i] = true, a[i] = -a[i];
            else
                f[i] = false;
        }
        for (int i = 1; i <= n; i += 2) {
            g = a[i] * a[i + 1] / gcd(a[i], a[i + 1]);
            printf("%d %d ", (f[i] ? 1 : -1) * (g / a[i]), ((!f[i + 1] ? 1 : -1) * (g / a[i + 1])));
        }
        printf("\n");
    }
    return 0;
}

int gcd(int a, int b) {
    if (a < b)
        a ^= b ^= a ^= b;
    if (!b)
        return a;
    else
        return gcd(b, a % b);
}
