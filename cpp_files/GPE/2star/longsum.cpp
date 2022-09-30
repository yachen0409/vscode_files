#include <iostream>
#include <vector>
using namespace std;
vector<int> solve(vector<int>&num1, vector<int>&num2, long long num_digit){
    vector<int>ans(num_digit, 0);
    for(long long i = 0; i < num_digit; ++i){
        ans[i] = num1[i] + num2[i];
    }
    for(long long i = num_digit-1; i > 0; --i){
        if(ans[i] >= 10){
            ans[i-1] += (ans[i]/10);
            ans[i] %= 10;
        }
    }
    return ans;
}
int main(){
    long long num, count = 0;
    cin >> num;
    for(long long i = 0; i < num; ++i){
        long long num_digit;
        vector<int> num1, num2;
        if(count!=0)cout << "\n";
        cin >> num_digit;
        for(long long j = 0; j < num_digit; ++j){
            long long temp1, temp2;
            cin >> temp1 >> temp2;
            num1.push_back(temp1);
            num2.push_back(temp2);
        }
        vector<int> ans = solve(num1, num2, num_digit);
        for(long long j = 0; j < ans.size(); ++j){
            cout << ans[j];
        }
        cout << endl;
        count++;
    }
    return 0;
}