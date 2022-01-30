#include <iostream>
#include <vector>
#define INF 1e15
using namespace std;
vector <long long> coinvalue, dp;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	long long n, q;
	cin >> n;
	coinvalue.resize(n);
	dp.resize(1e5+5, INF);
	for(long long i = 0; i < n; ++i){
		cin >> coinvalue[i];
	}
	dp[0] = 0;
	for(long long i = 0; i < coinvalue.size(); ++i){
		for(long long j = coinvalue[i]; j <= 1e5; ++j){
			dp[j] = min(dp[j], dp[j-coinvalue[i]]+1);
		}
	}
	cin >> q;
	for(long long i = 0; i < q; ++i){
		long long total = 0;
		cin >> total;
		total *= -1; 
		for(long long j = 0; j < n; ++j){
			long long temp;
			cin >> temp;
			total += (temp*coinvalue[j]);
		}
		cout << dp[total] << "\n";
	}
	
	return 0;
}