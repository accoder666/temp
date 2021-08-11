#include <cstdio>
#include <cstring>
using namespace std;

class num {
public:
    num(void) : len(0) { memset(a, 0, sizeof(a)); }
    inline void read(void) {
        static char buf[maxn * l + 10];
        scanf("%s", buf);
        int i = strlen(buf) - 1;
        for (len = 1; i >= l; i -= l, ++len)
            for (int j = i - l + 1; j <= i; ++j) a[len] = a[len] * 10 + buf[j] - '0';
        for (int j = 0; j <= i; ++j) a[len] = a[len] * 10 + buf[j] - '0';
        return;
    }
    inline void print(void) {
        printf("%d", a[len]);
        for (int i = len - 1; i; i--) printf("%09d", a[i]);
        return;
    }
    friend inline num gcd(num x, num y) {
        num pow2;
        pow2.a[++pow2.len] = 1;
        while (x > y || y > x)
            if (!(x.a[1] & 1) && !(y.a[1] & 1))
                x.div2(), y.div2(), pow2.mul2();
            else if (!(x.a[1] & 1))
                x.div2();
            else if (!(y.a[1] & 1))
                y.div2();
            else if (x > y)
                x -= y;
            else
                y -= x;
        return x * pow2;
    }

private:
    static const int maxn = 1010;
    static const int l = 9, base = 1000000000;
    int a[maxn], len;
    inline void div2(void) {
        for (int i = len; i; i--) {
            if (a[i] & 1)
                a[i - 1] += base;
            a[i] >>= 1;
        }
        if (len && !a[len])
            len--;
        return;
    }
    inline void mul2(void) {
        for (int i = 1; i <= len; i++) {
            a[i] <<= 1;
            if (a[i] >= base)
                a[i] -= base, a[i + 1]++;
        }
        if (a[len + 1])
            len++;
        return;
    }
    inline bool operator>(const num& rhs) const {
        if (len == rhs.len) {
            for (int i = len; i; i--)
                if (a[i] != rhs.a[i])
                    return a[i] > rhs.a[i];
            return false;
        }
        return len > rhs.len;
    }
    inline void operator-=(const num& rhs) {
        for (int i = len; i; i--) {
            a[i] -= rhs.a[i];
            if (a[i] < 0)
                a[i] += base, a[i + 1]--;
        }
        while (len && !a[len]) len--;
        return;
    }
    inline num operator*(const num& rhs) const {
        static long long tmp[maxn];
        for (int i = 1; i <= len; i++)
            for (int j = 1; j <= rhs.len; j++)
                tmp[i + j] += (long long)a[i] * rhs.a[j] / (long long)base,
                    tmp[i + j - 1] += (long long)a[i] * rhs.a[j] % (long long)base;
        num ret;
        int i;
        for (i = 1; i <= len + rhs.len || tmp[i + 1]; i++) {
            if (tmp[i] > base)
                tmp[i + 1] += tmp[i] / base, tmp[i] %= base;
            ret.a[i] = tmp[i];
        }
        ret.len = i;
        while (ret.len && !ret.a[ret.len]) ret.len--;
        return ret;
    }
};
num a, b;

int main() {
    a.read(), b.read();
    gcd(a, b).print();
    return 0;
}
