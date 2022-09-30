#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<long long> solve(vector<long long>&a, vector<long long> &b){
    vector<long long>ans(520, 0);
    for(long long i = 0; i < a.size(); ++i){
        for(long long j = 0; j < b.size(); ++j){
            ans[i+j] += a[i] * b[j];
        }
    }
    for(long long i = 1; i < ans.size(); ++i){
        ans[i] += ans[i-1]/10;
        ans[i-1] %= 10;
    }
    return ans;
}
int main(){
    string a, b;
    vector<long long> reverse_num1, reverse_num2, reverse_ans, ans;
    while(cin >> a >> b){
        reverse_num1.resize(260, 0); reverse_num2.resize(260, 0); reverse_ans.resize(520, 0); ans.resize(520, 0);
        for(long long i = 0; i < a.size(); ++i){
            reverse_num1[i] = a[a.size()-i-1] - '0';
        }
        for(long long i = 0; i < b.size(); ++i){
            reverse_num2[i] = b[b.size()-i-1] - '0';
        }
        reverse_ans = solve(reverse_num1, reverse_num2);
        int idx = 0;
        for(int i = reverse_ans.size()-1; i >= 0; --i){
            if(reverse_ans[i] != 0) {
                idx = i;
                break;
            }
        }
        for(int i = idx; i >= 0; --i){
            cout << reverse_ans[i];
        }
        cout << '\n';
    }
}