#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<long long>ans(22, 0);
    ans[0] = 1;//0組人
    ans[2] = 1;//1組人
    for(long long i = 2; i <= 10; ++i){ //2組到10組
        long long temp = 0;
        for(long long j = 0; j < i; ++j){
            temp += ans[2*j] * ans[2*i - 2*j - 2];
        }
        ans[2*i] = temp;
    }
    long long temp;
    long long count = 0;
    while(cin >> temp){
        if(count != 0) cout << "\n";
        cout << ans[2*temp] << endl;
        count++; 
    }
    return 0;
}

