#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 200010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1], T[maxn << 2];
int headG[maxn], headT[maxn << 1], cntG, cntT, cnt, c;
void build(const int&);
struct query {
    int p, q, nxt, lca;
};
query Q[maxn << 1];
int headQ[maxn], cntQ = 1;
void tarjan(const int&);
int val[maxn << 1], fa[maxn << 1];
void dfs(const int&);

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    int u, v;
    while (m--) {
        scanf("%d %d", &u, &v);
        G[++cntG] = { v, headG[u] }, headG[u] = cntG;
        G[++cntG] = { u, headG[v] }, headG[v] = cntG;
    }
    c = n;
    build(1);
    while (q--) {
        scanf("%d %d", &u, &v);
        Q[++cntQ] = { u, v, headQ[u], 0 }, headQ[u] = cntQ;
        Q[++cntQ] = { v, u, headQ[v], 0 }, headQ[v] = cntQ;
    }
    tarjan(1);
    for (int i = 0; i <= cntQ; i += 2) val[Q[i].p]++, val[Q[i].q]++, val[Q[i].lca]--, val[fa[Q[i].lca]]--;
    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d\n", val[i]);
    return 0;
}

stack<int> S;
int dfn[maxn], low[maxn];
void build(const int& u) {
    dfn[u] = low[u] = ++cnt, S.push(u);
    for (int i = headG[u]; i; i = G[i].nxt)
        if (!dfn[G[i].to]) {
            build(G[i].to);
            low[u] = min(low[u], low[G[i].to]);
            if (low[G[i].to] == dfn[u]) {
                c++;
                while (true) {
                    T[++cntT] = { c, headT[S.top()] }, headT[S.top()] = cntT;
                    T[++cntT] = { S.top(), headT[c] }, headT[c] = cntT;
                    if (S.top() == G[i].to)
                        break;
                    S.pop();
                }
                S.pop();
                T[++cntT] = { c, headT[u] }, headT[u] = cntT;
                T[++cntT] = { u, headT[c] }, headT[c] = cntT;
            }
        } else
            low[u] = min(low[u], dfn[G[i].to]);
    return;
}

int f[maxn << 1];

int find(const int& u) { return f[u] == u ? u : f[u] = find(f[u]); }

bool vis[maxn << 1];
void tarjan(const int& u) {
    f[u] = u, vis[u] = true;
    for (int i = headT[u]; i; i = T[i].nxt)
        if (!vis[T[i].to])
            tarjan(T[i].to), f[T[i].to] = fa[T[i].to] = u;
    for (int i = headQ[u]; i; i = Q[i].nxt)
        if (vis[Q[i].q])
            Q[i].lca = Q[i ^ 1].lca = find(Q[i].q);
    return;
}

void dfs(const int& u) {
    for (int i = headT[u]; i; i = T[i].nxt)
        if (T[i].to != fa[u])
            dfs(T[i].to), val[u] += val[T[i].to];
    return;
}
