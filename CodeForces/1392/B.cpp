#include <cctype>
#include <cstdio>
namespace io {
using namespace std;
struct istream {
#define M (1 << 25)
    int f;
    char buf[M], *ch = buf - 1;
    inline istream() { fread(buf, 1, M, stdin); }
    inline istream& operator>>(int& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    inline istream& operator>>(long long& x) {
        f = 1;
        while (!isdigit(*++ch))
            if (*ch == '-')
                f = -1;
        for (x = *ch & 15; isdigit(*++ch);) x = x * 10 + (*ch & 15);
        x *= f;
        return *this;
    }
    inline istream& operator>>(char& c) {
        c = *++ch;
        return *this;
    }
#undef M
} cin;
struct ostream {
#define M (1 << 25)
    char buf[M], *ch = buf - 1;
#define endl (char)10
    inline ostream& operator<<(int x) {
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
    inline ostream& operator<<(long long x) {
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
    inline ostream& operator<<(const char& x) {
        *++ch = x;
        return *this;
    }
    inline ~ostream() { fwrite(buf, 1, ch - buf + 1, stdout); }
#undef M
} cout;
}  // namespace io
using namespace io;

#include <climits>
using namespace std;

const int maxn = 200010;
int a[maxn];

int main() {
    int t, n, k;
    cin >> t;
    int min, max;
    while (t--) {
        cin >> n >> k;
        min = INT_MAX, max = INT_MIN;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (a[i] < min)
                min = a[i];
            if (a[i] > max)
                max = a[i];
        }
        k &= 1;
        for (int i = 1; i <= n; i++) a[i] = k ? (max - a[i]) : (a[i] - min);
        for (int i = 1; i < n; i++) cout << a[i] << ' ';
        cout << a[n] << endl;
    }
    return 0;
}
