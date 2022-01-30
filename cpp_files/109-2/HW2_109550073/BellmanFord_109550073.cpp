#include<iostream>
#include <vector>
#include <cmath>
using namespace std;
#define MAXDISTANCE 9999999

class Bellman{
    public:
    int start_node_num, target_node_num, num_of_node, num_of_edge;
    vector<int> parent, distance; 
    vector<vector<int>> adjmatrix;
    Bellman(){};
    Bellman(int start, int end, int node, int edge):start_node_num(start), target_node_num(end), num_of_node(node), num_of_edge(edge){};
    void initilize(){
        distance.resize(num_of_node);
        parent.resize(num_of_node);
        adjmatrix.resize(num_of_node);
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
    bool negetive_loop(){
        for(int j = 0; j < num_of_node; j++){
            vector<int> neighbor;
            for(int a = 0; a < num_of_node; a++){
                if(adjmatrix[j][a]!=0){
                    neighbor.push_back(a);
                }
            }
            for(int k = 0; k < neighbor.size(); k++){
                if(distance[j]+adjmatrix[j][neighbor[k]]<distance[neighbor[k]]){
                    return true;
                }
            }
        }
        return false;
    }
    void bellman_ford(){
        initilize(); 
        vector<vector<int>> neighbor; 
        neighbor.resize(num_of_node);
        for(int i = 0; i < num_of_node-1; i++){
            for(int j = 0; j < num_of_node; j++){
                if(i == 0){
                    for(int a = 0; a < num_of_node; a++){
                        if(adjmatrix[j][a]!=0){
                            neighbor[j].push_back(a);
                        }
                    }
                }
                for(int k = 0; k < neighbor[j].size(); k++){
                    if(distance[j]+adjmatrix[j][neighbor[j][k]]<distance[neighbor[j][k]]){
                        distance[neighbor[j][k]] = distance[j]+adjmatrix[j][neighbor[j][k]];
                        parent[neighbor[j][k]] = j;
                    }
                }
            }
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
    Bellman bellman(start_node, target_node, num_of_node, num_of_edge);
    for(int i = 0; i < num_of_edge; i++){
        cin >> begin >> end >> distance;
        bellman.addedge(begin, end, distance);
    }
    bellman.bellman_ford();
    if(bellman.negetive_loop()){
        cout << "Negative loop detected!"<<endl;
    }
    else{
        bellman.printanswer();
    }
    
    return 0;
}