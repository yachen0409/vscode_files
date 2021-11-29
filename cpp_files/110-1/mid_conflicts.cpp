#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long sum = 0;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> first;
    vector<int> second;
    first.resize(N);
    second.resize(N);
    for(int i = 0; i < N ; ++i){
        cin >> first[i];
    }
    for(int i = 0; i < N ; ++i){
        cin >> second[i];
    }
    sort(first.begin(), first.end());
    sort(second.begin(), second.end(), greater<int>());
    for(int j = 0; j < N; ++j){
        sum += first[j] * second[j];
    }
    cout << sum;
    return 0;
}