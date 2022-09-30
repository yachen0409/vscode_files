#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<long long>prime;
    vector<long long>num(10005, 0);
    num[1] = 1;
    for(long long i = 2; i < num.size(); ++i){
        if(num[i] == 0){
            for(long long j = i + i; j < num.size(); j += i){
                num[j] = 1;
            }
            prime.push_back(i);
        }
    }
    long long n;
    while(cin >> n){
        if(n==0) break;
        long long count = 0;
        for(long long i = 0; prime[i] <= n; ++i){
            long long sum = 0;
            for(long long j = i; sum <= n; ++j){
                sum += prime[j];
                if(sum == n){
                    count++;
                    break;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}