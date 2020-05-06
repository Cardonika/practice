#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#define ll long long
using namespace std;
ll num[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073, 4807526976, 7778742049, 12586269025, 20365011074, 32951280099, 53316291173, 86267571272, 139583862445, 225851433717, 365435296162, 591286729879, 956722026041, 1548008755920, 2504730781961, 4052739537881, 6557470319842, 10610209857723, 17167680177565, 27777890035288, 44945570212853, 72723460248141, 117669030460994, 190392490709135, 308061521170129, 498454011879264, 806515533049393, 1304969544928657, 2111485077978050, 3416454622906707, 5527939700884757, 8944394323791464, 14472334024676221, 23416728348467685, 37889062373143906, 61305790721611591, 99194853094755497, 160500643816367088, 259695496911122585, 420196140727489673, 679891637638612258};
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int anscount = 0, z;
bool inplacew(vector<string> board, int hrow, int srow)
{
    for (int i = hrow; i > -1; i--)
    {
        if (board[i][srow] == 'x')
            return false;
    }
    //左上方
    for (int i = hrow,j = srow; i > -1 && j > -1; i--, j--)
    {
        if (board[i][j] == 'x')
            return false;
    }
    //右上方
    for (int i = hrow,j = srow; i > -1 && j < z; i--, j++)
    {
        if (board[i][j] == 'x')
            return false;
    }
    return true;
}
void Queenplan(vector<string>& board, int hrow)
{
    if (hrow < z){
        for (int i = 0; i < z; i++){
            if (inplacew(board, hrow, i)){
                board[hrow][i] = 'x';
                Queenplan(board, hrow + 1);
                board[hrow][i] = '.';
            }
        }
    }else{
        anscount++;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    ll x;
    int m, judge = 0, ans = 0, r = 1;
    cin >> x >> m;
    for (int i = 0; i < 86; i++)
    {
        if (num[i] == x)
        {
            judge = 1;
            break;
        }
    }
    if (judge)
    { //尾0数
        int e;
        for (int i = 24;; i--)
        { //寻找m因数中最大质数e
            if (!(m % prime[i]))
            {
                e = prime[i];
                break;
            }
        }
        ll count = x / e;
        ll ans = count / e * (e + 1) + (1 + count / e / e) * count / e / e / 2 + (count - count / e * e);
        cout << ans << endl;
    }
    else
    { //皇后
        z = x % min(13, m) + 1;
        vector<string> board(z, string(z, '.')); //初始化棋盘
        Queenplan(board, 0);
        cout << anscount << endl;
    }
}