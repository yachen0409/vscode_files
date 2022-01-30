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
        if (currentleft > leftbound) break;
        if (currentleft < leftbound && currentright > rightbound){
            sections.insert(1);
            continue;
        }
        auto it2 = boundset.lower_bound({it->second, it->second});
        if (it2 == boundset.end()){
            it2 = ++it;
        }         
        else{
            if(it2->first != it->second){
                if(it2 == prev(it2, 1)) continue;
                else if(it2->first > it->second) it2--;
            }
        } 
        while(it2 !=boundset.end()){
            if (it2->first <= currentright){
                if(it2->second > currentright){
                    currentright = it2->second;
                    numofsection++;
                }
            }
            if(currentright >= rightbound) break;

            auto nextit = boundset.lower_bound({currentright, currentright}); 
            if (nextit == boundset.end()){
                it2++;
            }
            else {
                if(nextit->first != currentright){
                    if(it2 == prev(nextit, 1)) break;
                    else if(nextit->first > currentright) it2 = --nextit;
                }
                else{
                    it2 = nextit; 
                }
            }                                         
        }
        if (currentright >= rightbound){
            sections.insert(numofsection);
        }
    }
    if (sections.size() == 0) cout << "0";
    else cout << *sections.begin() * p;
    return 0;
}