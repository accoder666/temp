// fixme

#pragma GCC optimize("Ofast")

#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 10010;
inline void AddEdge(const int&, const int&, const int&);
struct edge {
    int to, nxt, val;
};
edge G[maxn << 1];
int head[maxn], cnt;
int dist[maxn], p[maxn];
bool vis[maxn];
deque<int> Q;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int x, a, b, c;
    bool flag = false;
    while (m--) {
        scanf("%d %d %d", &x, &a, &b);
        switch (x) {
            case 1:
                scanf("%d", &c);
                AddEdge(a, b, c);
                if (a == b) {
                    flag = true;
                    break;
                }
                break;
            case 2:
                scanf("%d", &c);
                AddEdge(b, a, -c);
                break;
            case 3:
                AddEdge(a, b, 0);
                AddEdge(b, a, 0);
                break;
            default:
                break;
        }
    }
    if (flag) {
        printf("No\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) vis[i] = true, Q.push_back(i);
    int u;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop_front();
        vis[u] = false;
        for (int i = head[u]; i; i = G[i].nxt)
            if (dist[G[i].to] < dist[u] + G[i].val) {
                dist[G[i].to] = dist[u] + G[i].val, p[G[i].to] = p[u] + 1;
                if (p[G[i].to] == n) {
                    flag = true;
                    break;
                }
                if (!vis[G[i].to]) {
                    vis[G[i].to] = true;
                    if (!Q.empty() && dist[G[i].to] < dist[Q.front()])
                        Q.push_front(G[i].to);
                    else
                        Q.push_back(G[i].to);
                }
            }
        if (flag)
            break;
    }
    printf(flag ? "No\n" : "Yes\n");
    return 0;
}

inline void AddEdge(const int& u, const int& v, const int& val) {
    G[++cnt] = { v, head[u], val }, head[u] = cnt;
    return;
}
