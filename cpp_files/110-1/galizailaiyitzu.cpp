#include <iostream>
#include <map>
#include <vector>
#define INF 1000000000000000000
using namespace std;
vector<long long>coinvalue;
vector<long long>dp;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	long long T, N;
    cin >> T;
    dp.resize(100001, INF);
    for(long long i = 0; i < T; ++i){
        long long temp;
        cin >> temp;
        coinvalue.push_back(temp);
    }
    dp[0] = 0;
    for(long long i = 0; i < coinvalue.size(); ++i){
        for(long long k = coinvalue[i]; k <= 100000; ++k){
            dp[k] = min(dp[k], dp[k-coinvalue[i]]+1);
        }
    }
    // for(auto a = dp.begin(); a != dp.end(); ++a){
        // cout << *a << " ";
    // }
    cin >> N;
    for(long long j = 0; j < N; ++j){
        long long priceneed, change, pricepaid = 0;
        cin >> priceneed;
        for(int k = 0; k < coinvalue.size(); ++k){
            long long temp;
            cin >> temp;
            pricepaid += coinvalue[k]*temp;
        } 
        change = pricepaid - priceneed;
        cout << dp[change] << "\n";
    }
    
    return 0;
}