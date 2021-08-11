#include <cstdio>
using namespace std;

const int maxn = 200010, maxv = 2500010;
int a[maxn], p1[maxv << 1], p2[maxv << 1];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int sum;
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++) {
            sum = a[i] + a[j];
            if (!p1[sum])
                p1[sum] = i, p2[sum] = j;
            else if (p1[sum] != i && p1[sum] != j && p2[sum] != i && p2[sum] != j) {
                printf("YES\n");
                printf("%d %d %d %d\n", i, j, p1[sum], p2[sum]);
                return 0;
            }
        }
    printf("NO\n");
    return 0;
}
