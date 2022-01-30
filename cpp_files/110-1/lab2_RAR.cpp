#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
/*
If i = 0, Ri = {1}
Otherwise, Ri is constructed as follows,
A = Reverse(R_(i-1))
B = Add(R_(i-1), 2^(i - 1))
*/
void vector_reverse(vector<long long> &a){
    std::reverse(a.begin(), a.end());
}
void add(vector<long long>&a, int j){
    for(int i = 0; i < a.size(); ++i){
        a[i] += j;
    }
}
void rotate(vector<long long> &a, vector<long long> &b){
    b.insert(b.end(), a.begin(), a.end());
}
int main(){
    long long i;
    cin >> i;
    vector<long long> sequence = {1};
    for(int j = 0; j < i; ++j){
        vector<long long> temp1 = sequence, temp2 = sequence;
        vector_reverse(temp1);
        add(temp2, pow(2, j));
        rotate(temp1, temp2);
        sequence = temp2;
    }
    for(int j = 0; j < sequence.size(); ++j){
        cout << sequence[j] << " ";
    }
    return 0;
}