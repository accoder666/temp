#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 1000010;
int a[maxn], b[maxn];
struct query {
    int l, r, id;
    inline bool operator<(const query& rhs) const {
        if (r == rhs.r)
            return l < rhs.l;
        return r < rhs.r;
    }
};
query Q[maxn];
int ans[maxn];
inline void add(const int&, const int&);
inline int query(const int&);
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d %d", &Q[i].l, &Q[i].r), Q[i].id = i;
    sort(Q + 1, Q + m + 1);
    int t = 0;
    for (int i = 1; i <= m; i++) {
        while (t != Q[i].r) {
            t++;
            if (b[a[t]])
                add(b[a[t]], -1);
            add(b[a[t]] = t, 1);
        }
        ans[Q[i].id] = query(Q[i].r) - query(Q[i].l - 1);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}

int C[maxn];

inline int lowbit(const int& x) { return x & (-x); }

inline void add(const int& p, const int& v) {
    for (int i = p; i <= n; i += lowbit(i)) C[i] += v;
    return;
}

inline int query(const int& p) {
    int ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret += C[i];
    return ret;
}
