#include <cstdio>
using namespace std;

class ModNum {
public:
    ModNum() : val(0) {}
    ModNum(unsigned long long n) : val(init(n)) {}
    static inline unsigned long long init(unsigned long long w) { return reduce((__uint128_t)w * r); }
    static inline void set_mod(unsigned long long m) {
        mod = inv = m;
        inv *= (2 - inv * m);
        inv *= (2 - inv * m);
        inv *= (2 - inv * m);
        inv *= (2 - inv * m);
        inv *= (2 - inv * m);
        r = -(__uint128_t)m % m;
        return;
    }
    inline ModNum operator+(ModNum rhs) const {
        ModNum ret = *this;
        ret.val += rhs.val - mod;
        if (((long long)ret.val >> 63))
            ret.val += mod;
        return ret;
    }
    inline ModNum& operator+=(ModNum rhs) {
        val += rhs.val - mod;
        if (((long long)val >> 63))
            val += mod;
        return *this;
    }
    inline ModNum operator-(ModNum rhs) const {
        ModNum ret = *this;
        ret.val -= rhs.val - mod;
        if ((long long)ret.val > mod)
            ret.val -= mod;
        return ret;
    }
    inline ModNum operator*(ModNum rhs) const {
        ModNum ret;
        ret.val = reduce((__uint128_t)val * rhs.val);
        return ret;
    }
    inline ModNum operator*=(ModNum rhs) {
        val = reduce((__uint128_t)val * rhs.val);
        return *this;
    }
    inline unsigned long long get() const { return reduce(val); }

private:
    unsigned long long val;
    static unsigned long long mod, inv, r;
    static inline unsigned long long reduce(__uint128_t x) {
        unsigned long long y = (unsigned long long)(x >> 64) -
                               (unsigned long long)(((__uint128_t)((unsigned long long)x * inv) * mod) >> 64);
        return ((long long)y >> 63) ? y + mod : y;
    }
};
unsigned long long ModNum::mod, ModNum::inv, ModNum::r;

int n, p;
inline int Count(int);
inline ModNum Power(ModNum, int e = p - 2);

int main() {
    scanf("%d %d", &n, &p);
    int max = 1 << n, tmp = max - 8, i;
    ModNum::set_mod(p);
    const ModNum pow[24] = { Power(2, 0),  Power(2, 1),  Power(2, 2),  Power(2, 3),  Power(2, 4),
                             Power(2, 5),  Power(2, 6),  Power(2, 7),  Power(2, 8),  Power(2, 9),
                             Power(2, 10), Power(2, 11), Power(2, 12), Power(2, 13), Power(2, 14),
                             Power(2, 15), Power(2, 16), Power(2, 17), Power(2, 18), Power(2, 19),
                             Power(2, 20), Power(2, 21), Power(2, 22), Power(2, 23) },
                 P = p, v = 1, coeff = Power(P + Power(4, n) - Power(2, n));
    ModNum ans, ans0, ans1, ans2, ans3, ans4, ans5, ans6, ans7;
    for (i = 1; i <= tmp; i += 8) {
        ans0 += ((Count(i) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ i)] * (ModNum)((max - 1) ^ i) * coeff);
        ans1 += ((Count(i + 1) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 1))] * (ModNum)((max - 1) ^ (i + 1)) * coeff);
        ans2 += ((Count(i + 2) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 2))] * (ModNum)((max - 1) ^ (i + 2)) * coeff);
        ans3 += ((Count(i + 3) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 3))] * (ModNum)((max - 1) ^ (i + 3)) * coeff);
        ans4 += ((Count(i + 4) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 4))] * (ModNum)((max - 1) ^ (i + 4)) * coeff);
        ans5 += ((Count(i + 5) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 5))] * (ModNum)((max - 1) ^ (i + 5)) * coeff);
        ans6 += ((Count(i + 6) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 6))] * (ModNum)((max - 1) ^ (i + 6)) * coeff);
        ans7 += ((Count(i + 7) & 1) ? v : P - 1) *
                Power(P + 1 - pow[Count((max - 1) ^ (i + 7))] * (ModNum)((max - 1) ^ (i + 7)) * coeff);
    }
    for (; i < max; i++)
        ans += ((Count(i) & 1) ? v : P - 1) *
               Power(P + 1 - pow[Count((max - 1) ^ i)] * (ModNum)((max - 1) ^ i) * coeff);
    ans += ans0 + ans1 + ans2 + ans3 + ans4 + ans5 + ans6 + ans7;
    printf("%llu\n", ans.get());
    return 0;
}

