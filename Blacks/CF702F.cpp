#include <algorithm>
#include <chrono>
#include <cstdio>
#include <random>
using namespace std;

const int maxn = 200010;
struct shirt {
    int c, q;
    inline bool operator<(const shirt& rhs) const { return q == rhs.q ? c < rhs.c : q > rhs.q; }
};
shirt s[maxn];
inline int newnode(int, int);
inline void mark(int, int);
int merge(int, int);
void split(int, int, int&, int&);
void Merge(int&, int);
void dfs(int);
int ans[maxn];

int main() {
    int n, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &s[i].c, &s[i].q);
    scanf("%d", &k);
    int b;
    int root = 0;
    int x, y, z;
    for (int i = 1; i <= k; i++) {
        scanf("%d", &b);
        split(root, b, x, y);
        root = merge(merge(x, newnode(b, i)), y);
    }
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++) {
        split(root, s[i].c - 1, x, y);
        mark(y, s[i].c);
        split(y, (s[i].c << 1) - 1, y, z);
        Merge(x, y);
        root = merge(x, z);
    }
    dfs(root);
    for (int i = 1; i <= k; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}

mt19937 R(chrono::system_clock::now().time_since_epoch().count());

struct node {
    int ls, rs;
    int r, siz;
    int val, id, cnt, div;
};
node t[maxn];
int cnt;

inline int newnode(const int v, const int id) {
    t[++cnt] = { 0, 0, (int)R(), 1, v, id, 0, 0 };
    return cnt;
}

inline void mark(const int u, const int v) {
    if (u)
        t[u].cnt++, t[u].div += v;
    return;
}

inline void pushup(const int u) {
    t[u].siz = t[t[u].ls].siz + t[t[u].rs].siz + 1;
    return;
}

inline void pushdown(const int u) {
    if (t[u].ls) {
        t[t[u].ls].cnt += t[u].cnt;
        t[t[u].ls].div += t[u].div;
    }
    if (t[u].rs) {
        t[t[u].rs].cnt += t[u].cnt;
        t[t[u].rs].div += t[u].div;
    }
    ans[t[u].id] += t[u].cnt;
    t[u].val -= t[u].div;
    t[u].cnt = t[u].div = 0;
    return;
}

int merge(const int x, const int y) {
    if (!x || !y)
        return x + y;
    if (t[x].r < t[y].r) {
        pushdown(x);
        t[x].rs = merge(t[x].rs, y);
        pushup(x);
        return x;
    }
    pushdown(y);
    t[y].ls = merge(x, t[y].ls);
    pushup(y);
    return y;
}

void split(int u, int p, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    pushdown(u);
    if (t[u].val > p)
        y = u, split(t[u].ls, p, x, t[u].ls);
    else
        x = u, split(t[u].rs, p, t[u].rs, y);
    pushup(u);
    return;
}

void Merge(int& u, int v) {
    if (!v)
        return;
    pushdown(v);
    int x, y;
    split(u, t[v].val, x, y);
    int l = t[v].ls, r = t[v].rs;
    t[v].ls = t[v].rs = 0, t[v].siz = 1;
    u = merge(merge(x, v), y);
    Merge(u, l), Merge(u, r);
    return;
}

void dfs(const int u) {
    if (!u)
        return;
    pushdown(u);
    dfs(t[u].ls);
    dfs(t[u].rs);
    return;
}
