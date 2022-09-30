#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<long long> ans (52, 0);
    ans[0] = 1;
    ans[1] = 2;
    for(long long i = 2; i < ans.size(); ++i){
        ans[i] = ans[i-1] + ans[i-2];
    }
    long long temp;
    while(cin >> temp){
        if(temp == 0) break;
        cout << ans[temp-1] << "\n";
    }
    
    return 0;
}