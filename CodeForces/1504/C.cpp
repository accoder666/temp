#include <cstdio>
using namespace std;

const int maxn = 200010;
char a[maxn], b[maxn];
char s[maxn];
int S[maxn], top;

int main() {
    int t;
    scanf("%d", &t);
    int n;
    bool ans;
    int sum, f, l;
    while (t--) {
        scanf("%d", &n);
        scanf("%s", s);
        top = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0')
                S[++top] = i;
            while (top > 1)
                if (s[S[top]] == s[S[top - 1]] && s[S[top]] == '0') {
                    a[S[top - 1]] = b[S[top]] = '(', a[S[top]] = b[S[top - 1]] = ')';
                    top -= 2;
                } else
                    break;
        }
        if (top) {
            printf("NO\n");
            continue;
        }
        ans = true;
        f = 0, l = n - 1;
        while (f < l) {
            while (f < n && s[f] != '1') f++;
            while (l >= 0 && s[l] != '1') l--;
            if (f >= l)
                break;
            a[f] = b[f] = '(', a[l] = b[l] = ')';
            f++, l--;
        }
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i] == '(' ? 1 : -1;
            ans &= (sum >= 0);
        }
        ans &= !sum;
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += b[i] == '(' ? 1 : -1;
            ans &= (sum >= 0);
        }
        ans &= !sum;
        if (!ans) {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        a[n] = b[n] = '\0';
        printf("%s\n%s\n", a, b);
    }
    return 0;
}
