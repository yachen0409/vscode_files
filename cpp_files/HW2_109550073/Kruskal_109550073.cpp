#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct edge{
    int begin, end, weight;
    edge(){};
    edge(int a, int b, int c):begin(a), end(b), weight(c){};
};
bool compareWeight(struct edge a, struct edge b){
    return (a.weight < b.weight);
}
class Graph{
    public:
    int num_of_vertex, num_of_edge, total_cost = 0;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> set;
    Graph(){
        num_of_vertex = 0;
    }
    Graph(int a, int b){
        num_of_vertex = a;
        num_of_edge = b;
        adjMatrix.resize(num_of_vertex);
        for(int b = 0; b < num_of_vertex; b++){
            adjMatrix[b].resize(num_of_vertex);
        }
        set.resize(num_of_vertex);
        for(int c = 0; c < num_of_vertex; c++){
            set[c].push_back(c);
        }
    }
    
    void add(int begin, int end, int dist){
        adjMatrix[begin][end] = dist;
        adjMatrix[end][begin] = dist;
    }

    void edgesort(vector<struct edge> &x){
        for(int a = 0; a < num_of_vertex; a++){
            for(int b = 0; b < num_of_vertex; b++){
                if(adjMatrix[a][b] != 0){
                    x.push_back(edge(a, b, adjMatrix[a][b]));
                }
            }
        }
        sort(x.begin(), x.end(), compareWeight);
    }
    
    bool isSameSet(int a, int b){
        int a_index, b_index;
        for(int i = 0; i < set.size(); i++){
            for(int j = 0; j < set[i].size(); j++){
                if(set[i][j] == a){
                    a_index = i;
                }
                else if(set[i][j] == b){
                    b_index = i;
                }
            }
        }
        if(a_index == b_index){
            return true;
        }
        else{
            return false;
        }
    }
    int getindex(int a){
        int a_index;
        for(int i = 0; i < set.size(); i++){
            for(int j = 0; j < set[i].size(); j++){
                if(set[i][j] == a){
                    a_index = i;
                }
            }
        }   
        return a_index;
    }
    void kruckal(){
        vector<struct edge> increaseWeight;
        edgesort(increaseWeight);
        for(int i = 0; i < num_of_edge; i++){
            int start_node = increaseWeight[i].begin,
                end_node = increaseWeight[i].end,
                cost = increaseWeight[i].weight,
                start_index,
                end_index;
            if(!isSameSet(start_node, end_node)){
                start_index = getindex(start_node);
                end_index = getindex(end_node);
                for(int j = 0; j < set[end_index].size(); j++){
                    set[start_index].push_back(set[end_index][j]);
                }
                set[end_index].clear();
                total_cost += cost;
            }   
        }
        cout << total_cost;
    }
};


int main(){
    int num_of_node, num_of_edge;
    cin >> num_of_node >> num_of_edge;
    Graph g(num_of_node, num_of_edge);
    for(int i = 0; i < num_of_edge; i++){
        int a, b, dist;
        cin >> a >> b >> dist;
        g.add(a, b ,dist);
    }
    g.kruckal();
    return 0;
}