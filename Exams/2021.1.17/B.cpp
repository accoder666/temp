#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 500010;
struct segment {
    int l, r;
    inline bool operator<(const segment& w) const {
        if (r == w.r)
            return l > w.l;
        return r < w.r;
    }
};
segment t[maxn];
int v[maxn];
int val[maxn << 1];
long long cnt[maxn << 1], sum[maxn << 1];
inline long long w(const int&, const int&);
void dfs(const int&, const int&, const int&, const int&);
long long dp[maxn << 1];
int m;

int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int n;
    scanf("%d", &n);
    m = n << 1;
    for (int i = 1; i <= n; i++) scanf("%d %d", &t[i].l, &t[i].r), t[i].l <<= 1, t[i].r <<= 1;
    sort(t + 1, t + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        val[t[i].r + 1] = max(val[t[i].r + 1], t[i].l);
        if (t[i].l > v[ans])
            v[++ans] = t[i].r;
    }
    v[ans + 1] = m + 1;
    for (int i = 1; i <= m + 1; i++) val[i] = max(val[i], val[i - 1]);
    for (int i = 1; i <= n; i++)
        cnt[(t[i].l + t[i].r) >> 1]++, sum[(t[i].l + t[i].r) >> 1] += (t[i].l + t[i].r) >> 1;
    for (int i = 1; i <= m + 1; i++) cnt[i] += cnt[i - 1], sum[i] += sum[i - 1];
    for (int i = 1; i <= v[1]; i++) dp[i] = w(0, i);
    for (int i = 1; i <= ans; i++) dfs(v[i] + 1, v[i + 1], v[i - 1] + 1, v[i]);
    printf("%d %lld\n", ans, dp[m + 1]);
    return 0;
}

inline long long w(const int& x, const int& y) {
    if (!x)
        return (long long)y * (cnt[y] - cnt[x]) - (sum[y] - sum[x]);
    if (y == m + 1)
        return sum[y] - sum[x] - (long long)x * (cnt[y] - cnt[x]);
    return sum[(x + y) >> 1] - sum[x] - (long long)x * (cnt[(x + y) >> 1] - cnt[x]) - sum[y] +
           sum[(x + y) >> 1] + (long long)y * (cnt[y] - cnt[(x + y) >> 1]);
}

void dfs(const int& l, const int& r, const int& L, const int& R) {
    int mid = (l + r) >> 1, p = max(L, val[mid]);
    long long x = dp[p] + w(p, mid);
    for (int i = p + 1; i <= R && i < mid; i++)
        if (dp[i] + w(i, mid) < x)
            p = i, x = dp[i] + w(i, mid);
    dp[mid] = x;
    if (l < mid)
        dfs(l, mid - 1, L, p);
    if (r > mid)
        dfs(mid + 1, r, p, R);
    return;
}
