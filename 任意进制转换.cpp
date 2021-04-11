/*
    实现2-62进制的转换 0-9 A-Z(10-35) a-z(36-61)
    https://ac.nowcoder.com/acm/problem/25993
*/

#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 10000 + 10;

// a进制数s -> b进制数t
int a, b;
char s[maxn], t[maxn];

int S[maxn]; // 因为 s 里面还有字符，所以需要将字符转换成数字方便计算: 0-9 A-Z(10-35) a-z(36-61)
int T[maxn]; // 对应t中的数字，之后还要将数字转换成对应的字符

int main(){

    cin >> a >> s;  // a = 4  s = "321"
    cin >> b;       // b = 10

    int lenS = strlen(s);
    // 将 s 字符转化成数字，保存在S数组中, 并且s 和 S 是反序的，比如 s = "1 2 3", 那么 S = "3 2 1" 
    for(int i = 0; i < lenS; i ++){     // S = "1 2 3"
        if(s[i] <= '9'){    // 0 - 9
            S[lenS - 1 - i] = s[i] - '0';
        }else if(s[i] >= 'a'){ // a - z
            S[lenS - 1 - i] = s[i] - 'a' + 36;
        }else{  // A - Z
            S[lenS - 1 - i] = s[i] - 'A' + 10;
        }
        //S[lenS - 1 - i] = s[i] - (s[i] < 58 ? 48 : s[i] < 97 ? 55 : 61); // 58='9', 48='0', 97='a', 55='A'-10, 61='a'-36
    }
    // 开始进制转换
    int lenT = 0;
    while(lenS){
        // 堆积在S[0]处
        for(int i = lenS - 1; i >= 1; i--){  // "1 2 3" -> "1 14 0" -> "17 1 0"
            S[i - 1] += S[i] % b * a;  
            S[i] /= b;              // s[i] 后面跟的不是 % b 就是 /b 不会出现 % a 和 /a 的情况
        }
        // 释放 S[0] 到 T 中
        T[lenT ++] = S[0] % b;      // T[0] = 17%10 = 7
        S[0] /= b;          // "17 1 0" -> "1 1 0"
        // 去掉后面的 0 
        for(; lenS > 0 && !S[lenS - 1]; lenS--);    // "1 1 0" -> "1 1"
    }
    // 将数字转换成字符
    for(int i = 0; i < lenT; i ++){
        if(T[i] <= 9){  // '0' - '9'
            t[lenT - 1 - i] = T[i] + '0';
        }else if(T[i] >= 36){   // 'a' - 'z'
            t[lenT - 1 - i] = T[i] - 36 + 'a';
        }else{  // 'A' - 'Z'
            t[lenT - 1 - i] = T[i] - 10 + 'A';
        }
        //t[lenT - 1 - i] = T[i] + (T[i] < 10 ? 48 : T[i] < 36 ? 55 : 61);
    }
    t[lenT] = '\0';

    cout << t << endl;  // t = "57"
    return 0;
}   