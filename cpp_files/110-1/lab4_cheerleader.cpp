#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector <long long> seq, seqrever;
vector <long long> dpin, dpde, dpinrever, dpderever;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	long long n;
	cin >> n;
	seq.resize(n); seqrever.resize(n);
	for(long long i = 0; i < n; ++i){
		cin >> seq[i];
		seqrever[i] = -seq[i];
	}
	vector<long long>v, vde;
	v.push_back(seq[0]); vde.push_back(seqrever[0]);
	dpin.push_back(1); dpde.push_back(1); dpinrever.push_back(1); dpderever.push_back(1);
	
	for(long long i = 1; i < seq.size(); ++i){
		if(seq[i]>v.back()){
			v.push_back(seq[i]);
			dpin.push_back(v.size());
		}
		else{
			auto it = lower_bound(v.begin(), v.end(), seq[i]);
			*it = seq[i];
			dpin.push_back(it - v.begin() + 1);
		}
		
		if(seqrever[i]>vde.back()){
			vde.push_back(seqrever[i]);
			dpde.push_back(vde.size());
		}
		else{
			auto it2 = lower_bound(vde.begin(), vde.end(), seqrever[i]);
			*it2 = seqrever[i];
			dpde.push_back(it2 - vde.begin() + 1);
		}	
	}
	reverse(seq.begin(), seq.end());
	reverse(seqrever.begin(), seqrever.end());
	v.clear(); vde.clear();
	v.push_back(seq[0]); vde.push_back(seqrever[0]);
	
	for(long long i = 1; i < seq.size(); ++i){
		if(seq[i]>v.back()){
			v.push_back(seq[i]);
			dpinrever.push_back(v.size());
		}
		else{
			auto it = lower_bound(v.begin(), v.end(), seq[i]);
			*it = seq[i];
			dpinrever.push_back(it - v.begin() + 1);
		}
		
		if(seqrever[i]>vde.back()){
			vde.push_back(seqrever[i]);
			dpderever.push_back(vde.size());
		}
		else{
			auto it2 = lower_bound(vde.begin(), vde.end(), seqrever[i]);
			*it2 = seqrever[i];
			dpderever.push_back(it2 - vde.begin() + 1);
		}	
	}
	reverse(dpinrever.begin(), dpinrever.end());
	reverse(dpderever.begin(), dpderever.end());
	long long inbig = dpin[0] + dpinrever[0] - 1, debig = dpde[0] + dpderever[0] - 1;
	for(long long i = 1; i < dpin.size(); ++i){
		inbig = max(inbig, dpin[i]+dpinrever[i]-1);
		debig = max(debig, dpde[i]+dpderever[i]-1);
	}
	cout << max(inbig, debig);
	return 0;
}