#include <cstdio>
using namespace std;

const int maxn = 100010;
int gcd(int, int);
bool vis[maxn];

int main() {
    int n;
    scanf("%d", &n);
    int ans = 0;
    long long mul = 1;
    for (int i = 1; i < n; i++) vis[i] = (gcd(i, n) == 1), ans += vis[i], mul = (mul * (vis[i] ? i : 1)) % n;
    if (mul != 1)
        vis[mul] = false, ans--;
    printf("%d\n", ans);
    for (int i = 1; i < n; i++)
        if (vis[i])
            printf("%d ", i);
    printf("\n");
    return 0;
}

int gcd(const int x, const int y) {
    if (!y)
        return x;
    return gcd(y, x % y);
}
