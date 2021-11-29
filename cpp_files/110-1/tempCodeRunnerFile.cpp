#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, Q;
    vector<long long> spe;
    cin >> N;
    spe.resize(N);
    for(long long i = 0; i < N; ++i){
        cin >> spe[i];
    }
    sort(spe.begin(), spe.end());
    cin >> Q;
    for(long long i = 0; i < Q; ++i){
        long long min, max;
        long long length;
        cin >> min >> max;
        auto minit = lower_bound(spe.begin(), spe.end(), min);
        auto maxit = upper_bound(spe.begin(), spe.end(), max);
        cout << maxit-minit << "\n";
    }
    return 0;
}