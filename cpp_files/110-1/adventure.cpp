#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
 
void threeSum(vector<int> &num, int sum) 
    {
        vector<vector<int> > result;
        int ans = 0;
        sort(num.begin(), num.end());

        for (int i = 0;i < num.size() - 2; i++)
        {
            if (i > 0 && num[i] == num[i - 1])  
                continue;
            int j = i + 1;
            int k = num.size() - 1;
            while (j < k)
            {
                ans = num[i] + num[j] + num[k];
                if (ans == sum)
                {
                    result.push_back({num[i], num[j], num[k]});
                    ++j;
                    while (j < num.size() && num[j] == num[j - 1])
                        ++j;
                    --k;
                    while (k >= 0 && num[k] == num[k + 1])
                        --k;
                }
                else if (ans > sum) 
                    --k;
                else 
                    ++j;
            }
        }
        if(result.size() == 0){
            cout<<"FeiDooDoo_Zuo_Wei_Men\n";
        }
        else{
            cout << result.size() << "\n";
        }
    }
 
/* Driver program to test above function */
int main(){   
    vector<int> list;
    int sum, num=0;
    cin >> num >> sum;
    for(int i = 0; i < num; ++i){
        int number;
        cin >> number;
        list.push_back(number);
    }
    threeSum(list, sum);
    return 0;
}