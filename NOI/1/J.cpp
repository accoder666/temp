#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxa = 210, maxb = 3010;
int x[maxa], y[maxb];
struct edge {
    int to, nxt, v, val;
};
vector<edge> G;
int head[maxb];
bool G2[maxa][maxb];
inline void AddEdge(int, int);
inline int dinic(int, int);
int flag[maxb], tim;
int b;

int main() {
    int a, m, u, v;
    int ans, tmp, cnt;
    scanf("%d %d %d", &a, &b, &m);
    for (int i = 1; i <= a; i++) scanf("%d", x + i);
    for (int i = 1; i <= b; i++) scanf("%d", y + i);
    while (m--) scanf("%d %d", &u, &v), G2[u][v] = true;
    for (int i = 1; i <= b; i++)
        if (y[i] & 1)
            for (int j = 1; j <= b; j++)
                if (!(y[j] & 1) && !(__builtin_popcount(y[i] | y[j]) & 1))
                    AddEdge(i, j);
    for (int i = 1; i <= b; i++)
        if (y[i] & 1)
            AddEdge(b + 1, i);
        else
            AddEdge(i, b + 2);
    ans = b - dinic(b + 1, b + 2);
    for (int i = 1; i <= a; i++) {
        tim++, cnt = 0;
        for (int j = 1; j <= b; j++)
            if (G2[i][j])
                flag[j] = tim, cnt++;
        flag[b + 1] = flag[b + 2] = tim;
        if ((tmp = (cnt - dinic(b + 1, b + 2)) + 1) > ans)
            ans = tmp;
    }
    for (int i = 1; i <= a; i++)
        for (int j = i + 1; j <= a; j++)
            if ((x[i] ^ x[j]) & 1) {
                tim++, cnt = 0;
                for (int k = 1; k <= b; k++)
                    if (G2[i][k] && G2[j][k])
                        flag[k] = tim, cnt++;
                flag[b + 1] = flag[b + 2] = tim;
                if ((tmp = (cnt - dinic(b + 1, b + 2)) + 2) > ans)
                    ans = tmp;
            }
    printf("%d\n", ans);
    return 0;
}

inline void AddEdge(const int u, const int v) {
    G.push_back({ v, head[u], 1, 0 }), head[u] = G.size() - 1;
    G.push_back({ u, head[v], 0, 0 }), head[v] = G.size() - 1;
    return;
}

int d[maxb];

queue<int> Q;
inline bool bfs(const int s, const int t) {
    memset(d, 0, sizeof(d));
    d[s] = 1, Q.push(s);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = head[u]; i; i = G[i].nxt)
            if (G[i].val && !d[G[i].to])
                d[G[i].to] = d[u] + 1, Q.push(G[i].to);
    }
    return d[t];
}

int cur[maxb];

int dfs(const int u, const int t, int flow) {
    if (!flow || u == t)
        return flow;
    int ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(G[i].to, t, G[i].val < flow ? G[i].val : flow))) {
            ret += tmp, G[i].val -= tmp, G[i ^ 1].val += tmp, flow -= tmp;
            if (!flow)
                break;
        }
    return ret;
}

inline int dinic(const int s, const int t) {
    for (int i = 1; i <= b + 2; i++)
        for (int j = head[i]; j; j = G[j].nxt) {
            if (flag[i] == tim && flag[G[j].to] == tim)
                G[j].val = G[j].v;
            else
                G[j].val = 0;
        }
    int ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, t, INT_MAX);
    }
    return ret;
}
