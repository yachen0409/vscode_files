#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
vector<long long>disjoint;
void init(){
    for(long long i = 0; i < disjoint.size(); ++i){
        disjoint[i] = i;
    }
}
long long find(long long a){
    return a == disjoint[a] ? a : find(disjoint[a]);
}
void merge(long long a, long long b){
    disjoint[find(a)] = find(b);
}
bool same(long long a, long long b){
    return find(a) == find(b);
}
int main(){
    long long num;
    long long count = 0;
    cin >> num;
    while(num--){
        long long point_num;
        long long connect = 0, not_connect = 0;
        cin >> point_num;
        disjoint.resize(point_num);
        init();
        string str;
        getline(cin, str);
        while(getline(cin, str)){
            if (str == "") break;
            stringstream ss(str);
            char operation;
            long long a, b;
            ss >> operation >> a >> b;
            if(operation == 'c'){
                merge(a-1, b-1);
            }
            else if(operation =='q'){
                if(same(a-1, b-1)){
                    connect++;
                }
                else{
                    not_connect++;
                }
            }
        }
        if (count > 0) cout << "\n"; 
        cout << connect << "," << not_connect << "\n";
        count++;
    }
    return 0;
}