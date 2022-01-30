#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
    int n, k;
    vector<int> list;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        list.push_back(temp);
    }
    sort(list.begin(), list.end());
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        long long x, l, sum = 0;
        cin >> x >> l;
        auto lower = lower_bound(list.begin(), list.end(), x);
        auto upper = upper_bound(list.begin(), list.end(), x*k>l ? l : x*k);
        for(int j = 1; j <= k  ; j++){//&& j*x <= l
            auto lower_inside = lower_bound(lower, upper, j*x);
            auto upper_inside = lower_bound(lower, upper, (j+1)*x);
            long long temp = j * (upper_inside - lower_inside);
            sum += temp;
        }
        cout << sum << "\n";
    }
    return 0;
}