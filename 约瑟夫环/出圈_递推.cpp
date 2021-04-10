#include <iostream>
using namespace std;

int main(){

    int n;       // n个人
    // 这里编号从0开始，即 0 1 2 3 4 ..... n-1
    int k;      // 报到k数字的人出圈，每次从1开始报数
    cin >> n >> k;

    int num = 0;  // 当人数为1个人的时候，那个活下来的人的编号，它总是0，因为每次重新从0开始编号
    // 现在反推当人数为n的时候编号为多少
    for(int current = 2; current <= n; current++){
        // 当人数为current个人的时候那个活下来的编号
        num = (num + k) % current;
    }
    // 因为一开始的编号是 从0开始到n-1, 而题目是从1到n编号，所以+1
    cout << num + 1 <<endl;

    return 0;
}