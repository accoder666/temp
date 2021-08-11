#include <cstdio>
using namespace std;

const int maxn = 110;
long long p;
class Matrix {
public:
    Matrix(void) { a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
    inline long long* operator[](const int x) { return a[x]; }
    inline Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                for (int k = 0; k < maxn; k++) ret[i][j] = (ret[i][j] + a[i][k] * rhs.a[k][j]) % p;
        return ret;
    }
    inline Matrix& operator*=(const Matrix& rhs) {
        *this = this->operator*(rhs);
        return *this;
    }

private:
    static const int maxn = 2;
    long long a[maxn][maxn];
};
inline long long solve(long long);
long long M[maxn];

int main() {
    freopen("hakugai.in", "r", stdin);
    freopen("hakugai.out", "w", stdout);
    int T;
    scanf("%d", &T);
    int k;
    long long a, b, n;
    Matrix base, Mat;
    while (T--) {
        scanf("%lld %lld %lld %d %lld", &a, &b, &n, &k, M + 1);
        for (int i = 2; i <= k; i++) M[i] = solve(M[i - 1]);
        for (int i = k; i; i--) {
            p = M[i];
            if (!n)
                n = a % p;
            else if (n == 1)
                n = b % p;
            else {
                base[0][0] = 3, base[0][1] = 1, base[1][0] = p - 1, base[1][1] = 0;
                Mat[0][0] = b, Mat[0][1] = a, Mat[1][0] = Mat[1][1] = 0;
                n--;
                while (n) {
                    if (n & 1)
                        Mat *= base;
                    base *= base, n >>= 1;
                }
                n = Mat[0][0];
            }
        }
        printf("%lld\n", n);
    }
    return 0;
}

inline long long gcd(const long long x, const long long y) {
    if (!y)
        return x;
    return gcd(y, x % y);
}

inline long long get(const long long x) {
    if (x == 5)
        return 10;
    if (x % 5 == 1 || x % 5 == 4)
        return x - 1;
    return x + 1;
}

inline long long solve(long long P) {
    long long period = 1, tmp, pow;
    for (long long i = 2; i * i <= P; i++)
        if (!(P % i)) {
            pow = 1, P /= i;
            while (!(P % i)) pow *= i, P /= i;
            tmp = get(i) * pow;
            period = period / gcd(period, tmp) * tmp;
        }
    if (P != 1)
        period = period / gcd(period, get(P)) * get(P);
    return period;
}
