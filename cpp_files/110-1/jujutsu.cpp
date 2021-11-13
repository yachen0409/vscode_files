#include<iostream>
#include<set>
using namespace std;

int main(){
    int end, num;
    set<int> location;
    multiset <int> dis;
    cin >> end >> num;
    location.insert(0);
    location.insert(end);
    for(int i = 0; i < num; ++i){
        int good;
        cin >> good;
        location.insert(good);
        
        auto upper = ++location.upper_bound(good);
        int temp = *(location.begin());
        for(auto it = location.begin(); it != location.end(); it++){
            int temp_dis = abs(*(it)-temp) / 2;
            dis.insert(temp_dis);
            temp = *it;
        }
        auto it_rever = dis.rbegin();
        cout << *(it_rever) << "\n";
    }
    return 0;
}