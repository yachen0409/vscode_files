#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <long long> height;
vector <long long> dpincrease, dpincreasereverse, dpdecrease, dpdecreasereverse;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N;
    cin >> N;
    height.resize(N, 0);
    dpincrease.resize(N, 1);
    dpdecrease.resize(N, 1);
    dpincreasereverse.resize(N, 1);
    dpdecreasereverse.resize(N, 1);
    for(long long i = 0; i < N; ++i){
        cin >> height[i];
    }
    for(long long i = 1; i < N; ++i){
        for(long long j = 0; j < i; ++j){
            if(height[i]>height[j] && dpincrease[i] < dpincrease[j]+1){
                dpincrease[i] = dpincrease[j]+1;
            }
            else if(height[i]<height[j] && dpdecrease[i] < dpdecrease[j]+1){
                dpdecrease[i] = dpdecrease[j]+1;
            }
            if(height[N-i-1]<height[N-1-j] && dpdecreasereverse[N-i-1] < dpdecreasereverse[N-j-1]+1){
                dpdecreasereverse[N-i-1] = dpdecreasereverse[N-j-1]+1;
            }
            else if(height[N-i-1]>height[N-j-1] && dpincreasereverse[N-i-1] < dpincreasereverse[N-j-1]+1){
                dpincreasereverse[N-i-1] = dpincreasereverse[N-j-1]+1;
            }
        }
    }
    
    long long maxformat1 = dpincrease[0]+dpdecreasereverse[0]-1, maxformat2 =  dpincreasereverse[0]+dpdecrease[0]-1;
    for (long long i = 1; i < N; ++i){
        if (dpincrease[i] + dpdecreasereverse[i] - 1 > maxformat1)
             maxformat1 = dpincrease[i] + dpdecreasereverse[i] - 1;

        if (dpincreasereverse[i] + dpdecrease[i] - 1 > maxformat2)
             maxformat2 = dpincreasereverse[i] + dpdecrease[i] - 1;
    }
    cout << "increase:\n";
    for(auto a = dpincrease.begin(); a!=dpincrease.end(); ++a){
        cout << *a << " ";
    }
    cout << "increasereverse:\n";
    for(auto a = dpincreasereverse.begin(); a!=dpincreasereverse.end(); ++a){
        cout << *a << " ";
    }
    cout << "decrease:\n";
    for(auto a = dpdecrease.begin(); a!=dpdecrease.end(); ++a){
        cout << *a << " ";
    }
    cout << "decreasereverse:\n";
    for(auto a = dpdecreasereverse.begin(); a!=dpdecreasereverse.end(); ++a){
        cout << *a << " ";
    }
    cout << max(maxformat1, maxformat2);

    return 0;
}