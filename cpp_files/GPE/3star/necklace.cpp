#include <iostream>
#include <vector>
#include <cmath>
//! double比較不能直接比
using namespace std;
int main(){
    cin.tie();
    cin.sync_with_stdio();
    double a, b;
    while(cin >> a >> b){
        if(a == b && a == 0){
            break;
        }
        vector<pair<int, double>>ans;
        double max = 0.0;
        int max_num = 0;
        bool max_is_repeat = false;
        for(int i = 1; i <= a; ++i){
            double temp = a / i;
            if(temp > b){
                double value = 0.3 * sqrt((temp-b)) * i;
                // cout << max << " " << value << endl;
                if(value > max) max = value;
                ans.push_back(make_pair(i, value));
            }
        } 
        int repeatnum = 0;
        for(int i = 0; i < ans.size(); ++i){
            // cout << ans[i].first << " " << ans[i].second << endl;
            //!NOTICE: 沒有to_string()會錯==，因為double比較有精度的問題
            if(to_string(ans[i].second) == to_string(max)){     
                repeatnum++;
                max_num = ans[i].first;
            } 
            if(repeatnum == 2){
                max_is_repeat = true;
                break;
            }
        }
        // cout << "max num" << max_num << endl;
        // cout << "ans size:" << ans.size() << endl;
        if(max_is_repeat || ans.size() == 0){
            cout << "0\n";
        }
        else{
            cout << max_num << "\n";
        }
;
    }
    return 0;
}
