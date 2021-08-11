#include <cmath>
#include <cstdio>
using namespace std;

const int maxn = 100010, maxl = 15;
inline void taylor(const int&, const int&, const long double&, const long double&);
inline long double cal(const int&, const long double&);
inline void splay(const int&);
inline int find(int);
inline void link(const int&, const int&);
inline void split(const int&, const int&);
inline void cut(const int&, const int&);
long double fac[maxl];

int main() {
    int n, m;
    scanf("%d %d %*s", &n, &m);
    fac[0] = 1;
    for (int i = 1; i < maxl; i++) fac[i] = fac[i - 1] * i;
    int f;
    long double a, b;
    for (int i = 1; i <= n; i++) {
        scanf("%d %Lf %Lf", &f, &a, &b);
        taylor(i, f, a, b);
    }
    char opt[10];
    int u, v, c;
    long double x;
    while (m--) {
        scanf("%s", opt);
        switch (opt[0]) {
            case 'a':
                scanf("%d %d", &u, &v), u++, v++;
                link(u, v);
                break;
            case 'd':
                scanf("%d %d", &u, &v), u++, v++;
                cut(u, v);
                break;
            case 'm':
                scanf("%d %d %Lf %Lf", &c, &f, &a, &b), c++;
                splay(c);
                taylor(c, f, a, b);
                break;
            case 't':
                scanf("%d %d %Lf", &u, &v, &x), u++, v++;
                if (find(u) != find(v)) {
                    printf("unreachable\n");
                    break;
                }
                split(u, v);
                printf("%.8Le\n", cal(v, x));
                break;
            default:
                break;
        }
    }
    return 0;
}

long double val[maxn][maxl];

inline void taylor(const int& p, const int& f, const long double& a, const long double& b) {
    long double P, c, s, e;
    switch (f) {
        case 1:
            P = 1, s = sinl(b), c = cosl(b);
            for (int j = 0; j < maxl; j++)
                val[p][j] = (j & 1 ? c : s) * (j & 2 ? -1 : 1) * P / fac[j], P *= a;
            break;
        case 2:
            P = 1, e = expl(b);
            for (int j = 0; j < maxl; j++) val[p][j] = e * P / fac[j], P *= a;
            break;
        case 3:
            val[p][1] = a, val[p][0] = b;
            for (int j = 2; j < maxl; j++) val[p][j] = 0;
            break;
        default:
            break;
    }
    return;
}

int son[maxn][2], fa[maxn];
long double func[maxn][maxl];
bool tag[maxn];

inline long double cal(const int& p, const long double& x) {
    long double ret = 0, P = 1;
    for (int i = 0; i < maxl; i++) ret += func[p][i] * P, P *= x;
    return ret;
}

inline int get(const int& u) { return son[fa[u]][1] == u; }

inline bool isroot(const int& u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

inline void pushup(const int& u) {
    for (int i = 0; i < maxl; i++) func[u][i] = func[son[u][0]][i] + func[son[u][1]][i] + val[u][i];
    return;
}

inline void mark(const int& u) {
    tag[u] ^= 1, son[u][0] ^= son[u][1] ^= son[u][0] ^= son[u][1];
    return;
}

inline void pushdown(const int& u) {
    if (!tag[u])
        return;
    tag[u] = false;
    if (son[u][0])
        mark(son[u][0]);
    if (son[u][1])
        mark(son[u][1]);
    return;
}

void update(const int& u) {
    if (!isroot(u))
        update(fa[u]);
    pushdown(u);
    return;
}

inline void rotate(const int& u) {
    int x = fa[u], y = fa[x], k = get(u);
    fa[u] = y;
    if (!isroot(x))
        son[y][get(x)] = u;
    son[x][k] = son[u][k ^ 1];
    fa[son[u][k ^ 1]] = x;
    son[u][k ^ 1] = x;
    fa[x] = u;
    pushup(x);
    pushup(u);
    pushup(y);
    return;
}

inline void splay(const int& u) {
    update(u);
    for (int f; f = fa[u], !isroot(u); rotate(u))
        if (!isroot(f))
            rotate(get(u) == get(f) ? f : u);
    pushup(u);
    return;
}

inline void access(int u) {
    for (int f = 0; u; u = fa[f = u]) splay(u), son[u][1] = f, pushup(u);
    return;
}

inline void makeroot(const int& u) {
    access(u);
    splay(u);
    mark(u);
    return;
}

inline int find(int u) {
    access(u);
    splay(u);
    while (son[u][0]) pushdown(u), u = son[u][0];
    splay(u);
    return u;
}

inline void link(const int& u, const int& v) {
    makeroot(u);
    if (find(v) != u)
        fa[u] = v;
    return;
}

inline void split(const int& u, const int& v) {
    makeroot(u);
    access(v);
    splay(v);
    return;
}

inline void cut(const int& u, const int& v) {
    makeroot(u);
    if (find(v) == u && fa[v] == u && !son[v][0])
        fa[v] = son[u][1] = 0, pushup(u);
    return;
}
