#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long n, m;
vector< vector<long long> > adjlist, adjrever, adjscc;
vector<long long> finish, scc;
vector<bool> visit1, visit2, visit3;
vector <long long> numperscc, dp;
void dfs1(long long start){
	visit1[start] = true;
	for(auto a = adjlist[start].begin(); a != adjlist[start].end(); ++a){
		if(!visit1[*a]){
			dfs1(*a);
		}
	}
	finish.push_back(start);
}
void dfs2(long long start, long long group){
	scc[start] = group;
	visit2[start] = true;
	for(auto a = adjrever[start].begin(); a != adjrever[start].end(); ++a){
		if(!visit2[*a]){
			dfs2(*a, group);
		}
	}
}
void dfs3(long long start){
	visit3[start] = true;
	for(auto a = adjscc[start].begin(); a != adjscc[start].end(); ++a){
		if(!visit3[*a]){
			dfs3(*a);
		}
		dp[start] = max(dp[start], dp[*a]+numperscc[start]);
	}
}
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	cin >> n >> m;
	adjlist.resize(n, vector<long long>());
	adjrever.resize(n, vector<long long>());
	scc.resize(n);
	visit1.resize(n, false); visit2.resize(n, false); visit3.resize(n, false);
	for(long long i = 0; i < m; ++i){
		long long t1, t2;
		cin >> t1 >> t2;
		adjlist[t1].push_back(t2);
		adjrever[t2].push_back(t1);
	}
	for(long long i = 0; i < n; ++i){
		if(!visit1[i]) dfs1(i);
	}
	reverse(finish.begin(), finish.end());
	long long counter = 0;
	for(long long i = 0; i < finish.size(); ++i){
		if(!visit2[finish[i]]) dfs2(finish[i], counter++);
	}
	numperscc.resize(counter);
	dp.resize(counter);
	adjscc.resize(counter, vector<long long>());
	
	for(long long i = 0; i < scc.size(); ++i){
		numperscc[scc[i]]++;
	}
	for(long long i = 0; i < counter; ++i){
		dp[i] = numperscc[i];
	}
	for(long long i = 0; i < n; ++i){
		for(auto a = adjlist[i].begin(); a!=adjlist[i].end(); ++a){
			if(scc[i]!= scc[*a]){
				adjscc[scc[i]].push_back(scc[*a]);
			}
		}
	}
	for(long long i = 0; i < counter; ++i){
		if(!visit3[i]) dfs3(i);
	}
	cout << *max_element(dp.begin(), dp.end());
	return 0;
}