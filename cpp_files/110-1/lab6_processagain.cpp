#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
long long n, m, totalnode, farmtofac, factocon, k, total = 0;
vector<bool>visited;
vector<long long> parent;
vector<map<long long, long long>> adjlist;
bool bfs(long long start){
    queue<long long> queue;
    queue.push(start);
    visited[start] = true;
    while (!queue.empty()) {
        long long cur = queue.front();
        for (auto itnear = adjlist[cur].begin(); itnear!= adjlist[cur].end(); ++itnear) {
            if (!visited[itnear->first] && itnear->second != 0) {
                queue.push(itnear->first);
                visited[itnear->first] = true;
                parent[itnear->first] = cur;
            }
        }
        queue.pop();
    }
    return (visited[totalnode-1] == true);   // 若t有被visited, 表示有path從s到t
                                // 也可以用 if (predecessor[t] != -1) 判斷
}
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> n ;
    
    totalnode = n+2 ;
    adjlist.resize(totalnode, map<long long, long long>());
    visited.resize(totalnode, false);
    parent.resize(totalnode, -1);
    for(long long i = 0; i < n; ++i){
        cin >> adjlist[0][i+1];
    }
    for(long long i = 0; i < n; ++i){
        cin >> adjlist[i+1][totalnode-1];
    }
    cin >> m;
    for(long long i = 0; i < m; ++i){
        long long t1, t2, cost;
        cin >> t1 >> t2 >> cost;
        if(adjlist[t1].find(t2) == adjlist[t1].end()){
            adjlist[t1][t2] = cost;
            adjlist[t2][t1] = cost;
        }
        else{
            adjlist[t1][t2] += cost;
            adjlist[t2][t1] += cost;
        }
        
    }
    while(bfs(0)){
        long long bpoint = totalnode-1, minweight = adjlist[parent[bpoint]][bpoint];  
        while(parent[bpoint] != -1){
            if(adjlist[parent[bpoint]][bpoint] < minweight){
                minweight = adjlist[parent[bpoint]][bpoint];
            }
            bpoint = parent[bpoint];
        }
        bpoint = totalnode-1;
        while(parent[bpoint] != -1){
            adjlist[parent[bpoint]][bpoint] -= minweight;
            if(adjlist[bpoint].find(parent[bpoint]) == adjlist[bpoint].end()) 
                adjlist[bpoint][parent[bpoint]] = minweight;
            else 
                adjlist[bpoint][parent[bpoint]] += minweight;
            bpoint = parent[bpoint];
        }
        visited.clear();
        parent.clear();
        visited.resize(totalnode, false);
        parent.resize(totalnode, -1);
        total += minweight;
    }
    cout << total;
    return 0;
}