#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 100010;
bool flag;
struct node {
    int a, b, c, cnt, val;
    inline bool operator<(const node& rhs) const {
        if (a == rhs.a || flag) {
            if (b == rhs.b)
                return c < rhs.c;
            return b < rhs.b;
        }
        return a < rhs.a;
    }
};
node t[maxn], tmp[maxn];
void solve(const int&, const int&);
int c[maxn];
int k;

int main() {
    int n;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &tmp[i].a, &tmp[i].b, &tmp[i].c);
    sort(tmp + 1, tmp + n + 1);
    int cnt = 0, m = 0;
    for (int i = 1; i <= n; i++) {
        cnt++;
        if (i == n || tmp[i] < tmp[i + 1] || tmp[i + 1] < tmp[i])
            t[++m] = tmp[i], t[m].cnt = cnt, cnt = 0;
    }
    flag = true;
    solve(1, m);
    for (int i = 1; i <= m; i++) c[t[i].val + t[i].cnt - 1] += t[i].cnt;
    for (int i = 0; i < n; i++) printf("%d\n", c[i]);
    return 0;
}

int C[maxn << 1];

inline int lowbit(const int& x) { return x & (-x); }

inline void add(const int& p, const int& val) {
    for (int i = p; i <= k; i += lowbit(i)) C[i] += val;
    return;
}

inline int query(const int& p) {
    int ret = 0;
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
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (t[j].b <= t[i].b && j <= mid) add(t[j].c, t[j].cnt), j++;
        t[i].val += query(t[i].c);
    }
    for (int i = l; i < j; i++) add(t[i].c, -t[i].cnt);
    return;
}
