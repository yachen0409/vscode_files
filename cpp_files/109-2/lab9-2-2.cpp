#include<iostream>
#include<vector>
using namespace std;
class Heap{
    private:
    int *heap, capacity, size;
    
    public:
    Heap(){
        this->capacity = 10;
        this->size = 0;
        heap = new int[capacity];
    };
    int getsize(){
        return size;
    }
    void add(int value){
        if (size == capacity){
            capacity*=2;
            int *newheap = new int[capacity];
            for(int i = 0; i<this->size; i++){
                newheap[i] = heap[i];
            }
            delete[] heap;
            heap = newheap;
        }
        
        heap[size] = value;
        int index = size;
        while(heap[index] < heap[(index-1)/2] && index>=0){
            int temp = heap[index];
            heap[index] = heap[(index-1)/2];
            heap[(index-1)/2] = temp;
            index = (index-1)/2;
        }
        size++;
    }
    int out(){
        int index = 0;
        int changeIndex = 0;
        int num = heap[0];
        heap[0] = heap[size-1];
        size--;
        while(index < size){

            if(index*2+1 >= size){
                break;
            }
            if(index*2+2>=size){
                changeIndex = index*2+1;
            }
            else if(heap[index*2+1]>heap[index*2+2]){
                changeIndex = index*2+2;
            }
            else if (heap[index*2+1]<=heap[index*2+2]){
                changeIndex = index*2+1;
            }

            if (heap[changeIndex]>heap[index]){
                break;
            }
            int temp = heap[index];
            heap[index] = heap[changeIndex];
            heap[changeIndex] = temp;
            index = changeIndex;
        }
        return num;
    }
};
int main(){
    int num;
    while(cin >> num){
        Heap heap;
        int sum = 0;
        if (num == 0){
            break;
        }
        int a;
        for(int i = 0; i < num; i++){
            cin>>a;
            heap.add(a);
        }
        while(heap.getsize()!=1){
            int temp;
            temp = heap.out();
            temp += heap.out();
            sum += temp;
            heap.add(temp);
            // cout << "[" << temp << "]" << endl;
        }
        cout << sum << endl;

    }
    return 0;
}