//#include <cstdio>
// using namespace std;
//
// const long long mod = 998244353;
// const long long inv2 = 499122177;
// const int maxn = 6000010;
// void query(const int &, const int &, long long &, long long &, long long &);
// void modify(const int &, const int &, const int &, const int &, int &, const long long &, const long long
// &,
//            const long long &);
// inline long long inv(long long);
//
// int main() {
//    int n;
//    scanf("%d", &n);
//    int l, r;
//    int root = 1;
//    long long ans = 0;
//    long long a, b, c;
//    static int lim = 100000000;
//    while (n--) {
//        scanf("%d %d", &l, &r);
//        a = b = c = 0;
//        query(r, 1, a, b, c);
//        ans += a + b * r % mod + c * r % mod * r % mod;
//        a = b = c = 0;
//        query(l, 1, a, b, c);
//        ans -= a + b * l % mod + c * l % mod * l % mod;
//        modify(1, l, 1, lim, root, 0, 1, 0);
//        modify(l + 1, r, 1, lim, root, -l * l % mod * inv2 % mod * inv(r - l) % mod, l * inv(r - l) % mod +
//        1,
//               -inv2 * inv(r - l) % mod);
//        modify(r + 1, lim, 1, lim, root, (l + r) * inv2 % mod, 0, 0);
//    }
//    printf("%lld\n", (ans % mod + mod) % mod);
//    return 0;
//}
//
// struct node {
//    int l, r;
//    int ls, rs;
//    long long a, b, c;
//};
// node t[maxn];
// int cnt;
//
// void query(const int &p, const int &u, long long &a, long long &b, long long &c) {
//    if (u) {
//        a += t[u].a, b += t[u].b, c += t[u].c;
//        a %= mod, b %= mod, c %= mod;
//    }
//    if (!u || t[u].l == t[u].r)
//        return;
//    if (p <= t[t[u].ls].r)
//        query(t[u].ls, p, a, b, c);
//    else
//        query(t[u].rs, p, a, b, c);
//    return;
//}
//
// void modify(const int &l, const int &r, const int &L, const int &R, int &u, const long long &a,
//            const long long &b, const long long &c) {
//    if (!u)
//        u = ++cnt, t[u].l = L, t[u].r = R;
//    if (l <= t[u].l && t[u].r <= r) {
//        t[u].a += a, t[u].b += b, t[u].c += c;
//        t[u].a %= mod, t[u].b %= mod, t[u].c %= mod;
//    }
//    int mid = (L + R) >> 1;
//    if (l <= mid)
//        modify(l, r, L, mid, t[u].ls, a, b, c);
//    if (mid < r)
//        modify(l, r, mid + 1, r, t[u].rs, a, b, c);
//    return;
//}
//
// inline long long inv(long long v) {
//    long long ret = 1, e = mod - 2;
//    while (e) {
//        if (e & 1)
//            ret = ret * v % mod;
//        v = v * v % mod, e >>= 1;
//    }
//    return ret;
//}

#include <cstdio>
using namespace std;

using namespace std;

const long long mod = 998244353;
const long long inv2 = 499122177;
inline long long inv(long long);
const int maxn = 100010;
int l[maxn], r[maxn];

int main() {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", l + i, r + i);
        for (int j = 1; j < i; j++) {
            if (r[i] < l[j])
                ans++;
            else if (r[j] < l[i])
                ;
            else if (l[i] < l[j]) {
            } else
                ans += (r[i] - l[j]) * (r[i] - l[j]) % mod * inv(r[i] - l[i]) % mod * inv(r[j] - l[j]) % mod;
        }
    }
    printf("%lld\n", (ans % mod + mod) % mod);
    return 0;
}

inline long long inv(long long v) {
    long long ret = 1, e = mod - 2;
    while (e) {
        if (e & 1)
            ret = ret * v % mod;
        v = v * v % mod, e >>= 1;
    }
    return ret;
}
