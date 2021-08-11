//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 300010, maxlg = 18;
struct edge {
    int to, nxt;
};
edge G[maxn], G2[maxn];
int head[maxn], cnt;
int head2[maxn], cnt2;
int f[maxn], d[maxn];
int anc[maxn][maxlg], lg[maxn];
void Dfs(int);
int c;
void dfs(int);
int n, ans;

int main() {
    int t;
    scanf("%d", &t);
    int a;
    for (int i = 2; i <= maxn - 10; i++) lg[i] = lg[i >> 1] + 1;
    while (t--) {
        scanf("%d", &n);
        cnt = cnt2 = c = 0;
        for (int i = 1; i <= n; i++) head[i] = head2[i] = 0;
        for (int i = 2; i <= n; i++) {
            scanf("%d", &a);
            G[++cnt] = { i, head[a] }, head[a] = cnt;
        }
        for (int i = 2; i <= n; i++) {
            scanf("%d", f + i);
            d[i] = d[f[i]] + 1, anc[i][0] = f[i];
            G2[++cnt2] = { i, head2[f[i]] }, head2[f[i]] = cnt2;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= lg[d[i]]; j++) anc[i][j] = anc[anc[i][j - 1]][j - 1];
        Dfs(1), ans = 0, dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}

int dfn[maxn], l[maxn], r[maxn];

void Dfs(const int u) {
    dfn[u] = l[u] = ++c;
    for (int i = head2[u]; i; i = G2[i].nxt) Dfs(G2[i].to);
    r[u] = c;
    return;
}

int C[maxn];

inline int lowbit(const int x) { return x & (-x); }

inline void modify(const int p, const int v) {
    for (int i = p; i <= n + 1; i += lowbit(i)) C[p] += v;
    return;
}

inline int query(const int p) {
    int ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret += C[i];
    return ret;
}

int L[maxn], Lc;
void dfs(const int u) {
    modify(dfn[u], 1), L[++Lc] = u;
    if (!head[u]) {
        int tmp = 0;
        for (int i = 1; i <= Lc; i++)
            if (query(r[L[i]]) == query(l[L[i]]))
                tmp++;
        if (tmp > ans)
            ans = tmp;
    } else
        for (int i = head[u]; i; i = G[i].nxt) dfs(G[i].to);
    modify(dfn[u], -1), Lc--;
    return;
}
