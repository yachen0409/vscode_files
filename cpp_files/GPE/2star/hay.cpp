#include <iostream>
#include <map>
#include <string>

using namespace std;
int main(){
    long long num1, num2;
    cin >> num1 >> num2;
    map<string, long long> bank;
    for(long long i = 0; i < num1; ++i){
        string tempstr;
        long long tempnum;
        cin >> tempstr >> tempnum;
        bank[tempstr] = tempnum;
    }
    for(long long i = 0; i < num2; ++i){
        string word;
        long long score = 0;
        while(cin >> word){
            if(word == ".") break;
            if(bank.find(word) != bank.end()){
                score += bank[word];
            }
        }
        cout << score << "\n";
    }
}