#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    long long num;
    cin >> num;
    while(num--){
        long long num_ins, cur = 0;
        vector<string>ins;
        cin >> num_ins;
        for(long long i = 0; i < num_ins; ++i){
            string temp;
            cin >> temp;
            if(temp == "LEFT"){
                cur--;
                ins.push_back(temp);
            }
            else if(temp == "RIGHT"){
                cur++;
                ins.push_back(temp);
            }
            else if(temp == "SAME"){
                long long temp_ins;
                cin >> temp >> temp_ins;
                if(ins[temp_ins-1] == "LEFT"){
                    cur--;
                    ins.push_back(ins[temp_ins-1]);
                }
                else{
                    cur++;
                    ins.push_back(ins[temp_ins-1]);
                }
            }
        }
        cout << cur << "\n";


    }
}