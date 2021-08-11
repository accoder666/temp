#include <cctype>
#include <cstdio>
using namespace std;

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int a, b, c, d;
    char ch;
    while (t--) {
        a = b = c = d = 0;
        ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        while (isdigit(ch)) a = ((a << 3) + (a << 1) + ch - '0') & 1, ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        while (isdigit(ch)) b = ((b << 3) + (b << 1) + ch - '0') % 3, ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        while (isdigit(ch)) c = ((c << 3) + (c << 1) + ch - '0') & 1, ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        while (isdigit(ch)) d = ((d << 3) + (d << 1) + ch - '0') % 3, ch = getchar();
        printf("%d\n", ((a + c) & 1) != (b + d) % 3);
    }
    return 0;
}
