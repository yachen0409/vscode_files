#include <iostream>
#include <string>
using namespace std;

int main(){
    string s, t;
    while(cin >> s >> t){
        long long s_index = 0;
        for(long long i = 0; i < t.size(); ++i){
            if(s[s_index] == t[i]) s_index++;
            if(s_index == s.size()) break;
        }
        if(s_index == s.size()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}