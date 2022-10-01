#include <iostream>
#include <map>
#include <vector>
using namespace std;
 
int main() {
    map <char, vector<int> > mp;
    mp['c'] = {0, 1, 1, 1, 0, 0, 1, 1, 1, 1};
    mp['d'] = {0, 1, 1, 1, 0, 0, 1, 1, 1, 0};
    mp['e'] = {0, 1, 1, 1, 0, 0, 1, 1, 0, 0};
    mp['f'] = {0, 1, 1, 1, 0, 0, 1, 0, 0, 0};
    mp['g'] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    mp['a'] = {0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    mp['b'] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    mp['C'] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    mp['D'] = {1, 1, 1, 1, 0, 0, 1, 1, 1, 0};
    mp['E'] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0};
    mp['F'] = {1, 1, 1, 1, 0, 0, 1, 0, 0, 0};
    mp['G'] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    mp['A'] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    mp['B'] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
     
    int t;
    string s;
    cin >> t;
    getline(cin, s); //clear buffer
    while (t--){
        getline(cin, s);
        int cnt[10] = {0};
        int a[10] = {0}; //status
        for (int i = 0; i < s.size(); i++){
            for (int j = 0; j < 10; j++){
                if (mp[s[i]][j]){
                    if (a[j]) continue;
                    else {
                        a[j] = 1;
                        cnt[j]++;
                    }
                } else {
                    a[j] = 0;
                }
            }
        }
        for (int i = 0; i < 10; i++){
            if(i){
                cout << " ";
            }
            cout << cnt[i] ;
        }
        cout << "\n";
    }
    return 0;
}
