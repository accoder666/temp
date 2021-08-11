#include <chrono>
#include <cstdio>
#include <iostream>
#include <random>
#include <unordered_map>
using namespace std;

inline long long power(long long, long long);
inline long long cipolla(long long);
inline long long BSGS(const long long&, const long long&);
long long p;

int main() {
    freopen("shu.in", "r", stdin);
    freopen("shu.out", "w", stdout);
    int t;
    scanf("%d", &t);
    long long x;
    long long sqrt5, s, inv2, t1, t2, v;
    long long n, n1, n2, n3, n4;
    while (t--) {
        scanf("%lld %lld", &x, &p);
        if (!x) {
            printf("0\n");
            continue;
        }
        sqrt5 = cipolla(5);
        inv2 = (p + 1) >> 1;
        s = x * sqrt5 % p;
        t1 = cipolla((s * s + 4) % p), t2 = cipolla((s * s - 4 + p) % p);
        v = (sqrt5 + 1) * inv2 % p;
        n = p;
        n1 = n2 = n3 = n4 = p;
        if (t1 != -1) {
            n1 = BSGS(v, (s + t1) * inv2 % p);
            n2 = BSGS(v, (s - t1 + p) * inv2 % p);
        }
        if (t2 != -1) {
            n3 = BSGS(v, (s + t2) * inv2 % p);
            n4 = BSGS(v, (s - t2 + p) * inv2 % p);
        }
        if (!(n1 & 1))
            n = min(n, n1);
        if (!(n2 & 1))
            n = min(n, n2);
        if (n3 & 1)
            n = min(n, n3);
        if (n4 & 1)
            n = min(n, n4);
        sqrt5 = p - sqrt5;
        s = x * sqrt5 % p;
        t1 = cipolla((s * s + 4) % p), t2 = cipolla((s * s - 4 + p) % p);
        v = (sqrt5 + 1) * inv2 % p;
        n1 = n2 = n3 = n4 = p;
        if (t1 != -1) {
            n1 = BSGS(v, (s + t1) * inv2 % p);
            n2 = BSGS(v, (s - t1 + p) * inv2 % p);
        }
        if (t2 != -1) {
            n3 = BSGS(v, (s + t2) * inv2 % p);
            n4 = BSGS(v, (s - t2 + p) * inv2 % p);
        }
        if (!(n1 & 1))
            n = min(n, n1);
        if (!(n2 & 1))
            n = min(n, n2);
        if (n3 & 1)
            n = min(n, n3);
        if (n4 & 1)
            n = min(n, n4);
        printf("%lld\n", n == p ? -1 : n);
        cerr << endl;
    }
    return 0;
}

inline long long power(long long b, long long e) {
    long long ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % p;
        b = b * b % p, e >>= 1;
    }
    return ret;
}

struct complex {
    long long a, b;
    static long long s;
    inline complex operator+(const complex& rhs) const { return { (a + rhs.a) % p, (b + rhs.b) % p }; }
    inline complex operator-(const complex& rhs) const {
        return { (a - rhs.a + p) % p, (b - rhs.b + p) % p };
    }
    inline complex operator*(const complex& rhs) const {
        return { (a * rhs.a + b * rhs.b % p * s) % p, (a * rhs.b + b * rhs.a) % p };
    }
};
long long complex::s;

inline complex power(complex b, long long e) {
    complex ret = { 1, 0 };
    while (e) {
        if (e & 1)
            ret = ret * b;
        b = b * b, e >>= 1;
    }
    return ret;
}

const int maxv = 1000000000;
mt19937 r(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> R(0, maxv);
inline long long cipolla(long long v) {
    v = (v % p + p) % p;
    if (!v)
        return 0;
    if (power(v, p >> 1) == p - 1)
        return -1;
    long long a;
    while (true) {
        a = R(r) % p;
        complex::s = (a * a % p - v + p) % p;
        if (power(complex::s, p >> 1) == p - 1)
            break;
    }
    complex x = { a, 1 };
    return power(x, (p + 1) >> 1).a;
}

unordered_map<long long, long long> M;
inline long long BSGS(const long long& a, const long long& b) {
    if (b == 1)
        return 0;
    int m = (int)sqrt(p) + 1;
    M.clear();
    long long tmp = b;
    for (int i = 0; i < m; i++) M[tmp] = i, tmp = tmp * a % p;
    long long t = power(a, m);
    tmp = t;
    unordered_map<long long, long long>::iterator it;
    for (int i = 1; i <= m; i++) {
        it = M.find(tmp);
        if (it != M.end())
            return (i * m - (it->second) + p) % p;
        tmp = t * tmp % p;
    }
    return p;
}
