#include <iostream>
#include <string>
#define MODNUM 1000000007
using namespace std;

long long binpow(long long a, long long b) {
  long long res = 1;
  while (b > 0) {
    if ((b%2) & 1) {
        res = res * a % MODNUM;
    }
    a = a * a % MODNUM;
    b /= 2;
  }
  return res;
}
int main(){
    long long n, a, b;
    cin >> a >> b >> n;
    for(long long i = 0; i < n; ++i){
        long long temp, ans;
        cin >> temp;
        if(temp == 1){
            cout << "1\n";
            continue; 
        }
        else{
            long long an;
            an = binpow(a, temp-1);
            ans = an +(( b/(a-1) * (an-1))%MODNUM);
            ans %= MODNUM;
            if(ans < 0){
                ans = ans + MODNUM ;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}