#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int n;
int a[maxn];
int dp[maxn];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

int main() {
    input();

    int sum = dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        dp[i] = max(a[i], dp[i - 1] + a[i]);
        sum = max(sum, dp[i]);
    }
    cout << sum << endl;
    return 0;
}