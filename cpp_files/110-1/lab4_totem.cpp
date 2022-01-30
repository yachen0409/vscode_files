#include<iostream>
#include<vector>
#define UPPERBOUND 10000001
#define MODNUM 1000000007
using namespace std;
vector<long long> onedtotem(UPPERBOUND);
vector<long long> fourdtotem(UPPERBOUND);
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N;
    cin >> N;
    onedtotem[1] = 1, onedtotem[2] = 3, onedtotem[3] = 5;
    fourdtotem[1] = 1, fourdtotem[2] =9, fourdtotem[3] = 21;
    for(long long i = 4; i < UPPERBOUND; ++i){
        onedtotem[i] = (onedtotem[i-1] + onedtotem[i-2]*2 + onedtotem[i-3])%MODNUM;
        fourdtotem[i] = (onedtotem[i]*4+fourdtotem[i-3])%MODNUM;
    }
    for(long long i = 0; i < N; ++i){
        long long target;
        cin >> target;
        cout << fourdtotem[target]<<"\n"; 
    }
    return 0;
}