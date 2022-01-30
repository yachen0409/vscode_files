#include <iostream>
#include <vector>
#include <algorithm>
#define MODNUM 1000000007
using namespace std;
struct node{
    long long node1, node2, edge;
    node(long long a, long long b, long long c): node1(a), node2(b), edge(c){}
};
bool cmp(node* a, node* b){
    return a->edge < b->edge;
}

vector<node*>tree;
vector<node*>mst;

vector<vector<long long>>mstadj;
vector<long long> visited;
vector<long long> numofnode;

vector<long long> disjoint;

void dfs(long long v){
    visited[v] = 1;
    for(auto a = mstadj[v].begin(); a!= mstadj[v].end(); ++a){
        if(!visited[*a]){
            dfs(*a);
            numofnode[v]+=numofnode[*a];
        }
    }
    numofnode[v]+=1;
}
long long find(long long x) {return x == disjoint[x] ? x : (disjoint[x] = find(disjoint[x]));}
void merge(long long x, long long y) {disjoint[find(x)] = find(y);}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, M, broadcastcost = 0;
    
    cin >> N >> M;
    disjoint.resize(N+1);
    mstadj.resize(N+1);
    visited.resize(N+1, 0); //not visited
    numofnode.resize(N+1, 0);
    for(long long i = 0; i < M; ++i){
        long long node1, node2, dis;
        cin >> node1 >> node2 >> dis;
        node* temp = new node(node1, node2, dis);
        tree.push_back(temp);
    }
    for (long long i=1; i<N+1; ++i) disjoint[i] = i;

    sort(tree.begin(), tree.end(), cmp);
    
    long long i = 0, totalcost = 0;
    for (long long j = 0; j < tree.size(); ++j)
    {
        if (find(tree[j]->node1) == find(tree[j]->node2)) continue;
        merge(tree[j]->node1, tree[j]->node2);
        mst.push_back(tree[j]);
        mstadj[tree[j]->node1].push_back(tree[j]->node2);
        mstadj[tree[j]->node2].push_back(tree[j]->node1);
        totalcost+=tree[j]->edge;
        totalcost%=MODNUM;
        i++;    // num of vertex mst has
    }
    if(i != N-1){
        cout << "-1";
    }
    else{
        totalcost*=2;
        cout << totalcost%MODNUM <<" ";
        dfs(1);
        for(long long i = 0; i < mst.size(); ++i){
            node* cur = mst[i];
            long long nodenumaside = min(numofnode[cur->node1], numofnode[cur->node2]);
            long long time = nodenumaside*(N-nodenumaside)%MODNUM;
            broadcastcost+=(time * cur->edge * 2);
            broadcastcost%=MODNUM;
        }
        cout << broadcastcost;
    }
    return 0;
}