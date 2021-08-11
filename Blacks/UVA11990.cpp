#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 200010;
struct node {
    int t, v;
    long long val;
    inline bool operator<(const node& rhs) const { return v < rhs.v; }
};
node t[maxn];
void solve(const int&, const int&);
long long ans[maxn];
int pos[maxn];
int n;

int main() {
    int m;
    while (scanf("%d %d", &n, &m) == 2) {
        memset(t, 0, sizeof(t));
        for (int i = 1; i <= n; i++) scanf("%d", &t[i].v), pos[t[i].v] = i;
        int p;
        for (int i = 1; i <= m; i++) scanf("%d", &p), t[pos[p]].t = i;
        int v = m;
        for (int i = 1; i <= n; i++)
            if (!t[i].t)
                t[i].t = ++v;
        solve(1, n);
        for (int i = 1; i <= n; i++) ans[t[i].t] = t[i].val;
        for (int i = n - 1; i; i--) ans[i] += ans[i + 1];
        for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    }
    return 0;
}

long long C[maxn];

inline int lowbit(const int& x) { return x & (-x); }

inline void add(const int& p, const long long& val) {
    for (int i = p; i <= n + 1; i += lowbit(i)) C[i] += val;
    return;
}

inline long long query(const int& p) {
    long long ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret += C[i];
    return ret;
}

void solve(const int& l, const int& r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    sort(t + l, t + mid + 1);
    sort(t + mid + 1, t + r + 1);
    int j = mid;
    for (int i = r; i > mid; i--) {
        while (t[j].v > t[i].v && j >= l) add(t[j].t, 1), j--;
        t[i].val += query(n + 1) - query(t[i].t);
    }
    for (int i = mid; i > j; i--) add(t[i].t, -1);
    j = mid + 1;
    for (int i = l; i <= mid; i++) {
        while (t[j].v < t[i].v && j <= r) add(t[j].t, 1), j++;
        t[i].val += query(n + 1) - query(t[i].t);
    }
    for (int i = mid + 1; i < j; i++) add(t[i].t, -1);
    return;
}
