#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<long long> cilimpic;
long long finalcount;
class pendamic{
    public:
    vector<long long>::iterator start, end;
    long long count, itdiff;
    // double rate;
    pendamic(long long c, long long d){
        count = c;
        itdiff = d;
        // rate = itdiff/count;
    }
};

vector<pendamic> period;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, M, S;
    cin >> N >> M >> S;
    vector<vector<long long>> dp(2, vector<long long>(S+1));
    cilimpic.resize(N);
    long long totalcover = 0;
    for(long long i = 0; i < N; ++i){
        cin>>cilimpic[i];
    }
    // finalcount = cilimpic.size();
    sort(cilimpic.begin(), cilimpic.end());
    for(long long i = 0; i < M; ++i){
        long long a, b, c;
        cin >> a >> b >> c;
        vector<long long>::iterator it1 = lower_bound(cilimpic.begin(), cilimpic.end(), a);
        vector<long long>::iterator it2 = upper_bound(cilimpic.begin(), cilimpic.end(), b);
        // cout <<*it1<<" "<<*it2<< it2-it1<<endl;
        long long tempint= it2-it1;
        totalcover += (tempint);
        pendamic temp(c, it2-it1);
        period.push_back(temp);
    }
    // dp.resize(M+2);
    // cout << cilimpic.size()<<" "<<totalcover << endl;
    pendamic temp(0, cilimpic.size()-totalcover);
    period.push_back(temp);
    // for(long long i = 0; i < dp.size(); ++i){
    //     dp[i].resize(S+1);
    // }
    // cout << "ok" << endl;
    for(long long i = 0; i < M+2; ++i){
        for(long long j = 0; j < S+1; ++j){
            // if(i == 0 && j > 0){
            //     dp[i][j] = cilimpic.size() - totalcover;
            // }
            if(i == 0 || j == 0){
                dp[i%2][j] = 0;
            }
            else if(period[i-1].count <= j){
                dp[i%2][j] = max(period[i-1].itdiff + dp[(i-1)%2][j-period[i-1].count], dp[(i-1)%2][j]);
            }
            else{
                dp[i%2][j] = dp[(i-1)%2][j];
            }
        }
        // cout << "hi"<<endl;
    }
    // cout << "teah"<<endl;
    cout << dp[(M+1)%2][S];
    // for(long long i = 0; i < dp.size(); ++i){
    //     for(long long j = 0; j < S+1; ++j){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;

}