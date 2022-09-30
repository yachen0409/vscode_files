#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<long long> ans;
void solve(string seq){
    long long sign = 1, num = 0, i;
    char operation;
    for(i = 1; i < seq.length(); ++i){
        if((seq[i]-'0') >= 0 && (seq[i]-'0') <= 9){
            num = num*10 + (seq[i]-'0');
        }
        else if(seq[i] == '-'){
            sign = -1;
        }
        else{
            operation = seq[i];
            break;
        }
    }
    num *= sign;
    // cout << "num = " << num << endl;
    if(operation == '+'){
        // cout << "here1" << endl;
        solve(seq.substr(i+1));
        long long temp = ans[0];
        ans[0] = num;
        for(long long j = 1; j < ans.size(); ++j){
            long long pre_cur = ans[j];
            ans[j] = ans[j-1] + temp; // v(i-1) + s(i-1)
            temp = pre_cur;
        }
    }
    else if(operation == '*'){
        // cout << "here2" << endl;
        solve(seq.substr(i+1));
        ans[0] *= num;
        for(long long j = 1; j < ans.size(); ++j){
            ans[j] *= ans[j-1];  //v(i-1) * s(i)
        }
    }
    else{
        // cout << "here3" << endl;
        for(long long j = 0; j < ans.size(); ++j){
            ans[j] = num;
            // cout << ans[j] << endl;
        }
        // cout << ans[0] << endl;
        // for(long long j = 0; j < ans.size(); ++j){
        //     cout << ans[j] << " " ;
        // }
        // cout << endl;
    }
    
}
int main(){
    long long num;
    string seq;
    while(cin >> seq >> num){
        ans.resize(55, 0);
        solve(seq);
        for(long long i = 0; i < num; ++i){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}