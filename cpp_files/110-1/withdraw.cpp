#include<iostream>
#include<utility>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    int num;
    queue<pair<int, int>> list;
    cin >> num;
    for(int i = 0; i < num; ++i){
        int id, potential;
        cin >> id >> potential;
        list.push(make_pair(id, potential));
    }
    while(!list.empty()){
        pair<int, int> temp = list.front();
        cout << temp.first << "\n";
        temp.second -= 1;
        list.pop();
        if(temp.second != 0){
            list.push(make_pair(temp.first, temp.second));
        }
    }
    return 0;
}