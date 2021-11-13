#include<iostream>
using namespace std;

void bubblesort(int length, int *arr){      //? find the BIGGEST one and swap it to the end one by one
    int temp;
    for(int i = 0; i < length-1; i++){              // for size n arr, only need n-1 times full sort
        for(int j = 0; j < length-i-1; j++){        // since every time we sort it, the last i bubbles hsa been sorted
                                                    //! without -1 will lead to an error isnce *(arr+length) = eof
            if(*(arr+j+1) < *(arr+j)){
                temp = *(arr+j+1);
                *(arr+j+1) = *(arr+j);
                *(arr+j) = temp;
            }
        }
    }
}
void selectionsort(int length ,int* arr){   //? find the SMALLEST one and swap it to the end one by one
    int min_index = 0;
    int temp;
    for(int i = 0; i < length-1; i++){
        for(int j = i+1; j < length; j++){
            if(arr[min_index] > arr[j]){
                min_index = j;
            }
        }

        temp = *(arr+i);
        *(arr+i) = arr[min_index];
        arr[min_index] = temp;
    }
}

void insertionsort1(int length, int* arr){          //? By myself, complacated
    int temp, insert_value;
    for(int i = 1; i < length; i++){
        int insert_index = -1;
        for(int j = i-1; j >= 0; j--){
            if(*(arr+j) > *(arr+i)){
                insert_index = j;
            }
        }
        // cout<< insert_index<<endl;
        if(insert_index >= 0){
            insert_value = *(arr+i);
            for(int k = i; k > insert_index ;k--){
                temp = *(arr+k);
                *(arr+k) = *(arr+k-1);
                *(arr+k-1) = temp;
            }
            arr[insert_index] = insert_value;
        }
    }
}

void insertionsort2(int length, int* arr){
    int value, j;
    for(int i = 0; i < length; i++){
        value = *(arr+i);
        j = i-1;
        while(j >= 0 && *(arr+j) > value){
            *(arr+j+1) = *(arr+j);
            j--;
        }
        *(arr+j+1) = value;
    }
}
void merge(int front_index, int back_index, int mid_index, int* arr){
    int left_arr_length = mid_index - front_index + 1,
        right_arr_length = back_index - mid_index,
        *left_arr = new int[left_arr_length],
        *right_arr = new int[right_arr_length];
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
    int a;
    int len;
    cin >> len;
    int *arr= new int[len];
    for(int i = 0; i < len; i++){
        cin>>arr[i];
    }
    
    // for(int j = 0; *(arr+j) != 0; j++){
    //     cout << *(arr+j) << endl;
    // }
    // bubblesort(len, arr);
    // selectionsort(len, arr);
    // insertionsort1(len, arr);
    // insertionsort2(len, arr);
    // mergesort(0, len-1, arr);
    quicksort(0, len-1, arr);
    cout << endl;
    for(int j = 0; j < len; j++){
        cout << *(arr+j) << endl;
    }
    return 0;
}
