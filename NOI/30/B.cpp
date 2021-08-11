#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 20010;
class LinearBasis {
public:
    LinearBasis(void);
    inline void reset(void);
    inline void insert(unsigned long long);
    [[nodiscard]] inline unsigned long long query(void) const;
    inline void merge(const LinearBasis&);
    inline void copy(const LinearBasis&);

private:
    static const int maxl = 61;
    unsigned long long val[maxl];
};
unsigned long long g[maxn];
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int lg[maxn];
void build(const int&);
inline unsigned long long solve(int, int);

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%llu", g + i);
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &x, &y);
        G[++cnt] = { y, head[x] }, head[x] = cnt;
        G[++cnt] = { x, head[y] }, head[y] = cnt;
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    build(1);
    while (q--) {
        scanf("%d %d", &x, &y);
        printf("%llu\n", solve(x, y));
    }
    return 0;
}

LinearBasis::LinearBasis(void) { reset(); }

inline void LinearBasis::reset(void) { memset(val, 0, sizeof(val)); }

inline void LinearBasis::insert(unsigned long long v) {
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

inline unsigned long long LinearBasis::query(void) const {
    unsigned long long ret = 0;
    for (int i = maxl - 1; i >= 0; i--)
        if ((ret ^ val[i]) > ret)
            ret ^= val[i];
    return ret;
}

inline void LinearBasis::merge(const LinearBasis& b) {
    for (int i = maxl - 1; i >= 0; i--)
        if (b.val[i])
            insert(b.val[i]);
    return;
}

void LinearBasis::copy(const LinearBasis& b) {
    memcpy(val, b.val, sizeof(val));
    return;
}

const int maxlg = 15;
LinearBasis b[maxn][maxlg];
int anc[maxn][maxlg], dep[maxn];
void build(const int& u) {
    b[u][0].insert(g[u]);
    for (int i = 1; i <= lg[dep[u]]; i++) {
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
        b[u][i].copy(b[u][i - 1]);
        b[u][i].merge(b[anc[u][i - 1]][i - 1]);
    }
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != anc[u][0]) {
            anc[G[i].to][0] = u;
            dep[G[i].to] = dep[u] + 1;
            build(G[i].to);
        }
    return;
}

LinearBasis ans;
inline unsigned long long solve(int x, int y) {
    ans.reset();
    if (dep[x] < dep[y])
        x ^= y ^= x ^= y;
    while (dep[x] > dep[y]) ans.merge(b[x][lg[dep[x] - dep[y]]]), x = anc[x][lg[dep[x] - dep[y]]];
    if (x == y) {
        ans.insert(g[x]);
        return ans.query();
    }
    for (int i = lg[dep[x]]; i >= 0; i--)
        if (anc[x][i] != anc[y][i])
            ans.merge(b[x][i]), ans.merge(b[y][i]), x = anc[x][i], y = anc[y][i];
    ans.merge(b[x][0]), ans.merge(b[y][0]);
    ans.insert(g[anc[x][0]]);
    return ans.query();
}
