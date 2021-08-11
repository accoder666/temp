
// Problem : P5643 [PKUWC2018]随机游走
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/P5643
// Memory Limit : 500 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cctype>
#include <cstdio>
namespace io {
using namespace std;
struct istream {
#define M (1 << 25)
    int f;
    char buf[M], *ch = buf - 1;
    istream() { fread(buf, 1, M, stdin); }
    istream& operator>>(int& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    istream& operator>>(long long& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    istream& operator>>(char& c) {
        c = *++ch;
        return *this;
    }
#undef M
} cin;
struct ostream {
#define M (1 << 25)
    char buf[M], *ch = buf - 1;
#define endl (char)10
    ostream& operator<<(int x) {
        if (!x) {
            *++ch = '0';
            return *this;
        }
        if (x < 0) {
            x = -x;
            *++ch = '-';
        }
        static int S[10], *top;
        top = S;
        while (x) {
            *++top = x % 10 ^ 48;
            x /= 10;
        }
        for (; top != S; --top) *++ch = *top;
        return *this;
    }
    ostream& operator<<(long long x) {
        if (!x) {
            *++ch = '0';
            return *this;
        }
        if (x < 0) {
            x = -x;
            *++ch = '-';
        }
        static int S[10], *top;
        top = S;
        while (x) {
            *++top = x % 10 ^ 48;
            x /= 10;
        }
        for (; top != S; --top) *++ch = *top;
        return *this;
    }
    ostream& operator<<(const char& x) {
        *++ch = x;
        return *this;
    }
    ~ostream() { fwrite(buf, 1, ch - buf + 1, stdout); }
#undef M
} cout;
}  // namespace io
using namespace io;

namespace inverse {
using namespace std;
template <typename T>
void exgcd(const T& a, const T& b, T& g, T& x, T& y) {
    if (b) {
        exgcd(b, a % b, g, y, x);
        y -= x * (a / b);
        return;
    }
    g = a, x = 1, y = 0;
    return;
}
template <typename T>
T Inverse(const T& a, const T& p) {
    T g, x, y;
    exgcd(a, p, g, x, y);
    x %= p;
    if (x < 0)
        x += p;
    return x;
}
}  // namespace inverse
using namespace inverse;

const long long mod = 998244353;
const int maxn = 20;
struct edge {
    int to, nxt;
};
edge G[maxn << 1];
int head[maxn], cnt;
long long deg[2][maxn];
inline void AddEdge(const int&, const int&);
void dfs(const int&, const int& fa = 0);
long long ans[1 << maxn];
int count[1 << maxn];
struct func {
    long long a, b;
};
func f[maxn];
int state;

int main() {
    int n, Q, x;
    cin >> n >> Q >> x;
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        AddEdge(u, v);
        AddEdge(v, u);
    }
    for (int i = 1; i <= n; i++) deg[1][i] = Inverse(deg[0][i], mod);
    int max = 1 << n;
    for (int i = 1; i < max; i++) count[i] = count[i >> 1] + (i & 1);
    for (state = 0; state < max; state++) {
        dfs(x);
        ans[state] = (count[state] & 1) ? f[x].b : mod - f[x].b;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < max; j++)
            if ((j >> i) & 1)
                ans[j] = (ans[j] + ans[j ^ (1 << i)]) % mod;
    int k, S, val;
    while (Q--) {
        cin >> k;
        S = 0;
        while (k--) {
            cin >> val;
            S |= 1 << (val - 1);
        }
        cout << (ans[S] + mod) % mod << endl;
    }
    return 0;
}

inline void AddEdge(const int& u, const int& v) {
    G[++cnt] = (edge){ v, head[u] };
    head[u] = cnt, deg[0][u]++;
    return;
}

void dfs(const int& u, const int& fa) {
    if ((1 << (u - 1)) & state) {
        f[u] = (func){ 0, 0 };
        return;
    }
    long long suma = 0, sumb = 0;
    for (int i = head[u]; i; i = G[i].nxt)
        if (G[i].to != fa) {
            dfs(G[i].to, u);
            suma = (suma + f[G[i].to].a) % mod;
            sumb = (sumb + f[G[i].to].b) % mod;
        }
    long long inv = Inverse((mod + 1 - (deg[1][u] * suma) % mod) % mod, mod);
    f[u] = (func){ (inv * deg[1][u]) % mod, (inv * ((1 + deg[1][u] * sumb) % mod)) % mod };
    return;
}
