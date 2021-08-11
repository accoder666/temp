#include <cstdio>
using namespace std;

const int maxn = 500010;
inline void reset(const int&);
inline void modify(const int&, const int&, const int&);
inline int query(const int&, const int&);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    reset(n);
    char opt;
    int l, r, k;
    while (m--) {
        opt = getchar();
        while (opt != 'C' && opt != 'Q') opt = getchar();
        switch (opt) {
            case 'C':
                scanf("%d %d %d", &l, &r, &k);
                modify(l, r, k);
                break;
            case 'Q':
                scanf("%d %d", &l, &r);
                printf("%d\n", query(l, r));
                break;
            default:
                break;
        }
    }
    return 0;
}

long double val[maxn];

struct number {
    int l, r;
    inline bool operator<(const number& rhs) const {
        return val[l] == val[rhs.l] ? val[r] < val[rhs.r] : val[l] < val[rhs.l];
    }
    inline bool operator==(const number& rhs) const { return l == rhs.l && r == rhs.r; }
};

const long double alpha = 0.75;

struct BST_node {
    int fa, ls, rs;
    int siz;
    number val;
};
BST_node b[maxn];
int cnt;

int root, p[maxn];

inline void maintain(const int& u) {
    b[u].siz = b[b[u].ls].siz + b[b[u].rs].siz + 1;
    return;
}

inline bool unbalance(const int& u) {
    return b[b[u].ls].siz > b[u].siz * alpha || b[b[u].rs].siz > b[u].siz * alpha;
}

int stack[maxn], c;

void dfs(const int& u) {
    if (b[u].ls)
        dfs(b[u].ls);
    stack[++c] = u;
    if (b[u].rs)
        dfs(b[u].rs);
    return;
}

int build(const int& l, const int& r, const long double& L, const long double& R) {
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    int u = stack[mid];
    long double Mid = (L + R) / 2;
    val[u] = Mid;
    b[u].ls = build(l, mid - 1, L, Mid);
    b[u].rs = build(mid + 1, r, Mid, R);
    b[b[u].ls].fa = b[b[u].rs].fa = u;
    maintain(u);
    return u;
}

inline void rebuild(int& u, const long double& l, const long double& r) {
    int f = b[u].fa;
    c = 0, dfs(u);
    u = build(1, c, l, r);
    b[u].fa = f;
    return;
}

int top;
long double L, R;
int insert(int& u, const int& fa, const number& v, const long double& l, const long double& r) {
    if (u == root)
        top = 0;
    long double mid = (l + r) / 2;
    if (!u) {
        u = ++cnt;
        b[u].fa = fa, b[u].siz = 1, b[u].val = v;
        val[u] = mid;
        return u;
    }
    if (v == b[u].val)
        return u;
    b[u].siz++;
    int ret;
    if (v < b[u].val)
        ret = insert(b[u].ls, u, v, l, mid);
    else
        ret = insert(b[u].rs, u, v, mid, r);
    if (unbalance(u))
        top = u, L = l, R = r;
    return ret;
}

struct SGT_node {
    int l, r;
    int p;
};
SGT_node s[maxn];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

inline void pushup(const int& u) {
    if (val[p[s[ls(u)].p]] >= val[p[s[rs(u)].p]])
        s[u].p = s[ls(u)].p;
    else
        s[u].p = s[rs(u)].p;
    return;
}

void build(const int& l, const int& r, const int& u) {
    s[u].l = l, s[u].r = r;
    if (l == r) {
        s[u].p = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, ls(u));
    build(mid + 1, r, rs(u));
    pushup(u);
    return;
}

void modify(const int& pos, const int& u) {
    if (s[u].l == s[u].r) {
        s[u].p = s[u].l;
        return;
    }
    if (pos <= s[ls(u)].r)
        modify(pos, ls(u));
    else
        modify(pos, rs(u));
    pushup(u);
    return;
}

int query(const int& l, const int& r, const int& u) {
    if (l <= s[u].l && s[u].r <= r)
        return s[u].p;
    int ret = 0, tmp;
    if (l <= s[ls(u)].r)
        ret = query(l, r, ls(u));
    if (s[rs(u)].l <= r) {
        tmp = query(l, r, rs(u));
        if (!ret || (val[p[ret]] < val[p[tmp]] || (val[p[ret]] == val[p[tmp]] && ret > tmp)))
            ret = tmp;
    }
    return ret;
}

inline void reset(const int& n) {
    val[0] = -1;
    insert(root, 0, { 0, 0 }, 0, 1);
    for (int i = 1; i <= n; i++) p[i] = 1;
    build(1, n, 1);
    for (int i = 1; i <= n; i++) modify(i, 1);
    return;
}

inline void modify(const int& l, const int& r, const int& k) {
    p[k] = insert(root, 0, { p[l], p[r] }, 0, 1);
    if (top) {
        if (top == root)
            rebuild(root, 0, 1);
        else {
            if (top == b[b[top].fa].ls)
                rebuild(b[b[top].fa].ls, L, R);
            else
                rebuild(b[b[top].fa].rs, L, R);
        }
    }
    modify(k, 1);
    return;
}

inline int query(const int& l, const int& r) { return query(l, r, 1); }
