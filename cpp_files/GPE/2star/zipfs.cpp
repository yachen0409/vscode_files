#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;
int main(){
    long long num;
    bool newline = false;
    while(cin >> num){
        if(newline) cout << "\n";
        newline = true;
        string word;
        map <string, long long> word_times;
        stringstream wordbank;
        while(cin >> word){
            if (word == "EndOfText") break;
            for(long long i = 0; i < word.size(); ++i){
                if(isupper(word[i]) || islower(word[i])){
                    word[i] = tolower(word[i]);
                }
                else{
                    word[i] = ' ';
                }
            }
            if(word != " "){
                wordbank << word << " "; // remember the space after each input word!
            }
            
        }
        while(wordbank >> word){
            word_times[word]++;
        }
        
        bool noans = true;
        for(map <string, long long>::iterator it = word_times.begin(); it != word_times.end(); ++it){
            if(it->second == num && it->first.size() > 0){
                cout << it->first << endl;
                noans = false;
            }
        }
        if(noans){
            cout << "There is no such word.\n";
        }
    }
    
    return 0;
}