#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int n;
int a[maxn];
int f[maxn];

int maxSubArray(int a[]) {
    int res = f[0] = a[0];
    for (int i = 1; i < n; i++) {
        f[i] = max(a[i], f[i - 1] + a[i]);
        res = max(res, f[i]);
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << maxSubArray(a) << endl;
    return 0;
}