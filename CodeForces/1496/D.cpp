#include <cstdio>
using namespace std;

const int maxn = 100010;
int L[maxn], R[maxn];
int p[maxn];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", p + i);
    L[1] = 1;
    for (int i = 2; i <= n; i++) L[i] = (p[i] > p[i - 1] ? L[i - 1] : i);
    R[n] = n;
    for (int i = n - 1; i; i--) R[i] = (p[i] > p[i + 1] ? R[i + 1] : i);
    int x, v = -1, val;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        val = (R[i] - i > i - L[i] ? R[i] - i : i - L[i]);
        if (val > v)
            x = i, v = val, flag = false;
        else if (val == v)
            flag = true;
    }
    if (flag) {
        printf("0\n");
        return 0;
    }
    int a = R[x] - x, b = x - L[x];
    if (a > b)
        a ^= b ^= a ^= b;
    for (int i = a; i <= b; i++)
        if (i & 1) {
            printf("0\n");
            return 0;
        }
    printf("1\n");
    return 0;
}
