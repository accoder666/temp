#include <bits/stdc++.h>

using namespace std;

const int maxn = 5000010;
struct edge {
    int to, nxt, val;
};
edge G[maxn << 2];
int head[maxn], cnt = 1;
inline void AddEdge(const int&, const int&);
inline int dinic(const int&, const int&);
bool vis[maxn];
int to[maxn];
int n;
int mp[1 << 13];
void solve(int lim) {
    for (int i = 1; i <= n; i++) AddEdge(0, i), AddEdge(i + n, (n + 1) << 1);
    int u, v;
    dinic(0, (n + 1) << 1);
    int ans = 0, is_first = 1;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            vector<int> v;
            v.push_back(u = i);
            while (to[u] && to[u] != (n + 1) << 1) v.push_back(u = to[u] - n);
            if (v.size() == 1 && !mp[v.front() - 1])
                continue;
            int x = 0;
            for (auto y : v) {
                ans += __builtin_popcount(x ^ (y - 1));
                x = y - 1;
            }
            if (is_first) {
                is_first = 0;
            } else {
                ans++;
            }
        }
    printf("%d\n", ans);
    is_first = 1;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            vector<int> v;
            v.push_back(u = i);
            while (to[u] && to[u] != (n + 1) << 1) v.push_back(u = to[u] - n);
            if (v.size() == 1 && !mp[v.front() - 1])
                continue;
            if (is_first) {
                is_first = 0;
            } else {
                cout << "R ";
            }
            int x = 0;
            for (auto y : v) {
                int tmp = x ^ (y - 1);
                for (int i = 0; i < lim; i++) {
                    if (tmp & (1 << i)) {
                        cout << lim - i - 1 << " ";
                    }
                }
                x = y - 1;
            }
        }
    cout << endl;
    return;
}
using namespace std;
int main() {
    int d, n;
    cin >> d >> n;
    ::n = (1 << d);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        bitset<20> bt(s);
        mp[bt.to_ulong()] = 1;
    }
    // mp[0] = 1;
    for (int i = 0; i < (1 << d); i++) {
        for (int j = 0; j < (1 << d); j++) {
            if (i != j && mp[i] && mp[j] && ((j | i) == j)) {
                // cout << i << " " << j << endl;
                AddEdge(i + 1, j + 1 + ::n);
            }
        }
    }
    solve(d);
}
inline void AddEdge(const int& u, const int& v) {
    G[++cnt] = { v, head[u], 1 }, head[u] = cnt;
    G[++cnt] = { u, head[v], 0 }, head[v] = cnt;
    return;
}

int d[maxn];

queue<int> Q;
inline bool bfs(const int& s, const int& t) {
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

int cur[maxn];
int dfs(const int& s, const int& u, const int& t, int flow) {
    if (u == t || !flow)
        return flow;
    int ret = 0, tmp;
    for (int& i = cur[u]; i; i = G[i].nxt)
        if (d[G[i].to] == d[u] + 1 && (tmp = dfs(s, G[i].to, t, min(flow, G[i].val)))) {
            if (u != s)
                to[u] = G[i].to, vis[G[i].to - n] = true;
            ret += tmp, flow -= tmp, G[i].val -= tmp, G[i ^ 1].val += tmp;
            if (!flow)
                break;
        }
    return ret;
}

inline int dinic(const int& s, const int& t) {
    int ret = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(cur));
        ret += dfs(s, s, t, INT_MAX);
    }
    return ret;
}
