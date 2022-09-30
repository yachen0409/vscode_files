#include <iostream>
#include <vector>
using namespace std;
vector<long long>ans;
void solve(long long num){
    bool hasans = true;
    long long i = 9;
    while(num != 1){
        if(num % i == 0){
            ans.push_back(i);
            num /= i;
            i = 9;
            continue;
        }
        i--;
        if(i==1){
            hasans = false;
            break;
        }
    }
    if (!hasans) cout << "-1\n";
    else{
        for(auto a = ans.rbegin(); a!= ans.rend(); ++a){
            cout << *a ;
        }
        cout << "\n";
    }
}
int main(){
    long long num;
    cin >> num;
    for (long long i = 0;i < num ; ++i){
        long long temp;
        ans.clear();
        cin >> temp;
        if(temp==1){
            cout << "1\n"; 
        }
        else{
            solve(temp);
        }
    }
    return 0;
}
