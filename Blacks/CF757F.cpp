#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 300010, maxlg = 18;
struct edge {
    int to, nxt;
    long long val;
};
edge G[maxn << 1], G2[maxn];
int head[maxn], cnt;
int head2[maxn], cnt2;
struct node {
    int u;
    long long d;
    inline bool operator<(const node& rhs) const { return d > rhs.d; }
};
priority_queue<node> PQ;
long long dis[maxn];
bool vis[maxn];
int deg[maxn];
edge T[maxn];
int headT[maxn], cntT;
queue<int> Q;
int lg[maxn];
int anc[maxn][maxlg], dep[maxn];
inline int lca(int, int);
void dfs(const int&);
int siz[maxn];

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    int u, v, w;
    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        G[++cnt] = { v, head[u], w }, head[u] = cnt;
        G[++cnt] = { u, head[v], w }, head[v] = cnt;
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, PQ.push({ s, 0 });
    while (!PQ.empty()) {
        u = PQ.top().u, PQ.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = G[i].nxt)
            if (dis[G[i].to] > dis[u] + G[i].val) {
                dis[G[i].to] = dis[u] + G[i].val;
                PQ.push({ G[i].to, dis[G[i].to] });
            }
    }
    for (int i = 1; i <= n; i++) {
        anc[i][0] = -1;
        for (int j = head[i]; j; j = G[j].nxt)
            if (dis[G[j].to] == dis[i] + G[j].val)
                G2[++cnt2] = { G[j].to, head2[i] }, head2[i] = cnt2, deg[G[j].to]++;
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    Q.push(s);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        if (u != s) {
            dep[u] = dep[anc[u][0]] + 1;
            T[++cntT] = { u, headT[anc[u][0]], 0 }, headT[anc[u][0]] = cntT;
            for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
        }
        for (int i = head2[u]; i; i = G2[i].nxt)
            if (deg[G2[i].to]) {
                anc[G2[i].to][0] = lca(anc[G2[i].to][0], u);
                if (!--deg[G2[i].to])
                    Q.push(G2[i].to);
            }
    }
    dfs(s);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (i != s && siz[i] > ans)
            ans = siz[i];
    printf("%d\n", ans);
    return 0;
}

inline int lca(int u, int v) {
    if (u == -1)
        return v;
    if (dep[u] < dep[v])
        u ^= v ^= u ^= v;
    while (dep[u] != dep[v]) u = anc[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

void dfs(const int& u) {
    siz[u] = 1;
    for (int i = headT[u]; i; i = T[i].nxt) dfs(T[i].to), siz[u] += siz[T[i].to];
    return;
}
