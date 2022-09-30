#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
//! 關鍵：有可能有負數！
int main(){
    long long num;
    while(cin >> num && num != 0){
        vector<long long>seq;
        for(long long i = 0; i < num; ++i){
            long long temp;
            cin >> temp;
            seq.push_back(temp);
        }
        sort(seq.begin(), seq.end());
        bool has_ans = false;
        for(long long i = seq.size()-1; i >= 0; --i){   //d
            for(long long j = seq.size()-1; j >= 0; --j){   //c //!不一定 j > i，有可能前面的是負數     
                //! 只須避開c和d指向seq的同個位子即可（i != j）
                long long d_minus_c = seq[i] - seq[j];
                if(i == j) continue; 
                // if(i != j){
                //     d_minus_c = seq[i] - seq[j];
                // }
                long long a = 0, b = j-1;
                while(a < b){
                    if(seq[a] + seq[b] == d_minus_c){
                        has_ans = true;
                        break;
                    }
                    else if(seq[a] + seq[b] > d_minus_c){
                        b--;
                    }
                    else{
                        a++;
                    }
                }
                if(has_ans) break;
            }
            if(has_ans){
                cout << seq[i] << "\n";
                break;
            } 
        }   
        if(!has_ans) cout << "no solution\n";

    }
    return 0;
}