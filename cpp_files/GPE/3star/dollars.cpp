#include<iostream>
#include<vector>
#include<iomanip> //for setprecision and setw
using namespace std;
vector<long long>money = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
int main(){
    vector<long long>dp(30005, 0); //一定要long long
    double n;
    dp[0] = 1;
    for(long long i = 0; i < money.size(); ++i){
        for(long long j = money[i]; j < dp.size(); j+=5){
            dp[j] = dp[j] + dp[j-money[i]];
        }
    }
    long long num1, num2; 
    char dot;
    while(cin >> num1 >> dot >> num2){    //不能直接讀一個double會出事(精度問題)
        if(num1 == num2 && num1 == 0) break;
        // printf( "%3d.%02d%17lld\n", num1, num2, dp[num1*100+num2] );
        cout << fixed << setprecision(2) << setw(6) << double(num1+num2/100.0)  << setw(17) << dp[num1*100 + num2] << "\n";
        
    }
}