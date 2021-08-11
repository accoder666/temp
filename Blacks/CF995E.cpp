#include <chrono>
#include <cstdio>
#include <random>
using namespace std;

const int maxn = 110;
int solve(const int&, const int&);
mt19937 r(chrono::system_clock::now().time_since_epoch().count());
bool ans[2][maxn];

int main() {
    int u, v, p;
    scanf("%d %d %d", &u, &v, &p);
    uniform_int_distribution<int> R(1, p - 1);
    int len1 = 0, len2 = 0;
    int x, y;
    do y = R(r), x = (long long)u * y % p;
    while (solve(x, y) > 100);
    while (y)
        if (x < y)
            len1++, x ^= y ^= x ^= y;
        else
            ans[0][++len1] = true, x -= y;
    do y = R(r), x = (long long)v * y % p;
    while (solve(x, y) > 100);
    while (y)
        if (x < y)
            len2++, x ^= y ^= x ^= y;
        else
            ans[1][++len2] = true, x -= y;
    printf("%d\n", len1 + len2);
    for (int i = 1; i <= len1; i++) printf("%d ", 3 - ans[0][i]);
    for (int i = len2; i; i--) printf("%d ", 3 - (ans[1][i] << 1));
    return 0;
}

int solve(const int& a, const int& b) {
    if (!b)
        return 0;
    return solve(b, a % b) + a / b + 1;
}
