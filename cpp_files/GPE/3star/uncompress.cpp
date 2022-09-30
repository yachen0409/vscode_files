#include<iostream>
#include<vector>
using namespace std;

int main(){
    string str, out = "";
    long long num = 0;
    vector<string>wordbank;
    while(getline(cin, str)){
        if(str == "0") break;
        str += "\n";
        for(long long i = 0; i < str.size(); ++i){
            if(isalpha(str[i])){
                out += str[i];
            }
            else if(isdigit(str[i])){
                num = num*10 + (str[i]-'0');
            }
            else{
                if(out != ""){
                    cout << out;
                    if(wordbank.empty()){
                       wordbank.push_back(out); 
                    }
                    else{
                        wordbank.push_back(wordbank.back());
                        for(long long j = wordbank.size()-2; j > 0; --j){
                            wordbank[j] = wordbank[j-1];
                        }
                        wordbank[0] = out;
                    }
                    out = "";
                }
                if(num != 0){
                    // cout<<"bank:"<<endl;
                    // for(long long j = 0; j < wordbank.size(); ++j){
                        // cout << wordbank[j] << " ";
                    // }
                    // cout << endl;
                    cout << wordbank[num-1];
                    string temp = wordbank[num-1];
                    for(long long j = num-1; j > 0; --j){
                        wordbank[j] = wordbank[j-1];
                    }
                    wordbank[0] = temp;
                    num = 0;
                }
                cout << str[i];
            }
        }
    }
    return 0;
}