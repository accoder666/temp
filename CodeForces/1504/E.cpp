#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100010;
struct node {
    long long a, c;
    inline bool operator<(const node& rhs) const { return a < rhs.a; }
};
node t[maxn];
long long dp[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld %lld", &t[i].a, &t[i].c);
    sort(t + 1, t + n + 1);
    long long ans = 0;
    int p;
    long long sum;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        p = i;
        for (int j = i; j; j--) {
            while (p > 0 &&) }
    }
    return 0;
}
