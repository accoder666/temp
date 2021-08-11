#include <cstdio>
using namespace std;

const long long mod = 1000000007;
const long long inv2 = 500000004, inv6 = 166666668;
struct node {
    long long x, y, z;
};
node solve(const long long&, const long long&, const long long&, const long long&);

int main() {
    long long a, b, c, l, r;
    scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &l, &r);
    node ans1 = solve(r, a, c, b), ans2 = solve(l - 1, a, c, b);
    printf("%lld\n", (ans1.z - ans2.z + (mod << 1ll)) % mod);
    return 0;
}

node solve(const long long& n, const long long& a, const long long& b, const long long& c) {
    long long S0 = (n + 1) % mod, S1 = n * (n + 1) % mod * inv2 % mod,
              S2 = n * (n + 1) % mod * ((n << 1ll) + 1) % mod * inv6 % mod;
    long long A = a / c % mod, B = b / c % mod;
    if (!a)
        return { B * S0 % mod, B * B % mod * S0 % mod, B * S1 % mod };
    if (a < c && b < c) {
        long long m = (a * n + b) / c % mod;
        node t = solve((a * n + b) / c - 1, c, c - b - 1, a);
        return { n * m % mod - t.x, (m * m % mod * n % mod - t.x - (t.z << 1ll)) % mod,
                 m * S1 % mod - (t.x + t.y) * inv2 % mod };
    }
    node t = solve(n, a % c, b % c, c);
    return { (A * S1 % mod + B * S0 % mod + t.x) % mod,
             (A * A % mod * S2 % mod + B * B % mod * S0 % mod + A * B % mod * (S1 << 1ll) % mod +
              (B << 1ll) * t.x % mod + (A << 1ll) * t.z % mod + t.y) %
                 mod,
             (A * S2 % mod + B * S1 % mod + t.z) % mod };
}
