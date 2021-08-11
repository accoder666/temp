#include <iostream>
using namespace std;

const int maxn = 60;
const string str = "abacaba";
const int len = 7;
inline int check(const string&);
inline void print(const string&);

int main() {
    int T, n;
    cin >> T;
    string S, tS;
    while (T--) {
        cin >> n >> S;
        n--;
        int cnt = check(S);
        if (cnt > 1)
            cout << 'N' << 'o' << endl;
        else if (cnt == 1)
            print(S);
        else {
            bool printed = false, f;
            for (int i = 0; i <= n - len + 1; i++) {
                tS = S;
                f = true;
                for (int p = 0; p < len; p++)
                    if (tS[i + p] != '?' && str[p] != tS[i + p]) {
                        f = false;
                        break;
                    } else
                        tS[i + p] = str[p];
                if (f && check(tS) == 1) {
                    printed = true;
                    print(tS);
                    break;
                }
            }
            if (!printed)
                cout << 'N' << 'o' << endl;
        }
    }
    return 0;
}

inline int check(const string& S) {
    int cnt = 0, n = S.size();
    bool f;
    for (int i = 0; i <= n - len + 1; i++) {
        f = true;
        for (int p = 0; p < len; p++)
            if (str[p] != S[i + p]) {
                f = false;
                break;
            }
        if (f)
            cnt++;
    }
    return cnt;
}

inline void print(const string& S) {
    int n = S.size();
    cout << 'Y' << 'e' << 's' << endl;
    for (int i = 0; i < n; i++) cout << (char)((S[i] == '?') ? 'd' : S[i]);
    cout << endl;
    return;
}
