#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 5010;
inline int gcd(int, int);
struct node {
    int x, y, v;
    inline bool operator<(const node& rhs) const { return v > rhs.v; }
};
node t[maxn];
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
bool vis[maxn];
int dist[maxn];
queue<int> Q;
int find(const int&);
int fa[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d %d %d", &t[i].x, &t[i].y, &t[i].v);
    sort(t + 1, t + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    int S, T;
    scanf("%d %d", &S, &T);
    int p;
    for (p = 1; p <= m; p++) {
        fa[find(t[p].x)] = find(t[p].y);
        if (find(S) == find(T))
            break;
        G[++cnt] = { t[p].x, head[t[p].y], t[p].v }, head[t[p].y] = cnt;
        G[++cnt] = { t[p].y, head[t[p].x], t[p].v }, head[t[p].x] = cnt;
    }
    if (p == m + 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[S] = 0, vis[S] = true, Q.push(S);
    pair<int, int> ans = make_pair(INT_MAX, 1), tmp;
    int u, g;
    for (p--; p <= m; p++) {
        G[++cnt] = { t[p].x, head[t[p].y], t[p].v }, head[t[p].y] = cnt;
        G[++cnt] = { t[p].y, head[t[p].x], t[p].v }, head[t[p].x] = cnt;
        Q.push(t[p].x), Q.push(t[p].y);
        vis[t[p].x] = vis[t[p].y] = true;
        while (!Q.empty()) {
            u = Q.front();
            Q.pop();
            vis[u] = false;
            for (int i = head[u]; i; i = G[i].nxt)
                if (dist[G[i].to] > max(dist[u], G[i].val)) {
                    dist[G[i].to] = max(dist[u], G[i].val);
                    if (!vis[G[i].to])
                        vis[G[i].to] = true, Q.push(G[i].to);
                }
        }
        g = gcd(t[p].v, dist[T]);
        tmp = make_pair(dist[T] / g, t[p].v / g);
        if ((long long)tmp.first * ans.second < (long long)tmp.second * ans.first)
            ans = tmp;
    }
    if (ans.second == 1)
        printf("%d\n", ans.first);
    else
        printf("%d/%d\n", ans.first, ans.second);
    return 0;
}

inline int gcd(int a, int b) {
    if (!a)
        return b;
    if (!b)
        return a;
    int s = 0;
    while (!((a | b) & 1)) s++, a >>= 1, b >>= 1;
    while (!(a & 1)) a >>= 1;
    do {
        while (!(b & 1)) b >>= 1;
        if (a > b)
            a ^= b ^= a ^= b;
        b -= a;
    } while (b);
    return a << s;
}

int find(const int& u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
