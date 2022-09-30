#include <iostream>
#include <vector>
using namespace std;
int main(){
    long long n;
    while(cin >> n){
        if(n==0) break;
        for(long long i = 1; i < n; ++i){
            long long turnoff;
            for(long long j = 1; j < n; ++j){
                turnoff = (turnoff + i) % j;
            }
            if(turnoff == 11){
                cout << i << "\n";
                break;
            }
        }
    }
    return 0;
}