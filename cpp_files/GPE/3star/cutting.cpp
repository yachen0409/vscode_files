#include <iostream>
#include <vector>
using namespace std;
//http://worldofmonmon.blogspot.com/2018/02/uva-10003-cutting-sticks-dp.html
vector<vector<long long>>dp;
vector<long long> stick;
int main(){
    long long l, n;
    while(cin >> l){
        if(l == 0)break;
        cin >> n;
        dp.resize(55, vector<long long>(55, 0));
        stick.resize(n+2);
        stick[0] = 0; stick[n+1] = l;
        for(long long i = 1; i < n+1; ++i){
            cin >> stick[i];
        }
        for(long long range = 2; range < n+2; range++){
            for(long long begin = 0; begin < (n+2)-2; begin++){
                long long end = begin + range;
                if(end > n+1) break; //out of index
                dp[begin][end] = INT64_MAX;
                for(long long cut_point = begin+1; cut_point < end; ++cut_point){
                    dp[begin][end] = min(dp[begin][end], dp[begin][cut_point] + dp[cut_point][end] + stick[end] - stick[begin]);
                }
            }
        }
        cout << "The minimum cutting is "<< dp[0][n+1] << ".\n";
    }
    return 0;
}