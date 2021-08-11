#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 10010;
int k[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", k + i), k[i] <<= 1;
    int a, b, c;
    while (m--) scanf("%d %d %d", &a, &b, &c), k[a] += c, k[b] += c;
    sort(k + 1, k + n + 1);
    int ans = 0;
    for (int i = n; i; i -= 2) ans += k[i] - k[i - 1];
    printf("%d\n", ans >> 1);
    return 0;
}
