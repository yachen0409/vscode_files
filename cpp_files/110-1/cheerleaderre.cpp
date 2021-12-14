#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <long long> height, negheight;
vector <long long> dpincrease, dpincreasereverse, dpdecrease, dpdecreasereverse;
vector <long long> record1, record2;
long long binarysearch(vector<long long>& a, long long left, long long right, long long value){
    while (right - left > 1) {
        int temp = left + (right - left) / 2;
        if (a[temp] >= value)
            right = temp;
        else
            left = temp;
    }
    return right;
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N;
    cin >> N;
    height.resize(N, 0);
    negheight.resize(N, 0);
    record1.resize(N, 0);
    record2.resize(N, 0);
    for(long long i = 0; i < N; ++i){
        cin >> height[i];
        negheight[i] = -height[i];
    }
    long long size1 = 1, size2 = 1;
    record1[0] = height[0];
    record2[0] = negheight[0];
    dpincrease.push_back(size1);
    dpdecrease.push_back(size2);
    for(long long i = 1; i < N; ++i){
        if(height[i] <= record1[0]) {
            record1[0] = height[i];
            dpincrease.push_back(1);
        }
        else if(height[i] > record1[size1-1]){
            record1[size1++] = height[i];
            dpincrease.push_back(size1);
        }
        else {
            long long increaseposition = binarysearch(record1, -1, size1-1, height[i]);
            record1[increaseposition] = height[i];
            dpincrease.push_back(increaseposition+1);
        }
        if(negheight[i] <= record2[0]) {
            record2[0] = negheight[i];
            dpdecrease.push_back(1);
        }
        else if(negheight[i] > record2[size2-1]){
            record2[size2++] = negheight[i];
            dpdecrease.push_back(size2);
        }
        else {
            long long decreaseposition = binarysearch(record2, -1, size2-1, negheight[i]);
            record2[decreaseposition] = negheight[i];
            dpdecrease.push_back(decreaseposition+1);
        }
    }
    reverse(height.begin(), height.end());
    reverse(negheight.begin(), negheight.end());
    size1 = 1, size2 = 1, record1.resize(N, 0), record2.resize(N, 0);
    record1[0] = height[0];
    record2[0] = negheight[0];
    dpincreasereverse.push_back(size1);
    dpdecreasereverse.push_back(size2);
    for(long long i = 1; i < N; ++i){
        if(height[i] <= record1[0]) {
            record1[0] = height[i];
            dpincreasereverse.push_back(1);
        }
        else if(height[i] > record1[size1-1]){
            record1[size1++] = height[i];
            dpincreasereverse.push_back(size1);
        }
        else {
            long long increaseposition = binarysearch(record1, -1, size1-1, height[i]);
            record1[increaseposition] = height[i];
            dpincreasereverse.push_back(increaseposition+1);
        }
        if(negheight[i] <= record2[0]) {
            record2[0] = negheight[i];
            dpdecreasereverse.push_back(1);
        }
        else if(negheight[i] > record2[size2-1]){
            record2[size2++] = negheight[i];
            dpdecreasereverse.push_back(size2);
        }
        else {
            long long decreaseposition = binarysearch(record2, -1, size2-1, negheight[i]);
            record2[decreaseposition] = negheight[i];
            dpdecreasereverse.push_back(decreaseposition+1);
        }
    }
    long long maxformat1 = dpincrease[0]+dpincreasereverse[N-1]-1, maxformat2 =  dpdecreasereverse[0]+dpdecrease[N-1]-1;
    for (long long i = 1; i < N; ++i){
        if (dpincrease[i] + dpincreasereverse[N-i-1] - 1 > maxformat1)
             maxformat1 = dpincrease[i] + dpincreasereverse[N-i-1] - 1;

        if (dpdecreasereverse[N-i-1] + dpdecrease[i] - 1 > maxformat2)
             maxformat2 = dpdecreasereverse[N-i-1] + dpdecrease[i] - 1;
    }
    cout << max(maxformat1, maxformat2);
    return 0;
}