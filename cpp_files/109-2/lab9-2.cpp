#include<iostream>
#include<vector>
using namespace std;

class Node{
    public:
    int key;
    Node():key(0){};
    Node(int a): key(a){};
};

class Heap{
    public:
    vector<Node> heap;
    Heap(){
        heap.resize(1);
    }
    Heap(int n){
        heap.resize(n+1);
    }
    void swap(class Node &p1, class Node &p2){
        Node temp = p1;
        temp = p1;
        p1 = p2;
        p2 = temp;
    }

    void minHeapity(int node, int length){
        int left = 2*node,          // 取得left child
            right = 2*node + 1,     // 取得right child
            smallest;               // smallest用來記錄包含root與child, 三者之中Key最小的node

        if (left <= length && heap[left].key < heap[node].key)
            smallest = left;
        else
            smallest = node;

        if (right <= length && heap[right].key < heap[smallest].key)
            smallest = right;

        if (smallest != node) {                 // 如果目前node的Key不是三者中的最小
            swap(heap[smallest], heap[node]);   // 就調換node與三者中Key最小的node之位置
            minHeapity(smallest, length);       // 調整新的subtree成Min Heap
        }
    }
    void buildMinHeap(vector<int> array){
        // 將array[]的資料放進 heap之矩陣中, 並預留 heap[0] 不做使用
        for (int i = 0; i < array.size(); i++) {     
            heap[i + 1].key = array[i];              // 把array[]的數值視為key
        }
        for (int i = (int)heap.size()/2; i >= 1 ; i--) {
            minHeapity(i, (int)heap.size()-1);     // length要減一, 因為heap從從1開始存放資料
        }
    }
    

};

int main(){
    return 0;
}