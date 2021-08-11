#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000010, sigma_size = 2;
inline void decode(char*, int);
inline void insert(const char*);
inline int query(const char*);
char S[maxn];

int main() {
    int q;
    scanf("%d", &q);
    scanf("%s", S);
    insert(S);
    int mask = 0, result;
    char type[10];
    while (q--) {
        scanf("%s", type);
        scanf("%s", S);
        decode(S, mask);
        switch (type[0]) {
            case 'A':
                insert(S);
                result = 0;
                break;
            case 'Q':
                printf("%d\n", result = query(S));
                break;
            default:
                break;
        }
        mask ^= result;
    }
    return 0;
}

inline void decode(char* s, int mask) {
    static const int c = 131;
    int n = strlen(s);
    char tmp;
    for (int i = 0; i < n; i++) {
        mask = (mask * c + i) % n;
        tmp = s[i], s[i] = s[mask], s[mask] = tmp;
    }
    return;
}

int son[maxn << 1][2], fa[maxn << 1];
int val[maxn << 1], tag[maxn << 1];
bool rev[maxn << 1];

inline int get(const int u) { return son[fa[u]][1] == u; }

inline bool isroot(const int u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

inline void mark(const int u) {
    rev[u] ^= 1;
    son[u][0] ^= son[u][1] ^= son[u][0] ^= son[u][1];
    return;
}

inline void pushdown(const int u) {
    if (rev[u]) {
        if (son[u][0])
            mark(son[u][0]);
        if (son[u][1])
            mark(son[u][1]);
        rev[u] = false;
    }
    if (tag[u]) {
        if (son[u][0])
            val[son[u][0]] += tag[u], tag[son[u][0]] += tag[u];
        if (son[u][1])
            val[son[u][1]] += tag[u], tag[son[u][1]] += tag[u];
        tag[u] = 0;
    }
    return;
}

void update(const int u) {
    if (!isroot(u))
        update(fa[u]);
    pushdown(u);
    return;
}

inline void rotate(const int& u) {
    int x = fa[u], y = fa[x], k = get(u);
    fa[u] = y;
    if (!isroot(x))
        son[y][get(x)] = u;
    son[x][k] = son[u][k ^ 1];
    fa[son[u][k ^ 1]] = x;
    son[u][k ^ 1] = x;
    fa[x] = u;
    return;
}

inline void splay(const int u) {
    update(u);
    for (int F; F = fa[u], !isroot(u); rotate(u))
        if (!isroot(F))
            rotate(get(u) == get(F) ? F : u);
    return;
}

inline void access(int u) {
    for (int F = 0; u; u = fa[F = u]) splay(u), son[u][1] = F;
    return;
}

inline void makeroot(const int u) {
    access(u);
    splay(u);
    mark(u);
    return;
}

inline void merge(const int u, const int v) {
    makeroot(u);
    access(v);
    splay(v);
    return;
}

inline void link(const int u, const int v) {
    fa[u] = v;
    return;
}

inline void cut(const int u, const int v) {
    merge(u, v);
    fa[u] = son[v][0] = 0;
    return;
}

int cnt = 1, last = 1;
int len[maxn << 1], f[maxn << 1];
int nxt[maxn << 1][sigma_size];
inline void insert(const bool d) {
    int cur, u, v, c;
    len[cur = ++cnt] = len[last] + 1;
    u = last;
    while (u && !nxt[u][d]) nxt[u][d] = cur, u = f[u];
    if (!u) {
        f[cur] = 1;
        link(cur, 1), merge(1, cur);
    } else {
        v = nxt[u][d];
        if (len[u] + 1 == len[v]) {
            f[cur] = v;
            link(cur, v), merge(1, cur);
        } else {
            c = ++cnt;
            cut(f[v], v);
            len[c] = len[u] + 1;
            f[c] = f[v];
            link(v, c), link(cur, c), link(c, f[v]);
            splay(v), val[c] = val[v];
            nxt[c][0] = nxt[v][0], nxt[c][1] = nxt[v][1];
            while (u && nxt[u][d] == v) nxt[u][d] = c, u = f[u];
            f[v] = f[cur] = c;
            merge(1, cur);
        }
    }
    val[cur]++, tag[cur]++;
    last = cur;
    return;
}

inline void insert(const char* s) {
    int n = strlen(s);
    for (int i = 0; i < n; i++) insert(s[i] != 'A');
    return;
}

inline int query(const char* s) {
    int n = strlen(s), u = 1;
    for (int i = 0; i < n; i++) {
        u = nxt[u][S[i] != 'A'];
        if (!u)
            break;
    }
    if (!u)
        return 0;
    splay(u);
    return val[u];
}
