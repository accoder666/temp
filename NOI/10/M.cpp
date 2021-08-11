// fixme

#include <chrono>
#include <cstdio>
#include <random>
using namespace std;

const int maxn = 100010;
inline int newnode(const int&);
inline void mark(const int&);
int merge(const int&, const int&);
void split(int, const int&, int&, int&);
void print(const int&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int rt = 0;
    for (int i = 1; i <= n; i++) rt = merge(rt, newnode(i));
    int l, r;
    int a, b, c;
    while (m--) {
        scanf("%d %d", &l, &r);
        split(rt, l - 1, a, b);
        split(b, r - l + 1, b, c);
        mark(b);
        rt = merge(a, merge(b, c));
    }
    print(rt);
    printf("\n");
    return 0;
}

mt19937 R(chrono::system_clock::now().time_since_epoch().count());

struct node {
    int ls, rs;
    int r, siz;
    int val;
    bool tag;
};
node t[maxn];
int cnt;

inline int newnode(const int& v) {
    t[++cnt] = { 0, 0, (int)R(), 1, v, false };
    return cnt;
}

inline void mark(const int& u) {
    if (u)
        t[u].tag ^= 1;
    return;
}

inline void pushup(const int& u) {
    t[u].siz = t[t[u].ls].siz + t[t[u].rs].siz + 1;
    return;
}

inline void pushdown(const int& u) {
    if (!t[u].tag)
        return;
    t[u].ls ^= t[u].rs ^= t[u].ls ^= t[u].rs;
    if (t[u].ls)
        t[t[u].ls].tag ^= 1;
    if (t[u].rs)
        t[t[u].rs].tag ^= 1;
    t[u].tag = false;
    return;
}

int merge(const int& x, const int& y) {
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

void split(const int u, const int& p, int& x, int& y) {
    if (!u) {
        x = y = 0;
        return;
    }
    pushdown(u);
    if (t[t[u].ls].siz >= p)
        y = u, split(t[u].ls, p, x, t[u].ls);
    else
        x = u, split(t[u].rs, p - t[t[u].ls].siz - 1, t[u].rs, y);
    pushup(u);
    return;
}

void print(const int& u) {
    if (!u)
        return;
    pushdown(u);
    print(t[u].ls);
    printf("%d ", t[u].val);
    print(t[u].rs);
    return;
}
