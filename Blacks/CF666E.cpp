#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxs = 500010, maxn = 50010, sigma_size = 26, maxlg = 17;
char s[maxs], str[maxn];
inline void insert(const char*, int);
inline void preprocess(void);
inline pair<int, int> solve(int, int, int, int);
int m;

int main() {
    scanf("%s", s + 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", str);
        insert(str, strlen(str));
    }
    preprocess();
    int q;
    scanf("%d", &q);
    int l, r, pl, pr;
    pair<int, int> ans;
    while (q--) {
        scanf("%d %d %d %d", &l, &r, &pl, &pr);
        ans = solve(l, r, pl, pr);
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}

struct node {
    int ls, rs;
    pair<int, int> val;
};
node t[maxn << 5];
int rt[maxn << 1];
int C;

inline pair<int, int> max(const pair<int, int> a, const pair<int, int> b) {
    if (a.first != b.first)
        return a.first > b.first ? a : b;
    return a.second < b.second ? a : b;
}

inline void pushup(const int u) {
    t[u].val = max(t[t[u].ls].val, t[t[u].rs].val);
    return;
}

inline void modify(int& u, const int l, const int r, const int p) {
    if (!u) {
        u = ++C;
        if (l == r)
            t[u].val.second = l;
    }
    if (l == r) {
        t[u].val.first++;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(t[u].ls, l, mid, p);
    else
        modify(t[u].rs, mid + 1, r, p);
    pushup(u);
    return;
}

inline int merge(const int u, const int v, const int l, const int r) {
    if (!u || !v)
        return u | v;
    int ret = ++C;
    if (l == r) {
        t[ret].val = make_pair(t[u].val.first + t[v].val.first, l);
        return ret;
    }
    int mid = (l + r) >> 1;
    t[ret].ls = merge(t[u].ls, t[v].ls, l, mid);
    t[ret].rs = merge(t[u].rs, t[v].rs, mid + 1, r);
    pushup(ret);
    return ret;
}

inline pair<int, int> query(const int u, const int l, const int r, const int L, const int R) {
    if (!u || r < L || R < l)
        return make_pair(0, 0);
    if (L <= l && r <= R)
        return t[u].val;
    int mid = (l + r) >> 1;
    return max(query(t[u].ls, l, mid, L, R), query(t[u].rs, mid + 1, r, L, R));
}

int len[maxn << 1], fa[maxn << 1];
int nxt[maxn << 1][sigma_size];
int cnt = 1;
vector<int> bel[maxn << 1];

inline void insert(const char* S, const int n) {
    static int Cnt;
    Cnt++;
    int u = 1, d;
    for (int i = 0; i < n; i++) {
        d = S[i] - 'a';
        if (!nxt[u][d])
            nxt[u][d] = ++cnt;
        u = nxt[u][d];
        bel[u].push_back(Cnt);
    }
    return;
}

inline int insert(const int last, const int d) {
    int cur = nxt[last][d];
    if (len[cur])
        return cur;
    for (int i : bel[cur]) modify(rt[cur], 1, m, i);
    len[cur] = len[last] + 1;
    int u = fa[last];
    while (u && !nxt[u][d]) nxt[u][d] = cur, u = fa[u];
    if (!u) {
        fa[cur] = 1;
        return cur;
    }
    int v = nxt[u][d];
    if (len[u] + 1 == len[v]) {
        fa[cur] = v;
        return cur;
    }
    int c = ++cnt;
    len[c] = len[u] + 1, fa[c] = fa[v];
    for (int i = 0; i < sigma_size; i++)
        if (len[nxt[v][i]])
            nxt[c][i] = nxt[v][i];
    while (u && nxt[u][d] == v) nxt[u][d] = c, u = fa[u];
    fa[v] = fa[cur] = c;
    return cur;
}

queue<pair<int, int>> Q;
inline void build(void) {
    for (int i = 0; i < sigma_size; i++)
        if (nxt[1][i])
            Q.push(make_pair(1, i));
    int last;
    while (!Q.empty()) {
        last = insert(Q.front().first, Q.front().second), Q.pop();
        for (int i = 0; i < sigma_size; i++)
            if (nxt[last][i])
                Q.push(make_pair(last, i));
    }
    return;
}

struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn << 1], Gcnt;
int lg[maxn << 1], dep[maxn << 1], anc[maxn << 1][maxlg];

void dfs(const int u) {
    for (int i = 1; i <= lg[dep[u]]; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = G[i].nxt) {
        dep[G[i].to] = dep[u] + 1;
        anc[G[i].to][0] = u;
        dfs(G[i].to);
        rt[u] = merge(rt[u], rt[G[i].to], 1, m);
    }
    return;
}

int p[maxs], le[maxs];

inline void preprocess(void) {
    build();
    for (int i = 2; i <= cnt; i++) G[++Gcnt] = { i, head[fa[i]] }, head[fa[i]] = Gcnt;
    for (int i = 2; i <= cnt; i++) lg[i] = lg[i >> 1] + 1;
    dfs(1);
    int u = 1, L = 0, d;
    int Len = strlen(s + 1);
    for (int i = 1; i <= Len; i++) {
        d = s[i] - 'a';
        if (nxt[u][d])
            u = nxt[u][d], L++;
        else {
            while (u && !nxt[u][d]) u = fa[u];
            if (!u)
                u = 1, L = 0;
            else
                L = len[u] + 1, u = nxt[u][d];
        }
        p[i] = u, le[i] = L;
    }
    return;
}

inline pair<int, int> solve(const int l, const int r, const int pl, const int pr) {
    int length = pr - pl + 1;
    if (le[pr] < length)
        return make_pair(l, 0);
    int u = p[pr];
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (len[anc[u][i]] >= length)
            u = anc[u][i];
    pair<int, int> ret = query(rt[u], 1, m, l, r);
    ret.first ^= ret.second ^= ret.first ^= ret.second;
    if (!ret.second)
        ret.first = l;
    return ret;
}
