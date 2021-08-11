#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 2000010;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
int pre[maxn], nxt[maxn];
bool vis[maxn];
queue<int> Q;
int ans[maxn];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    while (m--) {
        scanf("%d %d", &a, &b);
        G[++cnt] = { b, head[a] }, head[a] = cnt;
        G[++cnt] = { a, head[b] }, head[b] = cnt;
    }
    for (int i = 1; i <= n; i++) pre[i] = i - 1, nxt[i] = i + 1;
    nxt[0] = 1, nxt[n] = 0;
    int cnt = 0;
    while (nxt[0]) {
        cnt++;
        a = nxt[0];
        pre[nxt[a]] = 0;
        nxt[0] = nxt[a];
        Q.push(a);
        while (!Q.empty()) {
            ans[cnt]++;
            a = Q.front(), Q.pop();
            for (int i = head[a]; i; i = G[i].nxt) vis[G[i].to] = true;
            for (int i = nxt[0]; i; i = nxt[i])
                if (!vis[i]) {
                    pre[nxt[i]] = pre[i];
                    nxt[pre[i]] = nxt[i];
                    Q.push(i);
                }
            for (int i = head[a]; i; i = G[i].nxt) vis[G[i].to] = false;
        }
    }
    sort(ans + 1, ans + cnt + 1);
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
