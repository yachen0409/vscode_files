#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    long long int a=1000000007;
    long long int num;
    long long int sum = 1;
    vector <long long int> list;
    cin >> num;
    for(int i = 0; i < num; ++i){
        int number;
        cin >> number;
        list.push_back(number);
    }
    sort(list.begin(), list.end());
    for(int i = 0; i < list.size(); ++i){
        long long int temp;
        if(list[i] > num){
            temp = num - i;
        }
        else{
            temp = list[i] - i;
        }
        sum *= temp;
        sum = sum % a;
    }
    cout << sum;
}