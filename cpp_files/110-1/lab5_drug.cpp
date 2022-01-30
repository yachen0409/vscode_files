#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

vector<int>policedistance, mydistance;
void myDFS(queue<int> q, vector<vector<int>>adj){
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int i : adj[cur]){
            if(mydistance[i] == -1){
                mydistance[i] = mydistance[cur] + 1;
                q.push(i);
            }
        }
    }
}
void policeDFS(queue<int> q, vector<vector<int>>adj){
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int i : adj[cur]){
            if(policedistance[i] == -1){
                policedistance[i] = policedistance[cur] + 1;
                q.push(i);
            }
        }
    }
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int N, M, S, T;
    
    cin >> T;
    for(int i = 0; i < T; ++i){
        cin >> N >> M >> S;
        int policenum, destnum;
        bool alive = false;
        vector<int> destpos;
        vector<vector<int>> adjlist(N);
        queue<int> policeq, myq;
        adjlist.resize(N);
        policedistance.resize(N, -1);
        mydistance.resize(N, -1);
        destpos.resize(N, 0);

        for(int j = 0; j < M; ++j){
            int node1, node2;
            cin >> node1 >> node2;
            adjlist[node1-1].push_back(node2-1);
            adjlist[node2-1].push_back(node1-1);    //bidirectional
        }

        cin >> policenum;
        for(int j = 0; j < policenum; ++j){
            int temp;
            cin >> temp;
            policeq.push(temp-1);
            policedistance[temp-1] = 0;
        }
        policeDFS(policeq, adjlist);    //do MUL police DFS

        cin >> destnum;
        for(int j = 0; j < destnum; ++j){   //mark drug house
            int temp;
            cin >> temp;
            destpos[temp-1] = 1;
        }
        mydistance[S-1] = 0;    //do MYposition DFS
        myq.push(S-1);
        myDFS(myq, adjlist);

        for(int i = 0; i < N; ++i){
            if(destpos[i] == 1 && mydistance[i] < policedistance[i]){   //for judge whether the dealer can escape
                alive = true;
                break;
            }
        }
        if(alive) cout << "Yes\n";
        else cout << "No\n";
        policedistance.clear();
        mydistance.clear();
    }
    return 0;
}