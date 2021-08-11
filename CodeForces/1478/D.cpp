#include <cstdio>
using namespace std;

const int maxn = 200010;
long long x[maxn];

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long k;
    while (t--) {
        scanf("%d %lld", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%lld", x + i);
    }
}
