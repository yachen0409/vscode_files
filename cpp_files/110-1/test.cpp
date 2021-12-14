#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);
    int N;
    cin>>N;
    int seq[N];
    for(int i=0; i<N; i++)
        cin>>seq[i];
    vector <vector<long long>> dp(N, vector<long long> (N, INT_MIN));
    vector <vector<long long>> sum(N, vector<long long> (N, 0));
    for(int i=0; i<N; i++){
        sum[i][i]=seq[i];
        dp[i][i]=0;
    }
    for(int len=2; len<N; len+=2){
        for(int l=0; l+len<N; l++){
            int r=l+len;
            for(int i=l+1; i<r; i+=2){
                for(int j=r-1; j>=i; j-=2){
                    dp[l][r]=max(dp[l][r], dp[l][i-1]+dp[j+1][r]+dp[i][j]+(sum[l][i-1]*sum[j+1][r])-sum[i][j]);
                    sum[l][r]=sum[l][i-1]+sum[j+1][r]+sum[i][j];
                }
            }
        }
    }
    cout<<dp[0][N-1];
}