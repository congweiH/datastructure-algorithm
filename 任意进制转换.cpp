/*
    实现2-62进制的转换 0-9 A-Z(10-35) a-z(36-61)

*/

#include <iostream>
#include <cstring>
using namespace std;

// a进制数s -> b进制数t
int a, b;
char s[555], t[555];

int S[555]; // 因为 s 里面还有字符，所以需要将字符转换成数字方便计算: 0-9 A-Z(10-35) a-z(36-61)
int T[555]; // 对应t中的数字，之后还要将数字转换成对应的字符

int main(){

    cin >> a >> s;  // a = 4  s = "321"
    cin >> b;       // b = 10

    int lenS = strlen(s);
    // 将 s 字符转化成数字，保存在S数组中, 并且s 和 S 是反序的，比如 s = "1 2 3", 那么 S = "3 2 1" 
    for(int i = lenS - 1; i >= 0; i--){     // S = "1 2 3"
        S[lenS - 1 - i] = s[i] - (s[i] < 58 ? 48 : s[i] < 97 ? 55 : 61); // 58='9', 48='0', 97='a', 55='A'-10, 61='a'-36
    }
    // 开始进制转换
    int lenT = 0;
    while(lenS){
        for(int i = lenS - 1; i >= 1; i--){  // "1 2 3" -> "1 14 0" -> "17 1 0"
            S[i - 1] += S[i] % b * a;  
            S[i] /= b;  
        }
        T[lenT ++] = S[0] % b;      // T[0] = 17%10 = 7
        S[0] /= b;          // "17 1 0" -> "1 1 0"
        for(; 0 < lenS && !S[lenS - 1]; lenS--);    // "1 1 0" -> "1 1"
    }
    // 将数字转换成字符
    for(int i = 0; i < lenT; i++){ 
        t[lenT - 1 - i] = T[i] + (T[i] < 10 ? 48 : T[i] < 36 ? 55 : 61);
    }
    t[lenT] = '\0';

    cout << t << endl;  // t = "57"
    return 0;
}   