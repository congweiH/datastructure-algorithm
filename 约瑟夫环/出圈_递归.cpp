#include <iostream>
using namespace std;

// 还剩下 current 人的那一轮
int Num(int current, int k){
    if(current == 1){
        // 当剩下一个人，他的编号总是0
        return 0;
    }else{
        // 我们现在不知道下一轮的编号, 就问下一层，也就是这里 Num(current-1, k) 的含义
        return (Num(current - 1, k) + k) % current;
    }
}
int main(){

    int n, k;
    cin >> n >> k;
    // 编号 0 1 2 3 .... n-1

    
    // 最后记得+1，因为一开始题目编号规定是1-n。如果题目规定0到n-1，则不需要+1
    cout << Num(n, k) + 1 << endl;

    return 0;
}