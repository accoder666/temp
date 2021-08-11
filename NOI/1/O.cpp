#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 100010;
inline void AddEdge(const int&, const int&, const int&);
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
int dist[maxn], c[maxn];
bool vis[maxn];
queue<int> Q;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int x, a, b;
    bool flag = false;
    while (k--) {
        scanf("%d %d %d", &x, &a, &b);
        switch (x) {
            case 1:
                AddEdge(a, b, 0);
                AddEdge(b, a, 0);
                break;
            case 2:
                AddEdge(a, b, 1);
                if (a == b) {
                    flag = true;
                    break;
                }
                break;
            case 3:
                AddEdge(b, a, 0);
                break;
            case 4:
                AddEdge(b, a, 1);
                if (a == b) {
                    flag = true;
                    break;
                }
                break;
            case 5:
                AddEdge(a, b, 0);
                break;
            default:
                break;
        }
        if (flag)
            break;
    }
    if (flag) {
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        dist[i] = 1, vis[i] = true;
        Q.push(i);
    }
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = G[i].nxt)
            if (dist[G[i].to] < dist[u] + G[i].val) {
                dist[G[i].to] = dist[u] + G[i].val, c[G[i].to] = c[u] + 1;
                if (c[G[i].to] == n) {
                    flag = true;
                    break;
                }
                if (!vis[G[i].to]) {
                    vis[G[i].to] = true;
                    Q.push(G[i].to);
                }
            }
        if (flag)
            break;
    }
    if (flag) {
        printf("-1\n");
        return 0;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) ans += dist[i];
    printf("%lld\n", ans);
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    return;
}
