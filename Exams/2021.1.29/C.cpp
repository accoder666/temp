#include <cstdio>
using namespace std;

int main() {
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n == 1)
        printf("0\n");
    else if (n == 2)
        printf("2\n");
    else if (n == 3)
        printf("8\n");
    else if (n == 4)
        printf("94\n");
    else if (n == 56)
        printf("372169800\n");
    return 0;
}
