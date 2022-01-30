#include <iostream>
#include <vector>

using namespace std;
vector < vector<long long> > record;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	long long n, t;
	cin >> n >> t;
	record.resize(t, vector<long long>(n));
	for(long long i = 0; i < t; ++i){
		for(long long j = 0; j < n; ++j){
			cin >> record[i][j];
		}
	}
	for(long long i = t-2; i >= 0; --i){
		for(long long j = 0; j < n; ++j){
			if(n == 1){
				record[i][j] += record[i+1][j];
			}
			else if(j+1 < n && j-1 >= 0){	//left mid right
				record[i][j] += max(record[i+1][j-1], max(record[i+1][j], record[i+1][j+1]));
			}
			else if(j+1 >= n && j-1 >= 0){	//left mid
				record[i][j] += max(record[i+1][j-1], record[i+1][j]);
			}	
			else{	// mid right
				record[i][j] += max(record[i+1][j], record[i+1][j+1]);
			}		
		}
	}
	for(long long i = 0; i < n; ++i){
		cout << record[0][i] <<" ";
	}
	return 0;
}