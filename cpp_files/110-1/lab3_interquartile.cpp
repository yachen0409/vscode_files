#include <iostream>
#include <vector>
#include <set>
#include<iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
multiset<double>list;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    double num;
    multiset<double>::iterator iq1;
    multiset<double>::iterator iq3;
    double iqr;
    while(cin>>num){
        if(num == 0) break;
        int size = list.size();
        list.insert(num);
        
        if(size == 0){
            cout <<"0\n";
            iq1 = list.begin();
            iq3 = list.begin();
            continue;
        }
        if(size%4 == 1){
            if(num < *iq1){
                iq1--;
            }
            else if(num >= *iq3){
                iq3++;
            }
            iqr = *iq3-*iq1;
        }
        else if(size%4 == 2){
            if(num < *iq1){
                iq1--;
            }
            else if(num >= *iq3){
                iq3++;
            }
            iqr = *iq3-*iq1;
        }
        else if(size%4 == 3){
            if(num < *iq1){
                iq3--;
            }
            else if(num >= *iq3){
                iq1++;
            }
            else{
                iq1++;
                iq3--;
            }
            iqr = (*iq3+*(++iq3))/2 - (*iq1+*(--iq1))/2;
            iq1++;
            iq3--;
        }
        else if(size%4 == 0){
            if(num < *iq1){
                iq1--;
            }
            else if(num >= *iq3){
                iq3++;
            }
            iqr = (*iq3+*(++iq3))/2 - (*iq1+*(--iq1))/2;
            iq1++;
            iq3--;
        }

        if((int)iqr == iqr){
            cout << fixed << setprecision(0) << iqr << "\n";
        }
        else{
            // cout << "double!"<<endl;
            cout << fixed << setprecision(1) << iqr << "\n";
        }
    }
}