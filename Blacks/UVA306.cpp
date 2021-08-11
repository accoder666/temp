#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 210;
int n;
class node {
public:
    inline node operator*=(const node& rhs) {
        static int t[maxn];
        for (int i = 1; i <= n; i++) t[i] = a[rhs.a[i]];
        memcpy(a, t, sizeof(a));
        return *this;
    }
    int a[maxn];
};
node b, ans, tmp;
char s[maxn], a[maxn];

int main() {
    int k, len;
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) scanf("%d", b.a + i);
        while (cin >> k && k) {
            tmp = b;
            for (int i = 1; i <= n; i++) ans.a[i] = i;
            while (k) {
                if (k & 1)
                    ans *= tmp;
                tmp *= tmp, k >>= 1;
            }
            cin.get();
            cin.getline(s + 1, maxn);
            len = strlen(s + 1);
            for (int i = 1; i <= len; i++) a[ans.a[i]] = s[i];
            for (int i = len + 1; i <= n; i++) a[ans.a[i]] = ' ';
            for (int i = 1; i <= n; i++) cout << a[i];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
