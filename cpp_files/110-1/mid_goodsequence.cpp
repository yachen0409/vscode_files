#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
long long total = pow(10, 18);
void recur(long long *vectorbegin, long long *vectorend, long long sum){
    if(vectorend-vectorbegin <= 1){
        if(sum < total){
            total = sum;
        }
        return;
    }
    long long temp_sum = 0;
    long long mid_index = (vectorend-vectorbegin) / 2 ;
    // cout << "mid_index = "<<mid_index<<endl;
    vector<long long>temp_left (vectorbegin, vectorbegin+mid_index+1);
    
    auto leftmaxit = max_element(temp_left.begin(), temp_left.end());
    // cout << "leftmax:"<<*leftmaxit<<endl;

    // cout << "rightmax:"<<*rightmaxit<<endl;
    for(long long i = 0; i < temp_left.size(); ++i){
        temp_sum += *leftmaxit-temp_left[i];
    }
    recur(vectorbegin+mid_index+1, vectorend, sum + temp_sum);

    temp_sum = 0;
    vector<long long>temp_right (vectorbegin+mid_index+1, vectorend+1);
    auto rightmaxit = max_element(temp_right.begin(), temp_right.end());
    for(long long i = 0; i < temp_right.size(); ++i){
        temp_sum += *rightmaxit-temp_right[i] ;
    }
    // cout << temp_sum1 << " " << temp_sum2 << endl;
    
        // cout << "go left!" << endl;
    recur(vectorbegin, vectorbegin+mid_index, sum + temp_sum);
    
    
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long n;
    vector <long long> seq;
    cin >> n;
    seq.resize(n);
    for(long long i = 0; i < n; ++i){
        cin >> seq[i];
    }
    // sort(seq.begin(), seq.end());
    recur(&seq.front(), &seq.back(), 0);
    cout << total;
    return 0;
}