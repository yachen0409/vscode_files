#include <iostream>
#include <vector>
#include <algorithm>
#define UNDEFINED -10000000
using namespace std;
vector<long long> seq;
// vector<long long> aprime;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N;
    cin >> N;
    seq.resize(N+1, 0);
    vector<vector<long long>> r(N+1, vector<long long>(N+1, UNDEFINED));
    vector <vector<long long>> aprime(N+1, vector<long long> (N+1, 0));
    // aprime.resize(N+1, 0);

    for(long long i = 1; i < N+1; ++i){
        long long temp;
        cin >> seq[i];
        aprime[i][i]=seq[i];
        r[i][i]=0;
    }
    // for(long long i = 1; i < N+1; ++i){
    //     for(long long j = 1; j < N+1; ++j){
    //         cout << aprime[i][j]<<" ";
    //     }
    //     cout << endl;
    // }

    for(long long len = 2; len < N+1; len+=2){
        // cout << "len="<<len<<endl;
        for(long long left = 1; left+len < N+1; left++){
            long long right = left + len;
            // cout << "right="<<right<<" left="<<left<<endl;

            for(long long k1 = left+1; k1 < right; k1+=2){
                for(long long k2 = right-1; k2>= k1; k2-=2){
                    // cout << "k1="<<k1<<" k2="<<k2<<endl;
                    r[left][right]=max(r[left][right], r[left][k1-1]+r[k2+1][right]+r[k1][k2]+(aprime[left][k1-1]*aprime[k2+1][right])-aprime[k1][k2]);
                    aprime[left][right]=aprime[left][k1-1]+aprime[k2+1][right]+aprime[k1][k2];
                }
            }
        }
    }
    // for(long long i = 1; i < N+1; ++i){
    //     for(long long j = 1; j < N+1; ++j){
    //         cout << r[i][j]<<" ";
    //     }
    //     cout << endl;
    // }
    
    cout << r[1][N];
    return 0;
}