#include<iostream>
#include<set>
using namespace std;
multiset<pair<long long, long long>> boundset;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, K;
    cin >> N >> K;
    for(long long i = 0; i < N; ++i){
        long long left, right;
        cin >> left >> right;
        boundset.insert(make_pair(left, right));
    }
    auto itset = boundset.begin();
    long long counter = 1;
    long long curleftbound = itset->first;
    long long currightbound = itset->second;
    itset++;
    // cout <<curleftbound << " " << currightbound << endl;
    while(itset != boundset.end()){
        if (itset->first == curleftbound){
            
        }        
    }
    return 0;
}