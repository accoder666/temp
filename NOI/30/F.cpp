#include <cstdio>
using namespace std;

const int maxn = 100010;
inline unsigned long long query(unsigned long long);
void dfs(const int&, const unsigned long long&);
unsigned long long dis[maxn];
struct edge {
    int to, nxt;
    unsigned long long val;
};
edge G[maxn << 1];
int head[maxn], cnt;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int s, t;
    unsigned long long d;
    while (m--) {
        scanf("%d %d %llu", &s, &t, &d);
        G[++cnt] = { t, head[s], d }, head[s] = cnt;
        G[++cnt] = { s, head[t], d }, head[t] = cnt;
    }
    dfs(1, 0);
    printf("%llu\n", query(dis[n]));
    return 0;
}

const int maxl = 61;
unsigned long long val[maxl];

inline void insert(unsigned long long v) {
    for (int i = maxl - 1; i >= 0; i--)
        if (v >> i) {
            if (!val[i]) {
                val[i] = v;
                break;
            }
            v ^= val[i];
        }
    return;
}

inline unsigned long long query(unsigned long long v) {
    for (int i = maxl - 1; i >= 0; i--)
        if ((v ^ val[i]) > v)
            v ^= val[i];
    return v;
}

bool vis[maxn];
void dfs(const int& u, const unsigned long long& v) {
    vis[u] = true, dis[u] = v;
    for (int i = head[u]; i; i = G[i].nxt)
        if (vis[G[i].to])
            insert(v ^ G[i].val ^ dis[G[i].to]);
        else
            dfs(G[i].to, v ^ G[i].val);
    return;
}
