#include <iostream>
#include <vector>
#include <algorithm>
#define MAXDISTANCE 99999999
using namespace std;

class Prim{
    public:
    int num_of_node, num_of_edge, total_cost = 0;
    vector<vector<int>> adjmatrix;
    vector<int> distance, nearvertex, queue;
    vector<bool> visited;
    Prim(int a, int b):num_of_node(a), num_of_edge(b){
        adjmatrix.resize(num_of_node);
        distance.resize(num_of_node);
        visited.resize(num_of_node, false);
        queue.resize(num_of_node);
        for(int i = 1; i < num_of_node; i++){
            distance[i] = MAXDISTANCE;
        }
        distance[0] = 0;
        for(int j = 0; j < num_of_node; j++){
            queue[j] = j;
        }
        for(int k = 0; k < num_of_node; k++){
            adjmatrix[k].resize(num_of_node, 0);
        }
    };
    void addedge(int start, int end, int dist){
        adjmatrix[start][end] = dist;
        adjmatrix[end][start] = dist;
    }
    
    void find_nearnode(int node){
        for(int i = 0; i < num_of_node; i++){
            if(adjmatrix[node][i] != 0){
                nearvertex.push_back(i);
            }
        }
    }
    void compare(int a){
        int min_dist_node_index = a;
        int temp;
        for(int i = a+1; i < queue.size(); i++){
            if(distance[queue[i]] < distance[queue[min_dist_node_index]]){
                min_dist_node_index = i;
            }
        }
        temp = queue[a];
        queue[a] = queue[min_dist_node_index];
        queue[min_dist_node_index] = temp;
    }
    void prim(int start_node){
        int current = start_node;
        nearvertex.push_back(start_node);
        for(int k = 0; k < num_of_node; k++){
            compare(k);
        }
        while(queue.size()!=0){
            vector<int>::iterator temp = queue.begin();
            queue.erase(temp);
            find_nearnode(current);
            for(int i = 0; i < nearvertex.size(); i++){
                if(!visited[nearvertex[i]]){
                    if(distance[nearvertex[i]] > adjmatrix[current][nearvertex[i]]){
                        distance[nearvertex[i]] = adjmatrix[current][nearvertex[i]];
                    }
                }
            }                    
            visited[current] = true;
            for(int k = 0; k < queue.size(); k++){
                compare(k);
            }
            current = queue[0];
            nearvertex.clear();
        }
        for(int i = 0; i < num_of_node; i++){
            total_cost += distance[i];
        }
        cout << total_cost;
    }
};

int main(){
    int num_of_node, num_of_edge;
    cin >> num_of_node >> num_of_edge;
    Prim prim(num_of_node, num_of_edge);
    for(int i = 0; i < num_of_edge; i++){
        int a, b, dist;
        cin >> a >> b >> dist;
        prim.addedge(a, b ,dist);
    }
    prim.prim(0);
    return 0;
}