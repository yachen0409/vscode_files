#include <iostream>
#include <set>
using namespace std;

int main(){
    long long num;
    cin >> num;
    for(long long i = 0; i < num; ++i){
        long long days, parties;
        set<long long> hartals;
        cin >> days >> parties;
        for(long long j = 0; j < parties; ++j){
            long long temp;
            cin >> temp;
            for(long long k = 1; k*temp <= days; ++k){
                if(((k*temp%7) != 6) && ((k*temp%7) != 0)){
                    hartals.insert(k*temp);
                    // cout << "insert "<<k*temp << endl;
                }
            }
        }
        cout << hartals.size() << endl;
    }
    return 0;
}