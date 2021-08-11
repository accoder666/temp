#include <iostream>
using namespace std;

const int maxn = 200010;
string str[maxn];

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    int t;
    cin >> t;
    int m;
    bool ans;
    while (t--) {
        cin >> m;
        for (int i = 1; i <= m; i++) cin >> str[i];
        ans = true;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                if (str[i][1] == str[j][0]) {
                    cout << 3 << endl << "aa" << endl;
                    ans = false;
                    break;
                }
        if (ans)
            cout << 2 << endl << str[1] << endl;
    }
    return 0;
}
