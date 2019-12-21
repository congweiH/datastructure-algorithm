#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int nxt[maxn];
char s[maxn];
char t[maxn];

void getNext(char t[]) {
    nxt[0] = -1;
    int j = -1;
    int i = 0;
    int len = strlen(t);
    while (i < len) {
        if (j == -1 || t[j] == t[i]) {
            i++;
            j++;
            nxt[i] = j; // 这里不进一步优化
        } else {
            j = nxt[j];
        }
    }
}
int kmp(char s[], char t[], int pos = 0) {
    /*
     * 从s串中pos位置开始匹配
     */
    getNext(t);
    int i = pos;
    int j = 0;
    int count = 0; //匹配的次数
    int lens = strlen(s);
    int lent = strlen(t);
    while (i < lens) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = nxt[j];
        }
        if (j >= lent) {
            count++;    //计数加一
            j = nxt[j]; // 1. 可重叠计数
            // j = 0;   // 2. 不可重叠计数
            // return i - j; // 返回t串在s串中的位置
        }
    }
    // return -1;  //匹配不成功
    return count; //返回匹配的个数
}
int main() {
    cin >> s >> t;
    cout << kmp(s, t) << endl;
    return 0;
}