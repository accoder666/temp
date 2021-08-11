#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

const int maxn = 100010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
inline void init(void);
inline void insert(int, int, int, int);
inline long double solve(void);
int n;

int main() {
    int m;
    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a] }, head[a] = cnt;
        G[++cnt] = { a, head[b] }, head[b] = cnt;
    }
    init();
    int t, c, v, u;
    while (m--) {
        scanf("%d %d %d %d", &t, &c, &v, &u);
        insert(t, c, v, u);
    }
    long double ans = solve();
    if (ans < 0)
        printf("-1\n");
    else
        printf("%.30Lf\n", ans);
    return 0;
}

int fa[maxn], dep[maxn], siz[maxn], son[maxn];
int top[maxn];

void dfs1(const int u) {
    siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u]) {
            fa[G[i].to] = u;
            dep[G[i].to] = dep[u] + 1;
            dfs1(G[i].to);
            siz[u] += siz[G[i].to];
            if (siz[G[i].to] > siz[son[u]])
                son[u] = G[i].to;
        }
    return;
}

void dfs2(const int u) {
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa[u] && G[i].to != son[u])
            top[G[i].to] = G[i].to, dfs2(G[i].to);
    return;
}

inline void init(void) {
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    return;
}

inline int dist(int u, int v) {
    int tmp = dep[u] + dep[v];
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            u ^= v ^= u ^= v;
        u = fa[top[u]];
    }
    return tmp - ((dep[u] < dep[v] ? dep[u] : dep[v]) << 1);
}

class fraction {
public:
    inline fraction(long long a = 0, long long b = 1) {
        long long g = gcd(a > 0 ? a : -a, b > 0 ? b : -b);
        if (b < 0)
            g = -g;
        this->a = a / g, this->b = b / g;
    }
    inline fraction operator+(const fraction rhs) const { return fraction(a * rhs.b + b * rhs.a, b * rhs.b); }
    inline fraction operator-(const fraction rhs) const { return fraction(a * rhs.b - b * rhs.a, b * rhs.b); }
    inline fraction operator*(const fraction rhs) const { return fraction(a * rhs.a, b * rhs.b); }
    inline fraction operator/(const fraction rhs) const { return fraction(a * rhs.b, b * rhs.a); }
    inline fraction operator+=(const fraction rhs) { return *this = *this + rhs; }
    inline fraction operator-=(const fraction rhs) { return *this = *this - rhs; }
    inline fraction operator-(void) const { return fraction(-a, b); }
    inline bool operator<(const fraction rhs) const { return cmp(*this, rhs) < 0; }
    inline bool operator>(const fraction rhs) const { return cmp(*this, rhs) > 0; }
    inline bool operator<=(const fraction rhs) const { return cmp(*this, rhs) <= 0; }
    inline bool operator>=(const fraction rhs) const { return cmp(*this, rhs) >= 0; }
    inline bool operator==(const fraction rhs) const { return !cmp(*this, rhs); }
    inline operator long double(void) const { return (long double)a / b; }

private:
    long long a, b;
    static long long gcd(const long long x, const long long y) {
        if (!y)
            return x;
        return gcd(y, x % y);
    }
    static int cmp(const fraction x, const fraction y) {
        long long val = x.a * y.b - x.b * y.a;
        return !val ? 0 : (val < 0 ? -1 : 1);
    }
};

fraction x;

struct line {
public:
    fraction k, b, l, r;
    inline line(void) = default;
    inline line(const fraction k, const fraction b, const fraction l, const fraction r)
        : k(k), b(b), l(l), r(r) {}
    inline bool operator<(const line rhs) const {
        fraction v1 = f(x), v2 = rhs.f(x);
        if (v1 == v2)
            return l == rhs.l ? (r == rhs.r ? k < rhs.k : r < rhs.r) : l < rhs.l;
        return v1 < v2;
    }

private:
    inline fraction f(const fraction x) const { return k * x + b; }
};

vector<line> h[maxn], l[maxn];

inline void insert(const int t, const int c, int u, int v) {
    fraction S = t, V = c;
    fraction E = (fraction)t + (fraction)dist(u, v) / V;
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]]) {
            h[top[u]].push_back(
                line(-V, (fraction)dep[u] + V * S, S, S + (fraction)(dep[u] - dep[top[u]]) / V));
            S += (fraction)(dep[u] - dep[top[u]]) / V, u = top[u];
            l[u].push_back(line(-V, (fraction)dep[u] + V * S, S, S + (fraction)(dep[u] - dep[fa[u]]) / V));
            S += (fraction)(dep[u] - dep[fa[u]]) / V, u = fa[u];
        } else {
            h[top[v]].push_back(
                line(V, (fraction)dep[v] - V * E, E - (fraction)(dep[v] - dep[top[v]]) / V, E));
            E -= (fraction)(dep[v] - dep[top[v]]) / V, v = top[v];
            l[v].push_back(line(V, (fraction)dep[v] - V * E, E - (fraction)(dep[v] - dep[fa[v]]) / V, E));
            E -= (fraction)(dep[v] - dep[fa[v]]) / V, v = fa[v];
        }
    if (dep[u] > dep[v])
        h[top[u]].push_back(line(-V, (fraction)dep[u] + V * S, S, E));
    else
        h[top[v]].push_back(line(V, (fraction)dep[v] - V * E, S, E));
    return;
}

const long long lim = 10000000;

inline fraction intersection(const line l1, const line l2) {
    if (l1.k == l2.k) {
        if (l1.b == l2.b)
            return l1.l > l2.l ? l1.l : l2.l;
        return lim;
    }
    fraction ret = (l2.b - l1.b) / (l1.k - l2.k);
    if (l1.l <= ret && ret <= l1.r && l2.l <= ret && ret <= l2.r)
        return ret;
    return lim;
}

struct event {
    event(const line l, const bool f) : l(l), f(f) {}
    line l;
    bool f;
    inline bool operator<(const event rhs) const {
        fraction a = f ? l.l : l.r, b = rhs.f ? rhs.l.l : rhs.l.r;
        return a == b ? f > rhs.f : a < b;
    }
};

vector<event> V;
multiset<line> S;
inline void Solve(vector<line> vec, fraction& cur) {
    S.clear(), V.clear();
    for (const auto& i : vec) V.push_back(event(i, true)), V.push_back(event(i, false));
    sort(V.begin(), V.end());
    multiset<line>::iterator it;
    fraction tmp;
    for (const auto& i : V) {
        x = i.f ? i.l.l : i.l.r;
        if (x >= cur)
            break;
        if (i.f) {
            it = S.insert(i.l);
            if (it != S.begin()) {
                tmp = intersection(*prev(it), *it);
                if (tmp < cur)
                    cur = tmp;
            }
            if (next(it) != S.end()) {
                tmp = intersection(*it, *next(it));
                if (tmp < cur)
                    cur = tmp;
            }
        } else {
            it = S.lower_bound(i.l);
            if (it != S.begin() && next(it) != S.end()) {
                tmp = intersection(*prev(it), *next(it));
                if (tmp < cur)
                    cur = tmp;
            }
            S.erase(it);
        }
    }
    return;
}

inline long double solve(void) {
    fraction ret = lim;
    for (int i = 1; i <= n; i++)
        if (i == top[i])
            Solve(h[i], ret), Solve(l[i], ret);
    if (ret == (fraction)lim)
        return -1;
    return ret;
}