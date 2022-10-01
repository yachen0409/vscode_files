#include <iostream>
#include <vector>
using namespace std;

int main(){
    string a, b;
    while(getline(cin, a)){
        getline(cin, b);
        if(a.size() == 0 || b.size() == 0) {
            cout << "0\n";
            continue;
        }
        vector<vector <long long> > lcs_table;
        lcs_table.resize(a.size()+1, vector<long long>(b.size()+1, 0));
        for(long long i = 0; i < lcs_table.size(); ++i){
            for(long long j = 0; j < lcs_table[i].size(); ++j){
                if(i==0 || j==0) continue;
                else if(a[i-1] == b[j-1]){
                    lcs_table[i][j] = lcs_table[i-1][j-1] + 1;
                }
                else{
                    lcs_table[i][j] = max(lcs_table[i-1][j], lcs_table[i][j-1]);
                }
            }
        }
        // for(long long i = 0; i < lcs_table.size(); ++i){
        //     for(long long j = 0; j < lcs_table[i].size(); ++j){
        //         cout << lcs_table[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        cout << lcs_table[a.size()][b.size()] << "\n";
    }
    return 0;
}