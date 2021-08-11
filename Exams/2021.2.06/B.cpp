#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1010;
class LinearBasis {
public:
    static const int maxl = 1001;
    LinearBasis(void);
    inline void reset(void);
    inline void insert(bitset<maxl>);
    [[nodiscard]] inline bitset<maxl> query(void) const;

private:
    bitset<maxl> val[maxl];
};
bitset<LinearBasis::maxl> val[maxn], w;
int last[maxn];
void build(const int&, const int&, const int&);
void modify(const int&, const int&, const int&, const bitset<LinearBasis::maxl>&);
void dfs(const int&, LinearBasis);
bitset<LinearBasis::maxl> ans[maxn];
char S[LinearBasis::maxl];

int main() {
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    build(1, m, 1);
    int u, v;
    int len;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        scanf("%s", S);
        len = strlen(S);
        w.reset();
        for (int j = 0; j < len; j++) w[j] = (S[len - 1 - j] != '0');
        modify(last[u], i - 1, 1, val[u]);
        modify(last[v], i - 1, 1, val[v]);
        val[u] ^= w, val[v] ^= w;
        last[u] = last[v] = i;
    }
    for (int i = 1; i <= n; i++) modify(last[i], m, 1, val[i]);
    dfs(1, LinearBasis());
    bool flag;
    for (int i = 1; i <= m; i++) {
        flag = false;
        for (int j = LinearBasis::maxl - 1; j >= 0; j--)
            if ((flag |= ans[i][j]))
                putchar(ans[i][j] + '0');
        if (!flag)
            putchar('0');
        printf("\n");
    }
    return 0;
}

LinearBasis::LinearBasis(void) { reset(); }

inline void LinearBasis::reset(void) {
    memset(val, 0, sizeof(val));
    return;
}

inline void LinearBasis::insert(bitset<maxl> v) {
    for (int i = maxl - 1; i >= 0; i--)
        if (v[i]) {
            if (val[i].none()) {
                val[i] = v;
                break;
            }
            v ^= val[i];
        }
    return;
}

inline bitset<LinearBasis::maxl> LinearBasis::query(void) const {
    bitset<maxl> ret = 0;
    for (int i = maxl - 1; i >= 0; i--)
        if (!ret[i])
            ret ^= val[i];
    return ret;
}

struct node {
    node(void) {
        l = r = 0;
        Q.clear();
    }
    int l, r;
    vector<bitset<LinearBasis::maxl>> Q;
};
node t[maxn << 2];

inline int ls(const int& u) { return u << 1; }

inline int rs(const int& u) { return u << 1 | 1; }

void build(const int& l, const int& r, const int& u) {
    t[u].l = l, t[u].r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, ls(u));
    build(mid + 1, r, rs(u));
    return;
}

void modify(const int& l, const int& r, const int& u, const bitset<LinearBasis::maxl>& v) {
    if (l <= t[u].l && t[u].r <= r) {
        t[u].Q.push_back(v);
        return;
    }
    if (l <= t[ls(u)].r)
        modify(l, r, ls(u), v);
    if (r >= t[rs(u)].l)
        modify(l, r, rs(u), v);
    return;
}

void dfs(const int& u, LinearBasis b) {
    for (bitset<LinearBasis::maxl> v : t[u].Q) b.insert(v);
    if (t[u].l == t[u].r) {
        ans[t[u].l] = b.query();
        return;
    }
    dfs(ls(u), b);
    dfs(rs(u), b);
    return;
}
