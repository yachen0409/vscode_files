//? NOTE: 2/10 WA, don't know why QAQ 
#include <iostream>
#include <queue>
using namespace std;
class graph{
    public:
    int vertex;
    vector<vector<int>> G;
    graph(int v):vertex(v){
        G.resize(v);
        for(int i = 0; i < v; i++){
            G[i].resize(v, 0);        
        }
    }
    void addrelation(int a, int b){
        G[a][b] = 1;
    }
    bool Bipartite(){
        int colorA[vertex];
        for (int i = 0; i < vertex; ++i)
        colorA[i] = -1;
        colorA[0] = 1; 
        queue <int> q;
        q.push(0);
        while (!q.empty()) {
            int w = q.front(); //dequeue a vertex
            q.pop();
            for (int i = 0; i < vertex; ++i) {
                if (G[w][i] && colorA[i] == -1)  {
                colorA[i] = 1 - colorA[w];
                q.push(i);
                } else if (G[w][i] && colorA[i] == colorA[w])
                return false;
            }
        }
        return true;
    }
};

int main() {
    int v, relation;
    cin >> v;
    graph G(v);
    cin >> relation;
    for(int i = 0; i < relation; i++){
        int a, b;
        cin >> a >> b;
        G.addrelation(a, b);
    }
    if (G.Bipartite())
      cout << "YES";
    else
      cout << "NO" ;
    return 0;
}