#include <iostream>
#include <vector>
#define NEGINF -1e7
using namespace std;
long long n;
vector <long long> seq;
vector < vector<long long> > aprime, reward;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n;
	seq.resize(n);
	aprime.resize(n, vector<long long>(n, 0));
	reward.resize(n, vector<long long>(n, NEGINF));
	
	for(long long i = 0; i < n; ++i){
		cin >> seq[i]; 
	}	
	for(long long i = 0 ;i < n; ++i){
		aprime[i][i] = seq[i];
		reward[i][i] = 0;
	}
	
	for(long long len = 2; len < n; len+=2){
		for(long long left = 0; left + len < n; left++){
			long long right = left + len;
			for(long long k1 = left+1; k1 < right; k1+=2){
				for(long long k2 = right-1; k2 >= k1; k2-=2){
					reward[left][right] = max(reward[left][right], reward[left][k1-1] + reward[k1][k2] + reward[k2+1][right] + (aprime[left][k1-1]*aprime[k2+1][right]-aprime[k1][k2]));
					aprime[left][right] = aprime[left][k1-1] + aprime[k1][k2] + aprime[k2+1][right]; 
				}
			}
		}
	}
	cout << reward[0][n-1];
	return 0;
}