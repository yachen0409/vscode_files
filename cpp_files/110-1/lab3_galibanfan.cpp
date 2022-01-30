#include <iostream>
#include <vector>
using namespace std;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	long long T, N;
    cin >> T;
    for(long long i = 0; i < T; ++i){
        vector<long long> priceneed, change, pricepaid;
        vector <long long> money;
        bool needexchange = false; 
        cin >> N;
        pricepaid.resize(N, 0);
        priceneed.resize(N, 0);
        change.resize(N, 0);
        money.resize(7, 0);
        for(long long j = 0; j < N; ++j){
            cin >> priceneed[j];
            for(int k = 0; k < 7; ++k){
                long long temp;
                cin >> temp;
                money[k] += temp;
                switch(k){
                    case 0: pricepaid[j] += 1000*temp; break;
                    case 1: pricepaid[j] += 500*temp; break;
                    case 2: pricepaid[j] += 100*temp; break;
                    case 3: pricepaid[j] += 50*temp; break;
                    case 4: pricepaid[j] += 10*temp; break;
                    case 5: pricepaid[j] += 5*temp; break;
                    case 6: pricepaid[j] += 1*temp; break;
                }
            } 
            change[j] = pricepaid[j] - priceneed[j];
        }
        for(long long j = 0; j < N; ++j){
            if (change[j] == 0) continue;
            if(change[j] >= 1000){
                long long countk = change[j]/1000;
                if(countk <= money[0]){
                    change[j] = change[j] - 1000*(countk);
                    money[0] = money[0] - countk;
                }
                else{
                    change[j] = change[j] - money[0]*1000;
                    money[0] = 0;    
                }
            }
            if(change[j] >= 500){
                long long countk = change[j]/500;
                if(countk <= money[1]){
                    change[j] = change[j] - 500*(countk);
                    money[1] = money[1] - countk;
                }
                else{
                    change[j] = change[j] - money[1]*500;
                    money[1] = 0;    
                }
            }
            if(change[j] >= 100){
                long long countk = change[j]/100;
                if(countk <= money[2]){
                    change[j] = change[j] - 100*(countk);
                    money[2] = money[2] - countk;
                }
                else{
                    change[j] = change[j] - money[2]*100;
                    money[2] = 0;    
                }
            }
            if(change[j] >= 50){
                long long countk = change[j]/50;
                if(countk <= money[3]){
                    change[j] = change[j] - 50*(countk);
                    money[3] = money[3] - countk;
                }
                else{
                    change[j] = change[j] - money[3]*50;
                    money[3] = 0;    
                }
            }
            if(change[j] >= 10){
                long long countk = change[j]/10;
                if(countk <= money[4]){
                    change[j] = change[j] - 10*(countk);
                    money[4] = money[4] - countk;
                }
                else{
                    change[j] = change[j] - money[4]*10;
                    money[4] = 0;    
                }
            }
            if(change[j] >= 5){
                long long countk = change[j]/5;
                if(countk <= money[5]){
                    change[j] = change[j] - 5*(countk);
                    money[5] = money[5] - countk;
                }
                else{
                    change[j] = change[j] - money[5]*5;
                    money[5] = 0;    
                }
            }
            if(change[j] >= 1){
                long long countk = change[j]/1;
                if(countk <= money[6]){
                    change[j] = change[j] - 1*(countk);
                    money[6] = money[6] - countk;
                }
                else{
                    change[j] = change[j] - money[6]*1;
                    money[6] = 0;    
                }
            }
            if(change[j]!= 0){
                needexchange = true;
                break;
            } 
        }
        if(needexchange) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}