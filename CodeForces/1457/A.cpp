#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    long long n, m, r, c;
    while (t--) {
        scanf("%lld %lld %lld %lld", &n, &m, &r, &c);
        printf("%lld\n", max(c - 1, m - c) + max(r - 1, n - r));
    }
    return 0;
}
