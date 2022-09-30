#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<long long>build_lps(string str){ //跟power string一樣
    long long prelps = 0, i = 1;
    vector<long long>lps(str.size(), 0);
    while(i < str.size()){
        if(str[prelps] == str[i]){
            lps[i] = prelps + 1;
            i++;
            prelps++;
        }
        else if(prelps == 0){
            lps[i] = 0;
            i++;
        }
        else{
            prelps = lps[prelps - 1];
        }
    }
    return lps;
}
long long kmp(string str, string reverstr){
    long long str_pos = 0;
    long long reverstr_pos = 0;
    vector<long long>lps = build_lps(reverstr);

    while(str_pos < str.size()){
        // cout << "line "<<str_pos << " " << reverstr_pos << endl;
        if(reverstr[reverstr_pos] == str[str_pos]){
            str_pos++;
            reverstr_pos++;
        }
        else if(reverstr_pos == 0){
            str_pos++;
        }
        else{
            reverstr_pos = lps[reverstr_pos - 1];
        }
        // cout << reverstr_pos <<" " <<  reverstr.size() << endl;
        if(reverstr_pos == reverstr.size()){ //complete match
            // cout << str_pos-reverstr_pos << " ";
            break;
            // reverstr_pos = lps[reverstr_pos - 1];
        }   
    }
    // cout << reverstr_pos << endl;
    return reverstr_pos;
}
int main(){
    string str;
    while(cin >> str){
        string reverstr(str);
        reverse(reverstr.begin(), reverstr.end());
        long long cut_index = kmp(str, reverstr);
        cout << str;
        for(long long i = cut_index; i < reverstr.size(); ++i){
            cout << reverstr[i];
        }
        cout << "\n";
        // cout << cut_index << endl;
        
        // for(long long i = 0; i < lps.size(); ++i){
        //     cout << lps[i] << " ";
        // }
        // cout << endl;
        // cout << str << " " << reverstr << endl;       

    }
    return 0;
}