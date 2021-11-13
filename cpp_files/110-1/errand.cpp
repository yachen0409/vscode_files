#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    long long num_of_book, limit, time, count = 0;
    vector<long long> list;
    cin >> num_of_book >> limit >> time;
    for(long long i = 0; i < num_of_book; ++i){
        long long temp;
        cin >> temp;
        list.push_back(temp);
    }
    sort(list.begin(), list.end());
    //for(auto itr : list)
    //   cout << itr << " ";
    //cout <<endl;
    long long* p1 = &list.front();
    long long* p2 = &list.back();
    while(p1 < p2){
        if(*p1 + *p2 > limit){
            p2--;
            count++;
        }
        else{
            p1++;
            p2--;
            count++;
        }
    }
    if(p1 == p2){
        count++;
    }
    cout << count*time*2 << "\n";

    return 0;
}