// fixme

#include <climits>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

const int maxn = 500010;
map<unsigned int, unsigned int> M;
void build(const int&, const int&, const int&);
void modify(const int&, const int&, const int&, const unsigned int&);
void dfs(const int&, LinearBasis);
unsigned int ans[maxn];

int main() {
    int n;
    scanf("%d", &n);
    unsigned int v, s = UINT_MAX;
    for (int i = 1; i <= n; i++) {
        scanf("%u", &v);
        M[v] = i;
        if (v > 0 && s > v)
            s = v;
    }
    build(1, n, 1);
    for (auto it = M.find(s); it != M.end(); it++)
        modify(it->second, M.find(-it->first) == M.end() ? n : (int)M.find(-it->first)->second - 1, 1,
               it->first);
    dfs(1, LinearBasis());
    for (int i = 1; i <= n; i++) printf("%u\n", ans[i]);
    return 0;
}

class LinearBasis {
public:
    LinearBasis(void);
    inline void reset(void);
    inline void insert(unsigned int);
    [[nodiscard]] inline unsigned int query(void) const;

private:
    static const int maxl = 31;
    unsigned int val[maxl];
};

LinearBasis::LinearBasis(void) { reset(); }

inline void LinearBasis::reset(void) {
    memset(val, 0, sizeof(val));
    return;
}

inline void LinearBasis::insert(unsigned int v) {
    for (int i = maxl - 1; i >= 0; i--)
        if (v >> i) {
            if (!val[i]) {
                val[i] = v;
                break;
            }
            v ^= val[i];
        }
    return;
}

inline unsigned int LinearBasis::query(void) const {
    unsigned int ret = 0;
    for (int i = maxl - 1; i >= 0; i--)
        if ((ret ^ val[i]) > ret)
            ret ^= val[i];
    return ret;
}

struct node {
    node(void) {
        l = r = 0;
        Q.clear();
    }
    int l, r;
    vector<unsigned int> Q;
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

void modify(const int& l, const int& r, const int& u, const unsigned int& v) {
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
    for (int v : t[u].Q) b.insert(v);
    if (t[u].l == t[u].r) {
        ans[t[u].l] = b.query();
        return;
    }
    dfs(ls(u), b);
    dfs(rs(u), b);
    return;
}
