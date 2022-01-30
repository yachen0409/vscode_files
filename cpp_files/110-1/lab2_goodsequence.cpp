#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
long long total = pow(10, 18);
void recur(long long *vectorbegin, long long *vectorend,long long sum){
    if(vectorend-vectorbegin <= 1){
        if(sum < total){
            total = sum;
        }
        return;
    }
    long long temp_sum = 0;
    long long mid_index = (vectorend-vectorbegin) / 2 ;
    vector<long long>temp_left (vectorbegin, vectorbegin+mid_index+1);
    nth_element(temp_left.begin(), temp_left.begin()+temp_left.size()/2, temp_left.end()); //findmedian(leftvector)
    for(int i = 0; i < temp_left.size(); ++i){
        temp_sum += abs(temp_left[i] - temp_left[temp_left.size()/2]);
    }
    recur(vectorbegin+mid_index+1, vectorend, sum+temp_sum);
    
    temp_sum = 0;
    vector<long long>temp_right (vectorbegin+mid_index+1, vectorend+1);
    nth_element(temp_right.begin(), temp_right.begin()+temp_right.size()/2, temp_right.end()); //findmedian(rightvector)
    for(int i = 0; i < temp_right.size(); ++i){
        temp_sum += abs(temp_right[i] - temp_right[temp_right.size()/2]);
    }
    recur(vectorbegin, vectorbegin+mid_index, sum+temp_sum);

}
int main(){
    long long n;
    vector <long long> seq;
    cin >> n;
    seq.resize(n);
    for(long long i = 0; i < n; ++i){
        long long temp;
        cin >> temp;
        seq[i] = temp;
    }
    recur(&seq.front(), &seq.back(), 0);
    cout << total;
    
    return 0;
}