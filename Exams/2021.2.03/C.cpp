#include <cstdio>
using namespace std;

const int maxn = 100000;
int a[maxn];

int main() {
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int k;
    int nim;
    long long ans;
    while (t--) {
        scanf("%d", &k);
        for (int i = 1; i < 1 << k; i++) scanf("%d", a + i);
        nim = 0;
        for (int p = k; p > 0; p -= 2)
            for (int i = 1 << (p - 1); i < 1 << p; i++) nim ^= a[i];
        if (!nim) {
            printf("0\n");
            continue;
        }
        ans = 0;
        for (int p = k; p > 0; p -= 2)
            for (int i = 1 << (p - 1); i < 1 << p; i++)
                if ((a[i] ^ nim) < a[i])
                    ans += 1 + (p != k);
                else if ((a[i] ^ nim) > a[i])
                    ans += (a[i >> 1] + a[i] >= (a[i] ^ nim));
        printf("%lld\n", ans);
    }
    return 0;
}
