#include <cstdio>
using namespace std;

const int maxl = 50;
const unsigned long long mod = 2008;
unsigned long long val[maxl];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    unsigned long long v;
    char ch = getchar();
    while (m--) {
        v = 0;
        while (ch != 'O' && ch != 'X') ch = getchar();
        while (ch == 'O' || ch == 'X') v = (v << 1) | (ch == 'O'), ch = getchar();
        for (int i = maxl - 1; i >= 0; i--)
            if (v >> i) {
                if (!val[i]) {
                    val[i] = v;
                    break;
                }
                v ^= val[i];
            }
    }
    int cnt = 0;
    for (bool i : val) cnt += i;
    printf("%llu\n", ((unsigned long long)1 << cnt) % mod);
    return 0;
}
