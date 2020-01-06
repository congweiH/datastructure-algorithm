#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

char s[maxn]; //输入的字符串
char ma[maxn * 2];
int p[maxn * 2];

int Manacher(char s[]) {
    /*
     * 1. 将输入的字符串s每个字符之间插入一个#, 开头插入一个$,变成字符串ma
     */
    ma[0] = '$';
    ma[1] = '#';
    int len = strlen(s), tot = 2;
    for (int i = 0; i < len; i++) {
        ma[tot++] = s[i];
        ma[tot++] = '#';
    }
    ma[tot] = '\0';
    /*
     * 2. 开始更新
     */
    int mid = 0;
    int right = 0;
    int res = 0; // res 为最长回文子串的长度
    int pos = 0;
    for (int i = 1; i < tot; i++) {
        if (i < right)
            p[i] = min(p[2 * mid - i], right - i);
        else
            p[i] = 1;
        while (ma[i + p[i]] == ma[i - p[i]])
            p[i]++;
        if (right < i + p[i]) {
            mid = i;
            right = i + p[i];
        }
        // res = max(res, p[i] - 1);
        if (res < p[i] - 1) {
            res = p[i] - 1;
            pos = (i - p[i]) / 2;
        }
    }
    /*
     * 3. 可以返回一个具体实例ans
     */
    string ans = "";
    for (int i = pos; i < res + pos; i++) {
        ans += s[i];
    }
    return res;
}

int main() {
    cin >> s;
    cout << Manacher(s) << endl;
    return 0;
}