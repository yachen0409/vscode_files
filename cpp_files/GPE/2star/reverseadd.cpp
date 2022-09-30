#include<iostream>
#include<vector>
using namespace std;
long long reverse(long long num){
    long long reverse_num = 0;
    while(num != 0){
        reverse_num = 10*reverse_num + (num % 10);
        num /= 10;
    }
    return reverse_num;
}
int main(){
    long long num;
    cin >> num;
    for(long long i = 0; i < num; ++i){
        long long temp, reverse_num = 0, times = 0;
        cin >> temp;
        while(true){
            reverse_num = reverse(temp);
            temp += reverse_num;
            // cout << "here!"<<" ";
            times++;
            if(temp== reverse(temp)){
                // times++;
                cout << times << " " << temp << "\n";
                break;
            }
            
        }
         
    }
    return 0;
}