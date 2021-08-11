#include <bits/stdc++.h>
const int N = 400005, M = N * 4;
typedef long long ll;
using namespace std;
int n, m, to[M], hd[M], ln[M], lk[N], cnt, qwq[N], st[N], tot;
ll dis[N], ans = 1e18;
vector<int> ve[N];
bool vis[N];
struct dat {
    int x;
    ll d;
    friend bool operator<(dat a, dat b) { return a.d > b.d; }
};
priority_queue<dat> q;
int u, v, w;
inline void add(int u, int v, int w) {
    //	cerr<<u<<"-"<<w<<"->"<<v<<endl;
    to[++cnt] = v, hd[cnt] = lk[u], ln[cnt] = w, lk[u] = cnt;
}
bool cmp(int x, int y) { return qwq[x] < qwq[y]; }
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add(i, m + i, w);
        add(m + i, i, w);
        qwq[i] = qwq[m + i] = w;
        ve[u].push_back(i), ve[v].push_back(m + i);
    }
    for (int j = n; j; j--) {
        tot = 0;
        for (int i = 0; i < ve[j].size(); i++) st[tot++] = ve[j][i];
        sort(st, st + tot, cmp); /*
             cerr<<j<<"::";
             for(int i=0;i<tot;i++)
             cerr<<st[i]<<' ';
             cerr<<endl;*/
        for (int i = 1; i < tot; i++)
            add(st[i - 1], st[i], qwq[st[i]] - qwq[st[i - 1]]), add(st[i], st[i - 1], 0);
    }
    memset(dis, 0x3f, sizeof dis);
    for (int i = 0; i < tot; i++) q.push((dat){ st[i], dis[st[i]] = qwq[st[i]] });
    for (; q.size();) {
        u = q.top().x;
        q.pop();
        if (vis[u])
            continue;
        // cerr<<u<<" "<<dis[u]<<endl;
        vis[u] = 1;
        for (int i = lk[u]; i; i = hd[i])
            if (dis[v = to[i]] > dis[u] + ln[i])
                q.push({ v, dis[v] = dis[u] + ln[i] });
    }
    for (int i = 0; i < ve[n].size(); i++) ans = min(ans, dis[ve[n][i]]);
    printf("%lld", ans);
}
