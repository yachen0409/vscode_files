#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool comp(string a, string b){
    return a+b > b+a;
}

int main(){
    string s;
    vector<string> s_vec;
    int n; 
    while(cin >> n){
        if(n == 0) break;
        s_vec.clear();
        while(n--){
            cin >> s;
            s_vec.push_back(s);
        }
        sort(s_vec.begin(), s_vec.end(), comp);
        for(vector<string>::iterator it = s_vec.begin(); it != s_vec.end(); ++it){
            cout << *it;
        }
        cout << endl;        
    }

    return 0;
}