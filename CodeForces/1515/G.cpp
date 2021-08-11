#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 200010;
struct edge {
    int to, nxt;
    long long val;
};
edge G[maxn];
int head[maxn], cnt;
long long gcd(long long, long long);
void tarjan(int);
void build(int);
int bel[maxn];
long long r[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    long long l;
    while (m--) {
        scanf("%d %d %lld", &a, &b, &l);
        G[++cnt] = { b, head[a], l }, head[a] = cnt;
    }
    for (int i = 1; i <= n; i++)
        if (!bel[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (!r[bel[i]])
            build(i);
    int q;
    scanf("%d", &q);
    int v;
    long long s, t;
    while (q--) {
        scanf("%d %lld %lld", &v, &s, &t);
        printf(!(s % gcd(r[bel[v]], t)) ? "YES\n" : "NO\n");
    }
    return 0;
}

long long gcd(const long long a, const long long b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

stack<int> S;
int dfn[maxn], low[maxn];
void tarjan(const int u) {
    static int clock = 0, scc_cnt = 0;
    S.push(u);
    dfn[u] = low[u] = ++clock;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!dfn[G[i].to]) {
            tarjan(G[i].to);
            if (low[u] > low[G[i].to])
                low[u] = low[G[i].to];
        } else if (!bel[G[i].to] && low[u] > dfn[G[i].to])
            low[u] = dfn[G[i].to];
    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do bel[v = S.top()] = scc_cnt, S.pop();
        while (v != u);
    }
    return;
}

bool vis[maxn];
long long dep[maxn];
void build(const int u) {
    long long tmp;
    vis[u] = true;
    for (int i = head[u]; i; i = G[i].nxt)
        if (bel[u] == bel[G[i].to]) {
            if (vis[G[i].to])
                tmp = dep[u] + G[i].val - dep[G[i].to], r[bel[u]] = gcd(r[bel[u]], tmp > 0 ? tmp : -tmp);
            else
                dep[G[i].to] = dep[u] + G[i].val, build(G[i].to);
        }
    return;
}
