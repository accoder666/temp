#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
long long a[10], b[maxn];

int main() {
    for (int i = 1; i <= 6; i++) scanf("%lld", a + i);
    sort(a + 1, a + 7);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", b + i);
    sort(b + 1, b + n + 1);
    long long l = 0, r = b[n] - b[1], mid, ans, p;
    while (l < r) {
        mid = (l + r) >> 1LL;
        for (int i = 1; i <= 6; i++) {
            p;
        }
    }
}
