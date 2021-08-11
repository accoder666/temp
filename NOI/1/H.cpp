#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 510;
struct edge {
    int to, nxt, val;
};
edge G[maxn * maxn << 2];
int head[maxn * maxn], cnt;
inline int get(int, int);
inline void AddEdge(int, int, int);
int id[maxn][maxn];
struct node {
    int u, d;
    inline bool operator<(const node rhs) const { return d > rhs.d; }
};
priority_queue<node> Q;
int dis[maxn * maxn];
bool vis[maxn * maxn];
int n, c;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) id[i][j] = ++c;
    c++;
    int v;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &v);
            AddEdge(get(i, j), get(i - 1, j), v);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) {
            scanf("%d", &v);
            AddEdge(get(i, j - 1), get(i, j), v);
        }
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &v);
            AddEdge(get(i - 1, j), get(i, j), v);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) {
            scanf("%d", &v);
            AddEdge(get(i, j), get(i, j - 1), v);
        }
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0, Q.push({ 0, 0 });
    int u;
    while (!Q.empty()) {
        u = Q.top().u, Q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i; i = G[i].nxt)
            if (dis[G[i].to] > dis[u] + G[i].val) {
                dis[G[i].to] = dis[u] + G[i].val;
                Q.push({ G[i].to, dis[G[i].to] });
            }
    }
    printf("%d\n", dis[c]);
    return 0;
}

inline int get(const int x, const int y) {
    if (id[x][y])
        return id[x][y];
    if (x > n || y < 1)
        return 0;
    return c;
}

inline void AddEdge(const int u, const int v, const int val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    return;
}
