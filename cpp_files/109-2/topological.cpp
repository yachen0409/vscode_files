//? NOTE: only complete the part that judge cyclic 
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int V; 
  
    // Pointer to an array containing adjacency listsList
    list<int>* adj;
  
    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
  
public:
    Graph(int V); // Constructor
  
    // function to add an edge to graph
    void addEdge(int v, int w);
  
    // prints a Topological Sort of the complete graph
    stack<int> topologicalSort();
    bool isCyclicUtil(int v, bool visited[], bool *recStack);
    bool isCyclic();
};
  
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
  
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
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
// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited.
    visited[v] = true;
  
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);
  
    // Push current vertex to stack which stores result
    Stack.push(v);
}
  
// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
stack<int> Graph::topologicalSort()
{
    stack<int> Stack;
  
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
  
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);
  
    // Print contents of stack
    return Stack;
}
  
// Driver program to test above functions
int main()
{
    int n, edge;
    cin >> n;

    // Create a graph given in the above diagram
    Graph g(n);
    // 
    cin >> edge;
    for(int i = 0; i < edge; i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    if(g.isCyclic()){
        cout << "-1" << endl;
    }
    else{
        if(edge == 0){
            cout << "0" << endl;
        }
        else{
            stack<int> temp = g.topologicalSort();
            cout << temp.size()-1;
        }
    }
    return 0;
}