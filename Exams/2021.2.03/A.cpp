#include <cstdio>
using namespace std;

const int maxn = 300010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int c[maxn];
void solve(const int&, const int& val = 0);
long long ans[maxn];
int n;

int main() {
    freopen("mushroom.in", "r", stdin);
    freopen("mushroom.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        G[++cnt] = { v, head[u] }, head[u] = cnt;
        G[++cnt] = { u, head[v] }, head[v] = cnt;
    }
    solve(1, n);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}

bool vis[maxn];
int siz[maxn], root;

int value, tot;
void get(const int& u, const int& fa = 0) {
    int m = 0;
    siz[u] = 1;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && G[i].to != fa) {
            get(G[i].to, u);
            siz[u] += siz[G[i].to];
            if (m < siz[G[i].to])
                m = siz[G[i].to];
        }
    if (m < tot - siz[u])
        m = tot - siz[u];
    if (m < value)
        root = u, value = m;
    return;
}

long long count[maxn], col[maxn], sum;

void dfs1(const int& u, const int& fa = 0) {
    siz[u] = 1;
    count[c[u]]++;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && G[i].to != fa) {
            dfs1(G[i].to, u);
            siz[u] += siz[G[i].to];
        }
    if (!(--count[c[u]]))
        sum += siz[u], col[c[u]] += siz[u];
    return;
}

void dfs2(const int& u, const int& fa, const int& coeff) {
    count[c[u]]++;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && G[i].to != fa)
            dfs2(G[i].to, u, coeff);
    if (!(--count[c[u]]))
        sum += coeff * siz[u], col[c[u]] += coeff * siz[u];
    return;
}

long long num, s;

void dfs3(const int& u, const int& fa) {
    if (!(count[c[u]]++))
        sum -= col[c[u]], num++;
    ans[u] += sum + s * num;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && G[i].to != fa)
            dfs3(G[i].to, u);
    if (!(--count[c[u]]))
        sum += col[c[u]], num--;
    return;
}

void dfs4(const int& u, const int& fa = 0) {
    count[c[u]] = col[c[u]] = 0;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to] && G[i].to != fa)
            dfs4(G[i].to, u);
    return;
}

void dfs(const int& u) {
    dfs1(u);
    ans[u] += sum;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to]) {
            count[c[u]]++;
            sum -= siz[G[i].to], col[c[u]] -= siz[G[i].to];
            dfs2(G[i].to, u, -1);
            count[c[u]]--;
            s = siz[u] - siz[G[i].to];
            dfs3(G[i].to, u);
            count[c[u]]++;
            sum += siz[G[i].to], col[c[u]] += siz[G[i].to];
            dfs2(G[i].to, u, 1);
            count[c[u]]--;
        }
    sum = num = 0;
    dfs4(u);
    vis[u] = true;
    for (int i = head[u]; i; i = G[i].nxt)
        if (!vis[G[i].to])
            solve(G[i].to);
    return;
}

inline void solve(const int& u, const int& val) {
    root = 0, value = n, tot = val + siz[u];
    get(u), dfs(root);
    return;
}
