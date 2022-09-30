#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
//01背包問題
//!https://web.ntnu.edu.tw/~algo/KnapsackProblem.html#3
int main(){
    long long n;
    cin >> n;
    cin.ignore();
    while(n--){
        string str;
        long long sum = 0, weight;
        vector<long long> weights;
        vector<long long> dp;
        getline(cin, str);
        // cout << str << endl;
        stringstream ss(str);
        while(ss >> weight){ //分解string->int
            weights.push_back(weight);
            sum += weight;
        }
        if(sum % 2 == 1){ //if sum為基數->不可能兩個背包同重量
            cout << "NO\n";
            continue;
        }
        dp.resize(sum, 0);
        sum /= 2; 
        for(long long i = 0; i < weights.size(); ++i){
            for(long long j = sum; j-weights[i] >= 0; --j){
                dp[j] = max(dp[j], dp[j-weights[i]]+weights[i]);
            }
        }
        if(dp[sum] == sum){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
        // for(long long i = 0; i < dp.size(); ++i){
        //     cout << dp[i] << " ";
        // }
        // cout << endl << dp[sum]  << " "<< sum << endl;
     
    }
    return 0;
}