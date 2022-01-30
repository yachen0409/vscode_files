#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
long long f, n, m, totalnode, farmtofac, factocon, k, total = 0;
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
    cin >> f >> n >> m;
    
    totalnode = f + n*2 + m + 3;
    adjlist.resize(totalnode, map<long long, long long>());
    visited.resize(totalnode, false);
    parent.resize(totalnode, -1);
    for(long long i = 0; i < f; ++i){
        long long temp;
        cin >> temp;
        adjlist[0][i+1] = temp;
    }
    for(long long i = 0; i < n; ++i){
        long long temp;
        cin >> temp;
        adjlist[f+i+1][f+i+1+n] = temp;
    }
    for(long long i = 0; i < m; ++i){
        long long temp;
        cin >> temp;
        adjlist[f+n*2+i+1][f+n*2+m+1] = temp;
    }
    cin >> farmtofac;
    for(long long i = 0; i < farmtofac; ++i){
        long long t1, t2, weight;
        cin >> t1 >> t2 >> weight;
        if(adjlist[t1].find(f+t2)!= adjlist[t1].end()){
            adjlist[t1][f+t2] += weight;
        }
        else{
            adjlist[t1][f+t2]  = weight;
        }
    }
    cin >> factocon;
    for(long long i = 0; i < factocon; ++i){
        long long t1, t2, weight;
        cin >> t1 >> t2 >> weight;
        if(adjlist[f+n+t1].find(f+n*2+t2) != adjlist[f+n+t1].end()){
            adjlist[f+n+t1][f+n*2+t2] += weight;
        }
        else{
            adjlist[f+n+t1][f+n*2+t2] = weight;
        }
    }
    cin >> k;
    adjlist[totalnode-2][totalnode-1] = k;

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