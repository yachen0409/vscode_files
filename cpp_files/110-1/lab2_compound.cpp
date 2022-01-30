#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

void calculate(vector<pair<string, long long> > &element, string com, int l, int r);
bool sortbyName(pair<string, long long> a, pair<string, long long> b);

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    string compound;
    cin >> compound;
    int length = compound.size();
    vector<int> left_bracket;
    vector<int> right_bracket;

    for(int i=0; i<length; i++){
        if(compound[i] == '(' ){
            left_bracket.push_back(i);
        }else if(compound[i] == ')'){
            right_bracket.push_back(i);
        }
    }
    vector<pair<string, long long> > element;

    if(left_bracket.size() > 0){
        for(int i=0; i<left_bracket.size(); i++){
            if(i == 0){
                calculate(element, compound, left_bracket[left_bracket.size()-i-1], right_bracket[i]);
            }else{
                calculate(element, compound, left_bracket[left_bracket.size()-i-1], left_bracket[left_bracket.size()-i]);
                calculate(element, compound, right_bracket[i-1], right_bracket[i]);
            }
            int times = compound[right_bracket[i]+1] - 48;
            //cout << times << "\n";
            for(int r=0; r<element.size(); r++){
                element[r].second *= times;
            }
        }
        calculate(element, compound, 0, left_bracket[0]);
        calculate(element, compound, right_bracket[right_bracket.size()-1], length);
    }else{
        calculate(element, compound, 0, length);
    }

    sort(element.begin(), element.end(), sortbyName);

    long long counter1 = 0;
    long long counter2 = 0;    
    for(int i=0; i<element.size(); i++){
        if(element[i].first.size() == 1){
            counter1 ++;
        }else if(element[i].first.size() == 2){
            counter2 ++;
        }
    }

    cout << counter1 << "\n";
    for(int i=0; i<element.size(); i++){
        if(element[i].first.size() == 1){
            cout << element[i].first << ":" << element[i].second << "\n";
        }
    }
    cout << counter2 << "\n";
    for(int i=0; i<element.size(); i++){
        if(element[i].first.size() == 2){
            cout << element[i].first << ":" << element[i].second << "\n";
        }
    }

    return 0;
}

void calculate(vector<pair<string, long long> > &element, string com, int l, int r){
    string a,b;
    long long num = 0;
    int judge = 0;
    for(int i=l; i<r; i++){
        if('A' <= com[i] && com[i] <= 'Z'){
            i ++;
            if('a' <= com[i] && com[i] <= 'z'){
                a = com[i-1];
                b = com[i];
                a = a+b;
                i ++;
            }else{
                a = com[i-1];
            }
            while('0' <= com[i] && com[i] <= '9'){
                num = num*10 + com[i] - 48;
                i ++;
            }
            if(num == 0){
                num ++;
            }
            i --;
            for(int r=0; r<element.size(); r++){
                if(a == element[r].first){
                    element[r].second += num;
                    judge = 1;
                }
            }
            if(judge == 0){
                pair<string, long long> add;
                add.first = a;
                add.second = num;
                element.push_back(add);
            }
            num = 0;
        }
    }
}
bool sortbyName(pair<string, long long> a, pair<string, long long> b){
    return(a.first < b.first);
}