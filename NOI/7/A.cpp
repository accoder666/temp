#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 5010;
struct edge {
    int to, nxt;
    long long val;
};
edge G[maxn << 1];
int head[maxn], cnt = 1;
int cur[maxn], d[maxn];
queue<int> Q;
long long dfs(const int&, long long);
int n, m, s, t;

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    int u, v, c;
    long long sum = 0;
    while (m--) {
        scanf("%d %d %d", &u, &v, &c);
        G[++cnt] = { v, head[u], c }, head[u] = cnt;
        G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
        sum += c;
    }
    long long ans = 0;
    while (true) {
        memset(d, 0, sizeof(d));
        d[s] = 1, Q.push(s);
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = head[u]; i; i = G[i].nxt)
                if (G[i].val > 0 && !d[G[i].to])
                    d[G[i].to] = d[u] + 1, Q.push(G[i].to);
        }
        if (!d[t])
            break;
        memcpy(cur, head, sizeof(cur));
        ans += dfs(s, sum);
    }
    printf("%lld\n", ans);
    return 0;
}

long long dfs(const int& u, long long flow) {
    if (u == t || !flow)
        return flow;
    long long ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(G[i].to, min(flow, G[i].val)))) {
            G[i].val -= tmp, G[i ^ 1].val += tmp, flow -= tmp, ret += tmp;
            if (!flow)
                break;
        }
    return ret;
}
