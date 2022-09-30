#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
    long long n;
    vector<long long>num, lis, lds;
    while(cin >> n){
        vector<long long>temp_vec;
        num.resize(n);lis.resize(n);lds.resize(n);
        for(long long i = 0; i < n; ++i){
            // long long temp;
            cin >> num[i];
            // num.push_back(temp);
        }
        temp_vec.push_back(num[0]);
        lis[0] = 1;
        long long lis_length = 1;
        for(long long i = 1; i < n; ++i){

            if(num[i] > temp_vec.back()){
                temp_vec.push_back(num[i]);
                lis[i] = ++lis_length;
            }
            else{
                auto it = lower_bound(temp_vec.begin(), temp_vec.end(), num[i]);
                *it = num[i];
                lis[i] = it-temp_vec.begin()+1;
            }
        }

        vector<long long>temp_vec2;
        temp_vec2.push_back(num[n-1]);
        lds[n-1] = 1;
        long long lds_length = 1;
        for(long long i = n-2; i >= 0; --i){

            if(num[i] > temp_vec2.back()){
                temp_vec2.push_back(num[i]);
                lds[i] = ++lds_length;
            }
            else{
                auto it = lower_bound(temp_vec2.begin(), temp_vec2.end(), num[i]);
                *it = num[i];
                lds[i] = it-temp_vec2.begin()+1;
            }
        }
        // for(long long i = 0; i < n; ++i){cout << lis[i] << " ";}
        // cout << endl;
        // for(long long i = 0; i < n; ++i){cout << lds[i] << " ";}
        // cout << endl;
        long long max_size = 0;
        for(long long i = 0; i < n; ++i){
            long long temp = min(lis[i], lds[i]);
            if(temp > max_size){
                max_size = temp;
            }
        }
        cout << max_size*2-1 << "\n";
        
    }
}