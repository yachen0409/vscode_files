#include<iostream>
#include<vector>
using namespace std;

int main(){
    long long n, m;
    while(cin >> n >> m){
        vector<long long>steps(m);
        vector<long long>dp(1000005, 0);
        for(long long i = 0; i < m; ++i){
            cin >> steps[i];
        }
        for(long long i = 1; i < dp.size(); ++i){
            for(long long j = 0; j < m; ++j){
                if(i-steps[j] >= 0 && !dp[i-steps[j]]){
                    dp[i] = 1;
                    break;
                }
            }
        }
        if(dp[n]){
            cout << "Stan wins\n";
        }
        else{
            cout <<"Ollie wins\n";
        }
    }
    return 0;
}