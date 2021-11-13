#include<iostream>
#include <vector>
#include <cmath>
using namespace std;
#define MAXDISTANCE 9999999
struct Node{
    int node_num, key;
    Node():node_num(0), key(0){};
    Node(int a, int b):node_num(a), key(b){};
};
class BinaryHeap{
    public:
    vector<Node> heap;
    BinaryHeap(){
        heap.resize(1);
    }
    BinaryHeap(int size){
        heap.resize(size+1);
    }
    bool IsHeapEmpty(){return (heap.size()<1);};
    void swap(struct Node &node1, struct Node &node2){
        struct Node temp = node1;
        node1 = node2;
        node2 = temp;
    }
    void minheapify(int node_index, int length){
        int left_node_index = 2*node_index;
        int right_node_index = 2*node_index+1;
        int smallest_node_index;
        if(left_node_index <= length && heap[left_node_index].key < heap[node_index].key)
            smallest_node_index = left_node_index;
        else
            smallest_node_index = node_index;

        if (right_node_index <= length && heap[right_node_index].key < heap[smallest_node_index].key)
        smallest_node_index = right_node_index;

        if(smallest_node_index != node_index){
            swap(heap[smallest_node_index], heap[node_index]);
            minheapify(smallest_node_index, length);
        }
    }
    void build(vector<int> arr){           
        for(int i = 0; i < arr.size(); i++){
            heap[i+1].node_num = i;
            heap[i+1].key = arr[i];
        }
        for(int j = (int)(heap.size()/2); j>=1; j--){
            minheapify(j, heap.size()-1);
        }
    };
    int getmin_node_num(){
        return heap[1].node_num;
    }
    int getmin_value(){
        return heap[1].key;
    }
    int extract_min_node_num(){
        int min_node_num = heap[1].node_num;

        heap[1] = heap[heap.size()-1];
        heap.erase(heap.begin() + heap.size() - 1);
        // cout<<"erased!"<<endl;
        minheapify(1, heap.size());

        return min_node_num;
    }
    int find_pos(int node){
        int pos = 0;
        for (int i = 1; i < heap.size(); i++) {
            if (heap[i].node_num == node) {
                pos = i;
            }
        }
        return pos;
    }
    int get_parent_node_index(int node){
        return floor(node/2);
    }
    void change_key(int a, int newKey){
        // cout << "nodenum="<<a<<" newkey="<<newKey<<endl;
        int index_node = find_pos(a);      
        // cout << "nodeindex in heap:"<<index_node<<endl;
        if (newKey > heap[index_node].key) {      
            return;
        }
        heap[index_node].key = newKey;            
        while (index_node > 1 && heap[get_parent_node_index(index_node)].key > heap[index_node].key) {
            swap(heap[index_node], heap[get_parent_node_index(index_node)]);
            index_node = get_parent_node_index(index_node);
        }
    }
    void print(){
        for(int i = 1; i < heap.size(); i++){
            cout<<"node_num"<<heap[i].node_num<<" value"<<heap[i].key<<endl;
        }
    }
};
class Dijkstra{
    public:
    int start_node_num, target_node_num, num_of_node, num_of_edge;
    vector<int> parent, distance; 
    vector<vector<int>> adjmatrix;
    vector<bool> visited;
    Dijkstra():start_node_num(0){};
    Dijkstra(int start, int end, int node, int edge):start_node_num(start), target_node_num(end), num_of_node(node), num_of_edge(edge){};
    void initilize(){
        distance.resize(num_of_node);
        parent.resize(num_of_node);
        adjmatrix.resize(num_of_node);
        visited.resize(num_of_node, false);
        for(int i = 0; i < num_of_node; i++){
            distance[i] = MAXDISTANCE;
        }
        distance[start_node_num] = 0;
        for(int j = 0; j < num_of_node; j++){
            parent[j] = -1;
        }
    }
    void initialmatrix(){
        adjmatrix.resize(num_of_node);
        for(int k = 0; k < num_of_node; k++){
            adjmatrix[k].resize(num_of_node, 0);
        }
    }
    void addedge(int from, int to, int cost){
        initialmatrix();
        adjmatrix[from][to] = cost;
    }
    void dijkstra(){
        initilize();
        BinaryHeap minheap(num_of_node);
        minheap.build(distance);
        while(!(minheap.IsHeapEmpty())){
            vector<int> neighbor;
            
            int current_node_value = minheap.getmin_value();
            int current_node_num = minheap.extract_min_node_num();

            for(int i = 0; i < num_of_node; i++){
                if(adjmatrix[current_node_num][i]!=0 && !visited[current_node_num]){
                    neighbor.push_back(i);
                }
            }
            for(int j = 0; j < neighbor.size(); j++){
                if(distance[current_node_num] + adjmatrix[current_node_num][neighbor[j]] < distance[neighbor[j]]){
                    parent[neighbor[j]] = current_node_num;
                    distance[neighbor[j]] = distance[current_node_num] + adjmatrix[current_node_num][neighbor[j]];
                    minheap.change_key(neighbor[j], distance[neighbor[j]]);
                }
            } 
            visited[current_node_num] = true; 
        }
    }
    void printanswer(){
        cout<<distance[target_node_num];
    }
};
int main(){
    int num_of_node, num_of_edge, start_node, target_node, begin, end, distance;
    cin >> num_of_node >> num_of_edge;
    cin >> start_node >> target_node;
    Dijkstra dijkstra(start_node, target_node, num_of_node, num_of_edge);
    for(int i = 0; i < num_of_edge; i++){
        cin >> begin >> end >> distance;
        dijkstra.addedge(begin, end, distance);
    }
    dijkstra.dijkstra();
    dijkstra.printanswer();
    return 0;
}