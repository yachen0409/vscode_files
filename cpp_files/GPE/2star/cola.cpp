#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    int coke_sum = 0, coke_empty = 0;
    while(cin >> n){
        coke_sum = n;
        coke_empty = n;
        while(coke_empty >= 3){
            coke_sum += (coke_empty / 3);
            coke_empty = (coke_empty / 3) + (coke_empty % 3);
        }    
        int ans = coke_empty == 2 ? coke_sum + 1 : coke_sum;
        cout << ans << '\n';
    }
    return 0;
}