#include <iostream>
#include <utility>
#include <vector>
#include <set>
using namespace std;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, p, leftbound, rightbound;
    cin >> N >> p >> leftbound >> rightbound;
    set<pair<long long, long long>> boundset;
    set<long long>sections;
    for(long long i = 0; i < N; ++i){
        long long left, right;
        cin >> left >> right;
        boundset.insert(make_pair(left, right));
    }
    for (auto it = boundset.begin(); it != boundset.end(); it++){
        long long currentleft = it->first, currentright = it->second, numofsection = 1;
        // cout << "it->first = "<< it->first  << " itsecond"<<it->second<< endl;
        if (currentleft > leftbound) break;
        if (currentleft < leftbound && currentright > rightbound){
            sections.insert(1);
            continue;
        }

        auto it2 = boundset.lower_bound({it->second, it->second}); //覺得是這裡有問題，但不知道該怎麼解決好
        if (it2 == boundset.end()){
            it2 = ++it;
        }         
        else{
            if(it2->first != it->second){
                if(it2 == prev(it2, 1)) continue;
                else if(it2->first > it->second) it2--;
            }
        }                                                 //till here
        
        while(it2 !=boundset.end()){
            // cout << "it2->first = "<< it2->first  << " it2second"<<it2->second<< endl;
            if (it2->first <= currentright){
                if(it2->second > currentright){
                    currentright = it2->second;
                    numofsection++;
                    // cout <<"currentleft"<< currentleft <<endl;
                    // cout <<"currentright"<< currentright<<endl;
                }
            }
            if(currentright >= rightbound) break;

            auto nextit = boundset.lower_bound({currentright, currentright}); //覺得是這裡有問題，但不知道該怎麼解決好
            if (nextit == boundset.end()){
                it2++;
            }
            else {
                if(nextit->first != currentright){
                    // cout <<" here1 "<< endl;
                    if(it2 == prev(nextit, 1)) break;
                    else if(nextit->first > currentright) it2 = --nextit;
                }
                else{
                    it2 = nextit; 
                    // cout <<" here "<< endl;
                }
            }                                               //till here
        }
        if (currentright >= rightbound){
            sections.insert(numofsection);
        }
    }

    
    if (sections.size() == 0) cout << "0";
    else cout << *sections.begin() * p;
    return 0;
}