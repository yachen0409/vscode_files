#include<iostream>
#include<ctime>
using namespace std;

int partition(int front_index, int back_index, int* arr){
    int temp;
    int pivot = arr[back_index];
    int i = front_index;
    for(int j = front_index; j < back_index; j++){
        if(arr[j] < pivot){
            temp = *(arr+j);
            *(arr+j) = *(arr+i);
            *(arr+i) = temp;
            i++;
        }
    }
    temp = *(arr+i);
    *(arr+i) = *(arr+back_index);
    *(arr+back_index) = temp;
    return i;
}
void quicksort(int front_index, int back_index, int* arr){
    if(front_index < back_index){
        int pivot_index = partition(front_index, back_index, arr);
        quicksort(front_index, pivot_index-1, arr);
        quicksort(pivot_index+1, back_index, arr);
    }
}
int main(){ 
    int len;
    cin >> len;
    while(len != 0){
        clock_t tStart = clock();
        int *arr= new int[len];
        for(int i = 0; i < len; i++){
            cin>>arr[i];
        }
        quicksort(0, len-1, arr);
        
        for(int j = 0; j < len; j++){
            cout << *(arr+j) << " ";
        }
        // cout<<endl;
        // printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        cout << endl;
        cin >> len;
    }
    return 0;
}
