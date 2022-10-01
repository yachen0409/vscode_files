#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
    string a, b;
    while(cin >> a >> b){
        map<char, long long>a_freq, b_freq;
        for(long long i = 0; i < a.size(); ++i){
            a_freq[a[i]]++;
        }
        for(long long i = 0; i < b.size(); ++i){
            b_freq[b[i]]++;
        }
        for(map<char, long long>::iterator it_a = a_freq.begin(); it_a != a_freq.end(); ++it_a){
            map<char, long long>::iterator it_b = b_freq.find(it_a->first);
            if(it_b != b_freq.end()){
                long long times = min(it_a->second, it_b->second);
                for(long long i = 0; i < times; ++i){
                    cout << it_a->first;
                }
            }
        }
        cout << endl;
    }
    return 0;
}