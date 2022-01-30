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
    pendamic(long long c, long long d){
        count = c;
        itdiff = d;
    }
};

vector<pendamic> period;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, M, S;
    cin >> N >> M >> S;
    vector<long long> dp(S+1);
    cilimpic.resize(N);
    long long totalcover = 0;
    for(long long i = 0; i < N; ++i){
        cin>>cilimpic[i];
    }
    sort(cilimpic.begin(), cilimpic.end());
    for(long long i = 0; i < M; ++i){
        long long a, b, c;
        cin >> a >> b >> c;
        vector<long long>::iterator it1 = lower_bound(cilimpic.begin(), cilimpic.end(), a);
        vector<long long>::iterator it2 = upper_bound(cilimpic.begin(), cilimpic.end(), b);
        long long tempint= it2-it1;
        totalcover += (tempint);
        pendamic temp(c, it2-it1);
        period.push_back(temp);
    }
    for(long long i = 1; i < M+1; ++i){
        for(long long j = S; j >= 0; --j){
            if(j >= period[i-1].count){
                dp[j] = max(dp[j], dp[j-period[i-1].count] + period[i-1].itdiff);
            }
        }
    }
    cout << dp[S] + (N-totalcover);
    return 0;

}