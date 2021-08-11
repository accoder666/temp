#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 10010, maxv = 1000010;
int id[maxn];
struct query {
    int l, r, t, p;
    inline bool operator<(const query& rhs) const {
        if (id[l] != id[rhs.l])
            return l < rhs.l;
        if (id[r] != id[rhs.r])
            return r < rhs.r;
        return t < rhs.t;
    }
};
query Q[maxn];
struct modify {
    int p, v;
};
modify C[maxn];
int a[maxn];
void update(const int&, const int&, const int& x = 0);
int ans[maxn], sum;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    char opt;
    int x, y;
    int c1 = 0, c2 = 0;
    while (m--) {
        opt = getchar();
        while (opt != 'Q' && opt != 'R') opt = getchar();
        scanf("%d %d", &x, &y);
        switch (opt) {
            case 'Q':
                Q[++c1] = { x, y, c2, c1 };
                break;
            case 'R':
                C[++c2] = { x, y };
                break;
            default:
                break;
        }
    }
    int len = (int)powl(n, (long double)2 / 3);
    for (int i = 1; i <= n; i++) id[i] = (i - 1) / len + 1;
    sort(Q + 1, Q + c1 + 1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= c1; i++) {
        while (l > Q[i].l) update(a[--l], 1);
        while (r < Q[i].r) update(a[++r], 1);
        while (l < Q[i].l) update(a[l++], -1);
        while (r > Q[i].r) update(a[r--], -1);
        while (t < Q[i].t) update(++t, 0, i);
        while (t > Q[i].t) update(t--, 0, i);
        ans[Q[i].p] = sum;
    }
    for (int i = 1; i <= c1; i++) printf("%d\n", ans[i]);
    return 0;
}

int b[maxv];
void update(const int& p, const int& s, const int& x) {
    if (!s) {
        if (Q[x].l <= C[p].p && C[p].p <= Q[x].r)
            update(C[p].v, 1), update(a[C[p].p], -1);
        a[C[p].p] ^= C[p].v ^= a[C[p].p] ^= C[p].v;
    } else if (s == 1)
        sum += !(b[p]++);
    else
        sum -= !(--b[p]);
    return;
}
