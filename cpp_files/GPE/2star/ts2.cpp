#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> build_table(string s){
    
    vector<int> result(s.length(), 0);
    int i = 1; //index of partial string
    int j = 0; //index of whole string
    while(i < s.length()){
        if(s[i] == s[j]){
            i++;
            j++;
            result[i-1] = j;
        }else if(j <= 0){
            i++;
            result[i-1] = 0;        
        }else{
            j = result[j-1];
        }
    }
    return result;
}
int main(){
    //application of kmp algorithm
    string s;
    while(cin >> s){
        if(s == ".") break;
        int ans = 1;
        if(s.length() == 1) cout << ans << '\n';
        else{
            vector<int> failure = build_table(s);
            cout << "vector failure: ";
            for (int i = 0; i < failure.size(); ++i){
                cout << failure[i] << " ";
            }
            cout << endl;
            int target = failure.size()/2;
            int test = 0;
            for(int i = failure.size()-1; i >= 0; --i){
                if(failure[i] == 0){
                    test = i+1;
                    break;
                }
            }
            if(test > target) cout << ans << '\n';
            else if(s.length() % test != 0) cout << ans << '\n';
            else cout << (s.length() / test) << '\n';          
        }

    }
    return 0;
}