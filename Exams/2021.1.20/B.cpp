#include <cstdio>
#include <list>
#include <unordered_set>
using namespace std;

const int maxn = 200010;
struct edge {
    int from, to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int pre[maxn], nxt[maxn], h[maxn];
int p[maxn], rk[maxn];
int label[maxn];
bool vis[maxn];
int s[maxn];
unordered_set<int> M[maxn];

int main() {
    freopen("tu.in", "r", stdin);
    freopen("tu.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        G[++cnt] = { u, v, head[u] }, head[u] = cnt;
        G[++cnt] = { v, u, head[v] }, head[v] = cnt;
        M[u].insert(v), M[v].insert(u);
    }
    for (int i = 1; i <= n; i++) pre[i - 1] = i, nxt[i] = i - 1;
    h[0] = n, pre[0] = 0;
    int c = n, now = 0;
    while (c) {
        p[c] = h[now];
        rk[p[c]] = c;
        h[now] = nxt[h[now]];
        pre[p[c]] = nxt[p[c]] = 0;
        pre[h[now]] = 0;
        vis[p[c]] = true;
        for (int i = head[p[c]]; i; i = G[i].nxt)
            if (!vis[G[i].to]) {
                u = G[i].to;
                if (h[label[u]] == u)
                    h[label[u]] = nxt[u];
                pre[nxt[u]] = pre[u], nxt[pre[u]] = nxt[u];
                pre[u] = nxt[u] = 0;
                label[u]++;
                pre[h[label[u]]] = u, nxt[u] = h[label[u]];
                h[label[u]] = u;
            }
        c--;
        if (h[now + 1])
            now++;
        while (now && !h[now]) now--;
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        c = 0, u = p[i];
        for (int j = head[u]; j; j = G[j].nxt)
            if (rk[u] < rk[G[j].to]) {
                s[++c] = G[j].to;
                if (rk[s[c]] < rk[s[1]])
                    s[1] ^= s[c] ^= s[1] ^= s[c];
            }
        for (int j = 2; j <= c; j++)
            if (!M[s[1]].count(s[j])) {
                flag = false;
                break;
            }
        if (!flag)
            break;
    }
    if (flag)
        for (int i = 1; i <= m; i++) printf("%d", rk[G[i << 1].from] < rk[G[i << 1].to]);
    else
        printf("-1");
    printf("\n");
    return 0;
}