inline int Count(int val) {
#define BIT2(n) n, n + 1, n + 1, n + 2
#define BIT4(n) BIT2(n), BIT2(n + 1), BIT2(n + 1), BIT2(n + 2)
#define BIT6(n) BIT4(n), BIT4(n + 1), BIT4(n + 1), BIT4(n + 2)
#define BIT8(n) BIT6(n), BIT6(n + 1), BIT6(n + 1), BIT6(n + 2)
#define BIT10(n) BIT8(n), BIT8(n + 1), BIT8(n + 1), BIT8(n + 2)
#define BIT12(n) BIT10(n), BIT10(n + 1), BIT10(n + 1), BIT10(n + 2)
    static const int t[4096] = { BIT12(0) };
    return t[val & 4095] + t[(val >> 12) & 4095];
}

ModNum ret;
inline ModNum Power(ModNum b, int e) {
    ret = 1;
    if (e < 1)
        return ret;
    if (e & 1)
        ret *= b;
    b *= b;
    if (e < 2)
        return ret;
    if (e & 2)
        ret *= b;
    b *= b;
    if (e < 4)
        return ret;
    if (e & 4)
        ret *= b;
    b *= b;
    if (e < 8)
        return ret;
    if (e & 8)
        ret *= b;
    b *= b;
    if (e < 16)
        return ret;
    if (e & 16)
        ret *= b;
    b *= b;
    if (e < 32)
        return ret;
    if (e & 32)
        ret *= b;
    b *= b;
    if (e < 64)
        return ret;
    if (e & 64)
        ret *= b;
    b *= b;
    if (e < 128)
        return ret;
    if (e & 128)
        ret *= b;
    b *= b;
    if (e < 256)
        return ret;
    if (e & 256)
        ret *= b;
    b *= b;
    if (e < 512)
        return ret;
    if (e & 512)
        ret *= b;
    b *= b;
    if (e < 1024)
        return ret;
    if (e & 1024)
        ret *= b;
    b *= b;
    if (e < 2048)
        return ret;
    if (e & 2048)
        ret *= b;
    b *= b;
    if (e < 4096)
        return ret;
    if (e & 4096)
        ret *= b;
    b *= b;
    if (e < 8192)
        return ret;
    if (e & 8192)
        ret *= b;
    b *= b;
    if (e < 16384)
        return ret;
    if (e & 16384)
        ret *= b;
    b *= b;
    if (e < 32768)
        return ret;
    if (e & 32768)
        ret *= b;
    b *= b;
    if (e < 65536)
        return ret;
    if (e & 65536)
        ret *= b;
    b *= b;
    if (e < 131072)
        return ret;
    if (e & 131072)
        ret *= b;
    b *= b;
    if (e < 262144)
        return ret;
    if (e & 262144)
        ret *= b;
    b *= b;
    if (e < 524288)
        return ret;
    if (e & 524288)
        ret *= b;
    b *= b;
    if (e < 1048576)
        return ret;
    if (e & 1048576)
        ret *= b;
    b *= b;
    if (e < 2097152)
        return ret;
    if (e & 2097152)
        ret *= b;
    b *= b;
    if (e < 4194304)
        return ret;
    if (e & 4194304)
        ret *= b;
    b *= b;
    if (e < 8388608)
        return ret;
    if (e & 8388608)
        ret *= b;
    b *= b;
    if (e < 16777216)
        return ret;
    if (e & 16777216)
        ret *= b;
    b *= b;
    if (e < 33554432)
        return ret;
    if (e & 33554432)
        ret *= b;
    b *= b;
    if (e < 67108864)
        return ret;
    if (e & 67108864)
        ret *= b;
    b *= b;
    if (e < 134217728)
        return ret;
    if (e & 134217728)
        ret *= b;
    b *= b;
    if (e < 268435456)
        return ret;
    if (e & 268435456)
        ret *= b;
    b *= b;
    if (e < 536870912)
        return ret;
    if (e & 536870912)
        ret *= b;
    return ret;
}
