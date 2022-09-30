#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    long long num = 0;
    while(true){
        long long ans_num, test_num;
        vector<string> ans, test;
        cin >> ans_num;
        if (ans_num == 0) break;
        cin.ignore();
        for(long long i = 0; i < ans_num; ++i){
            string temp;
            getline(cin, temp);
            ans.push_back(temp);
        }
        cin >> test_num;
        cin.ignore();
        for(long long i = 0; i < test_num; ++i){
            string temp;
            getline(cin, temp);
            test.push_back(temp);
        }
        num++;
        cout << "Run #" << num << ": ";
        if(ans == test){
            cout << "Accepted\n";
        }
        else{
            vector<char>ans_number, test_number;
            for(long long i = 0; i < ans.size(); ++i){
                for(long long j = 0; j < ans[i].size(); ++j){
                    if(ans[i][j] >= '0' && ans[i][j] <= '9'){
                        ans_number.push_back(ans[i][j]);
                    }
                }
            }
            for(long long i = 0; i < test.size(); ++i){
                for(long long j = 0; j < test[i].size(); ++j){
                    if(test[i][j] >= '0' && test[i][j] <= '9'){
                        test_number.push_back(test[i][j]);
                    }
                }
            }
            if(ans_number == test_number){
                cout << "Presentation Error\n";
            }
            else{
                cout << "Wrong Answer\n";
            }
        }

    }
    return 0;
}