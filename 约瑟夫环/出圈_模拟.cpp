#include <iostream>
#include <deque>
using namespace std;

int n;          // n 个人
int k;          // 报到k数字的人出圈，从1开始报
deque<int> Q;   // 模拟围成的圈

int main(){

    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        Q.push_back(i);         // 1~n 依次排成一排 :  1 2 3 4 ... n
    }

    while(Q.size() != 1){      // 直到最后只剩一个人退出循环
        for(int i = 0; i < k - 1; i++){ // 将k-1个人移至尾部
            int t = Q.front();  // 得到队列的第一个元素
            Q.pop_front();      // 并删除第一个元素
            Q.push_back(t);     // 将这个元素插入到队列的尾部：2 3 4 ..... n 1
        }
        Q.pop_front();          // 将这个人出圈
    }

    cout << Q.front() << endl;  // 最后就剩下一个人，输出即可
    
    return 0;
}