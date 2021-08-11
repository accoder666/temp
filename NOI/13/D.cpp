#include <cctype>
#include <cstdio>
#include <queue>
using namespace std;

const int dx[] = { 0, 0, 1, -1 }, dy[] = { 1, -1, 0, 0 };
const int maxn = 110;
bool map[maxn][maxn];
queue<pair<int, int>> Q;

int main() {
    int n;
    scanf("%d", &n);
    char ch;
    for (int i = 1; i <= n; i++) {
        while (!isdigit(ch)) ch = getchar();
        for (int j = 1; j <= n; j++) map[i][j] = (ch == '0' || ch == '2' || ch == '5'), ch = getchar();
    }
    if (!map[1][1]) {
        printf("no\n0\n");
        return 0;
    }
    bool flag = false;
    int ans = 1;
    Q.push(make_pair(1, 1));
    map[1][1] = false;
    pair<int, int> u, t;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        if (u.first == n && u.second == n)
            flag = true;
        for (int i = 0; i < 4; i++) {
            t = make_pair(u.first + dx[i], u.second + dy[i]);
            if (t.first > 0 && t.first <= n && t.second > 0 && t.second <= n && map[t.first][t.second])
                map[t.first][t.second] = false, Q.push(t), ans++;
        }
    }
    printf(flag ? "yes\n" : "no\n");
    printf("%d\n", ans);
    return 0;
}
