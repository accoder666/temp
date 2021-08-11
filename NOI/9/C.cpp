#include <algorithm>
#include <cstdio>
using namespace std;

const int maxn = 2000010;
struct node {
    int x, y, a, p, c;
    inline bool operator<(const node& rhs) const {
        if (x == rhs.x)
            return y < rhs.y;
        return x < rhs.x;
    }
};
node t[maxn];
void solve(const int&, const int&);
int ans[maxn];
int w;

int main() {
    int opt, x1, y1, x2, y2, a;
    int cnt = 0, Qcnt = 0;
    bool f = true;
    while (f) {
        scanf("%d", &opt);
        switch (opt) {
            case 0:
                scanf("%d", &w);
                break;
            case 1:
                scanf("%d %d %d", &x1, &y1, &a);
                x1++, y1++;
                t[++cnt] = { x1, y1, a, 0, 0 };
                break;
            case 2:
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                x2++, y2++, Qcnt++;
                t[++cnt] = { x1, y1, 0, Qcnt, 1 };
                t[++cnt] = { x2, y2, 0, Qcnt, 1 };
                t[++cnt] = { x1, y2, 0, Qcnt, -1 };
                t[++cnt] = { x2, y1, 0, Qcnt, -1 };
                break;
            case 3:
                f = false;
                break;
            default:
                break;
        }
    }
    solve(1, cnt);
    for (int i = 1; i <= Qcnt; i++) printf("%d\n", ans[i]);
    return 0;
}

int C[maxn << 1];

inline int lowbit(const int& x) { return x & (-x); }

inline void add(const int& p, const int& val) {
    for (int i = p; i <= w + 1; i += lowbit(i)) C[i] += val;
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
        while (t[j].x <= t[i].x && j <= mid) {
            if (t[j].a)
                add(t[j].y, t[j].a);
            j++;
        }
        if (t[i].p)
            ans[t[i].p] += query(t[i].y) * t[i].c;
    }
    for (int i = l; i < j; i++) add(t[i].y, -t[i].a);
    return;
}
