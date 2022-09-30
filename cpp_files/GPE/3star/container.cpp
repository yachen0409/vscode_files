#include<iostream>
#include<vector>
using namespace std;
long long calculate(long long n, long long capacity, vector<long long>milk){
    long long temp_sum = 0, temp_count = 1;
    for(long long i = 0; i < n; ++i){
        if(milk[i] > capacity){
            return n;
        }
        temp_sum += milk[i];
        if(temp_sum > capacity){
            temp_count++;
            temp_sum = milk[i];
        }
    }
    return temp_count;

}
int main(){
    long long n, m;
    while(cin >> n >> m){
        vector<long long>milk(n, 0);
        long long max_milk = 0, sum_milk = 0;
        for(long long i = 0; i < n; ++i){
            cin >> milk[i];
            sum_milk += milk[i];
            if(milk[i] > max_milk) max_milk = milk[i];
        } 
        long long ans = 0;
        while(max_milk <= sum_milk){
            long long mid = (max_milk+sum_milk)/2;
            // cout << "mid = " << mid;
            // long long temp_sum = 0, temp_count = 0;
            long long count = calculate(n, mid, milk);
            // cout << "count = "<<count << endl;
            if(count <= m){
                sum_milk = mid - 1;
            }
            else if(count > m){
                max_milk = mid + 1;
            }
            // else{
            // ans = max_milk;
                // break;
            // }
        }        
        cout << max_milk << "\n";

    }
    return 0;
}