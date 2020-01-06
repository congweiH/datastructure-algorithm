#include <bits/stdc++.h>
using namespace std;
const int maxn = 200 + 10;

char s[maxn], t[maxn];
int dp[maxn][maxn];

void input() { cin >> s + 1 >> t + 1; }

int main() {
    input();

    int lens = strlen(s + 1), lent = strlen(t + 1);
    for (int i = 0; i <= lens; i++)
        dp[i][0] = 0;
    for (int i = 0; i <= lent; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= lens; i++)
        for (int j = 1; j <= lent; j++)
            if (s[i] == t[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    cout << dp[lens][lent] << endl;
    return 0;
}