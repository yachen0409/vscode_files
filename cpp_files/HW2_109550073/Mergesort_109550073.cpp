#include<iostream>
#include<ctime>
using namespace std;
void merge(int front_index, int back_index, int mid_index, int* arr){
    int left_arr_length = mid_index - front_index + 1,
        right_arr_length = back_index - mid_index,
        *left_arr = new int[left_arr_length+1],
        *right_arr = new int[right_arr_length+1];
    for(int i = 0; i < left_arr_length; i++){
        left_arr[i] = arr[front_index+i];
    }
    left_arr[left_arr_length] = 99999999;
    for(int j = 0; j < right_arr_length; j++){
        right_arr[j] = arr[mid_index+1+j];
    }
    right_arr[right_arr_length] = 99999999; 

    int i = 0;
    int j = 0;
    for(int k = front_index; k <= back_index; k++){
        if(left_arr[i] <= right_arr[j]){
            arr[k] = left_arr[i];
            i++;
        }
        else{
            arr[k] = right_arr[j];
            j++;
        }
    }
    
}
void mergesort(int front_index, int back_index, int* arr){  //divide and conquer
    int mid_index = (front_index + back_index) / 2;
    if(front_index < back_index){
        mergesort(front_index, mid_index, arr);
        mergesort(mid_index+1, back_index, arr);
        merge(front_index, back_index, mid_index, arr);
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
        mergesort(0, len-1, arr);
             
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