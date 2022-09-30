#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//!https://yuihuang.com/zj-e576/
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long n;
    cin >> n;
    while(n--){
        long long m;
        cin >> m;
        vector<pair<long long, long long>>lines, ans;
        long long temp1, temp2;
        while(cin >> temp1 >> temp2){
            if(temp1 == 0 and temp2 == 0) break;
            lines.push_back(make_pair(temp1, temp2));
        }
        sort(lines.begin(), lines.end());
        // for(long long i = 0; i < lines.size(); ++i){
        //     cout << lines[i].first << " " << lines[i].second << endl;
        // }
        long long left_tag = 0, right_tag = 0;
        for(long long i = 0; i < lines.size(); ++i){
            long long index = -1;
            for(long long j = i; j < lines.size(); ++j){
                if(lines[j].first > left_tag) break;
                if(lines[j].first <= left_tag && lines[j].second > right_tag){
                    right_tag = lines[j].second;
                    index = j;
                }
            }
            if(index == -1) break;
            ans.push_back(lines[index]);

            if(right_tag >= m) break;
            left_tag = right_tag;

        }
        if(right_tag < m) cout << "0\n";
        else{
            cout << ans.size() << "\n";
            for(long long i = 0; i < ans.size(); ++i){
                cout << ans[i].first << " " << ans[i].second << "\n";
            }
        }
    }
    return 0;
}
