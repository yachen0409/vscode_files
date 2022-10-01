#include <iostream>
#include <string>
#include <vector>
using namespace std;
//? https://www.youtube.com/watch?v=JoF0Z7nVSrA&ab_channel=NeetCode
vector<long long> build(string &str){
    vector<long long> lps(str.size(), 0);
    long long i = 1, prevlps = 0;
    while(i < str.size()){
        if (str[i] == str[prevlps]){
            lps[i] = prevlps + 1;
            prevlps++;
            i++;
        }
        else if(prevlps == 0){
            lps[i] = 0;
            i++;
        }
        else{
            prevlps = lps[prevlps - 1];         //! 注意！！！！上次多加了1 ＝＝
        }
    } 
    return lps;
}
int main(){
    cin.tie();
    cin.sync_with_stdio();
    string str;
    while(cin >> str){
        if (str == ".") break;
        long long ans = 1;
        if(str.size() == 1) cout << ans << "\n";
        vector<long long> lps = build(str);
        //? https://knightzone.studio/2018/09/28/3633/uva%EF%BC%9A10298%EF%BC%8Dpower-strings/
        long long repeatlength = str.size() - lps[str.size()-1];
        if(str.size() % repeatlength == 0){
            ans = str.size()/ repeatlength;
        }
        cout << ans << "\n";
        // for(long long i = 0; i < lps.size(); ++i){
        //     cout << lps[i] << " ";
        // }
        // cout << endl;
    }

    return 0;
}