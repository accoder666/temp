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

const int maxn = 200010;
int a[maxn], s[maxn], cnt;

int main() {
    int t, n;
    cin >> t;
    long long ans;
    while (t--) {
        cin >> n;
        cnt = ans = 0;
        cin >> a[1];
        for (int i = 2; i <= n; i++) {
            cin >> a[i];
            if (a[i] < a[i - 1])
                s[++cnt] = i;
        }
        for (int i = cnt; i > 0; i--) ans += a[s[i] - 1] - a[s[i]];
        cout << ans << endl;
    }
    return 0;
}
