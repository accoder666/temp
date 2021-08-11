#pragma GCC target("sse,sse2,sse3,sse4.1,sse4.2,popcnt,abm,mmx,avx")
#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <cctype>
#include <cstdio>
namespace io {
using namespace std;
#define fastcall __attribute__((optimize("-O3")))
#define IL __inline__ __attribute__((always_inline))
struct istream {
#define M (1 << 25)
    int f;
    char buf[M], *ch = buf - 1;
    fastcall IL istream() { fread(buf, 1, M, stdin); }
    fastcall IL istream& operator>>(int& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    fastcall IL istream& operator>>(long long& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    fastcall IL istream& operator>>(char& c) {
        c = *++ch;
        return *this;
    }
#undef M
} cin;
struct ostream {
#define M (1 << 25)
    char buf[M], *ch = buf - 1;
#define endl (char)10
    fastcall IL ostream& operator<<(int x) {
        if (!x) {
            *++ch = '0';
            return *this;
        }
        if (x < 0) {
            x = -x;
            *++ch = '-';
        }
        static int S[20], *top;
        top = S;
        while (x) {
            *++top = x % 10 ^ 48;
            x /= 10;
        }
        for (; top != S; --top) *++ch = *top;
        return *this;
    }
    fastcall IL ostream& operator<<(long long x) {
        if (!x) {
            *++ch = '0';
            return *this;
        }
        if (x < 0) {
            x = -x;
            *++ch = '-';
        }
        static int S[20], *top;
        top = S;
        while (x) {
            *++top = x % 10 ^ 48;
            x /= 10;
        }
        for (; top != S; --top) *++ch = *top;
        return *this;
    }
    fastcall IL ostream& operator<<(const char& x) {
        *++ch = x;
        return *this;
    }
    fastcall IL ~ostream() { fwrite(buf, 1, ch - buf + 1, stdout); }
#undef M
} cout;
}  // namespace io
using namespace io;

const int maxn = 1000010;
int build(const int&, const int&);
int modify(const int&, const int&, const int&);
int query(const int&, const int&);
int a[maxn], root[maxn];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    root[0] = build(1, n);
    int v, opt, loc, val;
    for (int i = 1; i <= m; i++) {
        cin >> v >> opt >> loc;
        switch (opt) {
            case 1:
                cin >> val;
                root[i] = modify(loc, val, root[v]);
                break;
            case 2:
                cout << query(loc, root[i] = root[v]) << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}

struct node {
    int l, r;
    int ls, rs;
    int val;
};
node t[maxn * 20];
int cnt;

inline int clone(const int& u) {
    t[++cnt] = t[u];
    return cnt;
}

int build(const int& l, const int& r) {
    int u = ++cnt;
    t[u].l = l, t[u].r = r;
    if (l == r) {
        t[u].val = a[l];
        return u;
    }
    int mid = (l + r) >> 1;
    t[u].ls = build(l, mid);
    t[u].rs = build(mid + 1, r);
    return u;
}

int modify(const int& p, const int& val, const int& u) {
    int ret = clone(u);
    if (t[u].l == t[u].r) {
        t[ret].val = val;
        return ret;
    }
    if (p <= t[t[u].ls].r)
        t[ret].ls = modify(p, val, t[u].ls);
    else
        t[ret].rs = modify(p, val, t[u].rs);
    return ret;
}

int query(const int& p, const int& u) {
    if (t[u].l == t[u].r)
        return t[u].val;
    if (p <= t[t[u].ls].r)
        return query(p, t[u].ls);
    return query(p, t[u].rs);
}
