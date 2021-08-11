#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 100010, sigma_size = 10;
inline void dfs(int, int, int);
inline long long solve(void);
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], Gcnt;
int deg[maxn];
int col[maxn];

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; i++) scanf("%d", col + i);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        G[++Gcnt] = { v, head[u] }, head[u] = Gcnt;
        G[++Gcnt] = { u, head[v] }, head[v] = Gcnt;
        deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            dfs(i, 0, 1);
    printf("%lld\n", solve());
    return 0;
}

const int maxl = 2000010;
int len[maxl << 1], fa[maxl << 1];
int nxt[maxl << 1][sigma_size];
int cnt = 1;

inline int insert(const int last, const int d) {
    int cur = nxt[last][d];
    if (len[cur])
        return cur;
    len[cur] = len[last] + 1;
    int u = fa[last];
    while (u && !nxt[u][d]) nxt[u][d] = cur, u = fa[u];
    if (!u) {
        fa[cur] = 1;
        return cur;
    }
    int v = nxt[u][d];
    if (len[u] + 1 == len[v]) {
        fa[cur] = v;
        return cur;
    }
    int c = ++cnt;
    len[c] = len[u] + 1, fa[c] = fa[v];
    for (int i = 0; i < sigma_size; i++)
        if (len[nxt[v][i]])
            nxt[c][i] = nxt[v][i];
    while (u && nxt[u][d] == v) nxt[u][d] = c, u = fa[u];
    fa[v] = fa[cur] = c;
    return cur;
}

queue<pair<int, int>> Q;
inline void build(void) {
    for (int i = 0; i < sigma_size; i++)
        if (nxt[1][i])
            Q.push(make_pair(1, i));
    int last;
    while (!Q.empty()) {
        last = insert(Q.front().first, Q.front().second), Q.pop();
        for (int i = 0; i < sigma_size; i++)
            if (nxt[last][i])
                Q.push(make_pair(last, i));
    }
    return;
}

inline void dfs(const int u, const int f, const int last) {
    if (!nxt[last][col[u]])
        nxt[last][col[u]] = ++cnt;
    int cur = nxt[last][col[u]];
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != f)
            dfs(G[i].to, u, cur);
    return;
}

inline long long solve(void) {
    build();
    long long ret = 0;
    for (int i = 1; i <= cnt; i++) ret += len[i] - len[fa[i]];
    return ret;
}
