#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 1010;
struct edge {
    int to, nxt, val;
};
edge G[maxn * maxn * 6];
int head[maxn * maxn << 1], cnt;
inline void AddEdge(int, int, int);
int id[maxn][maxn][2];
struct node {
    int u, d;
    inline bool operator<(const node rhs) const { return d > rhs.d; }
};
priority_queue<node> Q;
int dis[maxn * maxn << 1];
bool vis[maxn * maxn << 1];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int c = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) id[i][j][0] = ++c, id[i][j][1] = ++c;
    c++;
    int v;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) {
            scanf("%d", &v);
            if (i == 1)
                AddEdge(0, id[i][j][0], v);
            else if (i == n)
                AddEdge(id[i - 1][j][1], c, v);
            else
                AddEdge(id[i - 1][j][1], id[i][j][0], v);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &v);
            if (j == 1)
                AddEdge(id[i][j][1], c, v);
            else if (j == m)
                AddEdge(0, id[i][j - 1][0], v);
            else
                AddEdge(id[i][j - 1][0], id[i][j][1], v);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) {
            scanf("%d", &v);
            AddEdge(id[i][j][0], id[i][j][1], v);
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

inline void AddEdge(const int u, const int v, const int val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    G[++cnt] = { u, head[v], val }, head[v] = cnt;
    return;
}
