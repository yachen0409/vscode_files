#include <iostream>
#include <map>
using namespace std;

int main(){
    int num, num_find;
    map <int, int> list;
    cin >> num >> num_find;
    for(int i = 0; i < num; i++){
        int book;
        cin >> book;
        list[book] = i;
    }
    
    for(int i = 0; i < num_find; i++){
        int find;
        map <int, int>::iterator iter;
        cin >> find;
        iter = list.find(find);
        if(iter != list.end())
            cout<<iter->second<<"\n";
        else
            cout<<"-1"<<"\n";
    }
    return 0;
}