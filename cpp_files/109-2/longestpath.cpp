#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph
{
    int V;    
    list<int> *adj;  
public:
    Graph(int V);
    void addEdge(int v, int w);
    vector<int> BFS(int s); 
    bool isCyclic();
    bool isCyclicUtil(int v, bool visited[], bool *recStack);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
 
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
 
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
 
    return false;
}
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}
 
vector<int> Graph::BFS(int s)
{
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++){
        visited[i] = false;
    }
    list<int> queue;
    list<int>::iterator i;
    
    vector<int> result;
    visited[s] = true;
    queue.push_back(s);
    while(!queue.empty())
    {
        s = queue.front();
        result.push_back(s);
        queue.pop_front();

        for (i = adj[s].begin(); i != adj[s].end(); ++i){
            if (!visited[*i]){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    return result;
}

int main()
{
    int n, edge, 
        longest_path = 0;
    vector<int> result;
    cin >> n;
    Graph g(n);
    cin >> edge;
    for(int i = 0; i < edge; i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    for(int j = 0; j < n; j++){
        vector<int> temp = g.BFS(j);
        result.push_back(temp.size());
    }
    if(g.isCyclic()){
        cout << "-1";
    }
    else{
        if(result.size()>0){
            longest_path = result[0];
        }

        for(int k = 1; k < result.size(); k++){
            if(result[k] > longest_path){
                longest_path = result[k];
            }
        }
        if(longest_path == 0){
            cout << longest_path;
        }
        else{
            cout << longest_path-1;
        }
    }   
    return 0;
}
