#include <cctype>
#include <cstdio>
using namespace std;

const int maxn = 100010;
inline void pushup(const int&);
inline void splay(const int&);
inline void access(int);
inline void makeroot(const int&);
int son[maxn][2], fa[maxn], s[maxn][2];
bool tag[maxn];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    char op;
    int x, y;
    while (q--) {
        op = getchar();
        while (!isalpha(op)) op = getchar();
        scanf("%d %d", &x, &y);
        switch (op) {
            case 'A':
                makeroot(x);
                makeroot(y);
                fa[x] = y;
                s[y][1] += s[x][0];
                break;
            case 'Q':
                makeroot(x);
                access(y);
                splay(y);
                son[y][0] = fa[x] = 0;
                pushup(x);
                makeroot(x);
                makeroot(y);
                printf("%lld\n", (long long)s[x][0] * s[y][0]);
                makeroot(x);
                makeroot(y);
                fa[x] = y;
                s[y][1] += s[x][0];
                break;
            default:
                break;
        }
    }
    return 0;
}

inline void clear(const int& u) {
    son[u][0] = son[u][1] = fa[u] = s[u][0] = s[u][1] = 0;
    tag[u] = false;
    return;
}

inline bool isroot(const int& u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

inline int get(const int& u) { return son[fa[u]][1] == u; }

inline void pushup(const int& u) {
    clear(0);
    if (!u)
        return;
    s[u][0] = s[son[u][0]][0] + s[son[u][1]][0] + s[u][1] + 1;
    return;
}

inline void pushdown(const int& u) {
    if (!tag[u])
        return;
    tag[u] = false;
    son[u][0] ^= son[u][1] ^= son[u][0] ^= son[u][1];
    if (son[u][0])
        tag[son[u][0]] ^= 1;
    if (son[u][1])
        tag[son[u][1]] ^= 1;
    return;
}

void update(const int& u) {
    if (!isroot(u))
        update(fa[u]);
    pushdown(u);
    return;
}

inline void rotate(const int& u) {
    int x = fa[u], y = fa[x], vu = get(u);
    fa[u] = y;
    if (!isroot(x))
        son[y][get(x)] = u;
    son[x][vu] = son[u][vu ^ 1];
    fa[son[u][vu ^ 1]] = x;
    son[u][vu ^ 1] = x;
    fa[x] = u;
    pushup(x);
    pushup(u);
    pushup(y);
    return;
}

inline void splay(const int& u) {
    update(u);
    for (int f; f = fa[u], !isroot(u); rotate(u))
        if (!isroot(f))
            rotate(get(u) == get(f) ? f : u);
    return;
}

inline void access(int u) {
    for (int f = 0; u; f = u, u = fa[u])
        splay(u), s[u][1] += s[son[u][1]][0] - s[f][0], son[u][1] = f, pushup(u);
    return;
}

inline void makeroot(const int& u) {
    access(u);
    splay(u);
    tag[u] ^= 1;
    return;
}
