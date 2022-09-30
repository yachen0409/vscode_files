#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
//https://kai-y.medium.com/uva-10057-a-mid-summer-nights-dream-ea0e5eb610dc
int main(){
    long long n;
    while(cin >> n){
        vector<long long>list(n, 0);
        long long ans1 = 0, ans2 = 0, ans3 = 0;
        for(long long i = 0; i < n; ++i){
            cin >> list[i];
        }
        sort(list.begin(), list.end());
        if(n % 2 == 1){ // odd num
            ans1 = list[n/2];
            for(long long i = 0; i < list.size(); ++i){
                if(list[i] == ans1){
                    ans2++;
                }
            }
            ans3 = 1;
        }
        else{
            long long bigger_median;
            ans1 = list[n/2 - 1];
            bigger_median = list[n/2];
            for(long long i = 0; i < list.size(); ++i){
                if(list[i] == ans1 || list[i] == bigger_median){
                    ans2++;
                }
            }
            ans3 = list[n/2] - ans1 + 1;
        }
        cout << ans1 << " " << ans2 << " " << ans3 << "\n";
    }
    return 0;
}