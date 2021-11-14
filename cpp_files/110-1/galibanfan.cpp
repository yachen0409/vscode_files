#include <iostream>
#include <map>
#include <vector>
using namespace std;
long long judgement(long long a){
    long long index = 0;
    if(a<5) index = 6;
    else if (a<10) index = 5;
    else if (a<50) index = 4;
    else if (a<100) index = 3;
    else if (a<500) index = 2;
    else if (a<1000) index = 1;
    return index;
}
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
            if(change[j]!=0){
                long long startindex = judgement(change[j]);
                for(long long k = startindex; k < 7; ++k){
                    long long unit;
                    switch(k){
                        case 0: unit = 1000; break;
                        case 1: unit = 500; break;
                        case 2: unit = 100; break;
                        case 3: unit = 50; break;
                        case 4: unit = 10; break;
                        case 5: unit = 5; break;
                        case 6: unit = 1; break;
                    }
                    long long countk = change[j]/unit;
                    if(money[k] == 0) continue;
                    else{
                        if(countk <= money[k]){
                            change[j] = change[j] - unit*(countk);
                            money[k] = money[k] - countk;
                        }
                        else{
                            change[j] = change[j] - money[k]*unit;
                            money[k] = 0;    
                        }
                    }
                    if(change[j] == 0) break;
                }
                if(change[j]!= 0){
                    needexchange = true;
                    break;
                } 
            }
        }
        if(needexchange) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}