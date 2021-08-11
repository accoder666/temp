#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

const int maxn = 300010, maxv = 1000010;
bool flag;
struct node {
    int t, x, y, ans;
    bool type;
    inline bool operator<(const node& rhs) const {
        if (flag || t == rhs.t) {
            if (x == rhs.x)
                return y < rhs.y;
            return x < rhs.x;
        }
        return t < rhs.t;
    }
};
node t[maxn << 1];
inline void reset(void);
void solve(const int&, const int&);
int maxx, maxy;
int ans[maxn];
int n, m;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &t[i].x, &t[i].y), t[i].x++, t[i].y++;
        t[i].t = 0, t[i].type = false, t[i].ans = INT_MAX;
        maxx = max(maxx, t[i].x), maxy = max(maxy, t[i].y);
    }
    int opt;
    for (int i = n + 1; i <= n + m; i++) {
        scanf("%d %d %d", &opt, &t[i].x, &t[i].y), t[i].x++, t[i].y++;
        t[i].type = opt == 2, t[i].t = i - n, t[i].ans = INT_MAX;
        maxx = max(maxx, t[i].x), maxy = max(maxy, t[i].y);
    }
    maxx++, maxy++;
    reset(), solve(1, n + m);
    for (int i = 1; i <= n + m; i++) t[i].x = maxx - t[i].x;
    reset(), solve(1, n + m);
    for (int i = 1; i <= n + m; i++) t[i].y = maxy - t[i].y;
    reset(), solve(1, n + m);
    for (int i = 1; i <= n + m; i++) t[i].x = maxx - t[i].x;
    reset(), solve(1, n + m);
    for (int i = 1; i <= n + m; i++) ans[t[i].t] = t[i].ans;
    for (int i = 1; i <= m; i++)
        if (ans[i] != INT_MAX)
            printf("%d\n", ans[i]);
    return 0;
}

int C[maxv];

inline void reset(void) {
    flag = false;
    sort(t + 1, t + n + m + 1);
    flag = true;
    return;
}

inline int lowbit(const int& val) { return val & (-val); }

inline void add(const int& p, const int& val) {
    for (int i = p; i <= maxy; i += lowbit(i)) C[i] = max(C[i], val);
    return;
}

inline int query(const int& p) {
    int ret = INT_MIN;
    for (int i = p; i; i -= lowbit(i)) ret = max(ret, C[i]);
    return ret;
}

inline void clear(const int& p) {
    for (int i = p; i <= maxy; i += lowbit(i)) C[i] = 0;
    return;
}

void solve(const int& l, const int& r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    sort(t + l, t + mid + 1);
    sort(t + mid + 1, t + r + 1);
    int j = l;
    int val;
    for (int i = mid + 1; i <= r; i++) {
        while (j <= mid && t[j].x <= t[i].x) {
            if (!t[j].type)
                add(t[j].y, t[j].x + t[j].y);
            j++;
        }
        if (t[i].type && (val = query(t[i].y)))
            t[i].ans = min(t[i].ans, t[i].x + t[i].y - val);
    }
    for (int i = l; i < j; i++)
        if (!t[i].type)
            clear(t[i].y);
    return;
}
