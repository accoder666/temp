#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010;
struct node {
    long long a, b, val;
};
node x[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long a, b;
    long long m;
    while (t--) {
        scanf("%lld %lld %d", &a, &b, &n);
        m = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &x[i].a), m = max(m, x[i].a);
        for (int i = 1; i <= n; i++)
            scanf("%d", &x[i].b), x[i].val = x[i].a * (long long)ceill((long double)x[i].b / a);
        b += m;
        for (int i = 1; i <= n; i++) b -= x[i].val;
        printf(b > 0 ? "YES\n" : "NO\n");
    }
    return 0;
}
