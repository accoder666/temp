#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxc = 210, maxn = 1000010, sigma_size = 26;
int trie[maxn][sigma_size], fail[maxn], cnt;
char str[maxc][maxn];
int ans[maxn];
queue<int> Q;
int p[maxn];
struct edge {
    int to, nxt;
};
edge G[maxn];
int head[maxn], c;
void dfs(const int&);

int main() {
    int n;
    scanf("%d", &n);
    int len;
    for (int i = 1; i <= n; i++) {
        scanf("%s", str[i]);
        p[i] = 0, len = strlen(str[i]);
        for (int j = 0; j < len; j++) {
            if (!trie[p[i]][str[i][j] - 'a'])
                trie[p[i]][str[i][j] - 'a'] = ++cnt;
            p[i] = trie[p[i]][str[i][j] - 'a'];
        }
    }
    for (int i = 0; i < sigma_size; i++)
        if (trie[0][i])
            Q.push(trie[0][i]);
    int u;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        for (int i = 0; i < sigma_size; i++)
            if (trie[u][i])
                fail[trie[u][i]] = trie[fail[u]][i], Q.push(trie[u][i]);
            else
                trie[u][i] = trie[fail[u]][i];
    }
    for (int i = 1; i <= n; i++) {
        u = 0, len = strlen(str[i]);
        for (int j = 0; j < len; j++) ans[u = trie[u][str[i][j] - 'a']]++;
    }
    for (int i = 1; i <= cnt; i++) G[++c] = { i, head[fail[i]] }, head[fail[i]] = c;
    dfs(0);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[p[i]]);
    return 0;
}

void dfs(const int& u) {
    for (int i = head[u]; i; i = G[i].nxt) dfs(G[i].to), ans[u] += ans[G[i].to];
    return;
}
