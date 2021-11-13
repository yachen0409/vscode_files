#include <iostream>
using namespace std;

int main(){
    int size, value;
    int i = 0;
    int arr1[19] = {0};
    int arr2[19] = {0};
    cin >> size;
    while(cin>>value){
        int j = value % 19;
        while(arr1[j] != 0){
            j++;
            j %= 19;
        }

        if(arr1[j] == 0){
            arr1[j] = value;
        }

        int count = 0;
        int j2 = (value% 19 + count * count)% 19;
        while(arr2[j2] != 0){
            count++;
            j2 = (value% 19 + count * count)% 19 ;
        }

        if(arr2[j2] == 0){
            arr2[j2] = value;
        }
    }

    for(int i = 0; i < 19; i++){
        cout << arr1[i]<< " ";
    }
    cout << endl;
    for(int i = 0; i < 19; i++){
        cout << arr2[i]<< " ";
    }
    
    return 0;
}