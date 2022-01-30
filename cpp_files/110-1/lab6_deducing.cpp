#include <iostream>
#include <vector>
#include <queue>
#define INF 1e15
using namespace std;
long long n, m;
struct node{
    long long begin, end, weight;
    node(long long a, long long b, long long c):begin(a), end(b), weight(c){}
};
struct pqnode{
    long long endpoint, weight;
    pqnode(long long a, long long b): endpoint(a), weight(b){}
};
struct comp{
    bool operator()(pqnode* n1, pqnode* n2){
        return n1->weight > n2->weight;
    }
};

priority_queue<pqnode*, vector<pqnode*>, comp>pq1, pq2;
vector<vector<pair<long long, long long>>>adjlist, adjrever;
vector<node*>edges;
vector<long long>dis, disrever;
vector<bool>visited, visitedrever;

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> n >> m;
    dis.resize(n, INF);
    disrever.resize(n, INF);
    visited.resize(n, false);
    visitedrever.resize(n, false);
    adjlist.resize(n, vector<pair<long long, long long>>());
    adjrever.resize(n, vector<pair<long long, long long>>());
    for(long long i = 0; i < m; ++i){
        long long a, b, w;
        cin >> a >> b >> w;
        adjlist[a-1].push_back(make_pair(b-1, w));
        adjrever[b-1].push_back(make_pair(a-1, w));
        edges.push_back(new node(a-1, b-1, w));
    }

    dis[0] = 0;         //1 to n djikstra
    pq1.push(new pqnode(0, dis[0]));
    for(long long i = 0; i < n; ++i){
        long long shortestedgestartpoint = -1, shortestedge = INF;
        while(!pq1.empty() && visited[shortestedgestartpoint = pq1.top()->endpoint]){
            pq1.pop();
        }
        if(shortestedgestartpoint == -1)  break;
        visited[shortestedgestartpoint] = true;

        for(auto j = adjlist[shortestedgestartpoint].begin(); j != adjlist[shortestedgestartpoint].end(); ++j){
            long long adjendpoint = j->first, adjweight = j->second;
            if(!visited[adjendpoint] && dis[shortestedgestartpoint] + adjweight < dis[adjendpoint]){
                dis[adjendpoint] = dis[shortestedgestartpoint] + adjweight;
                pq1.push(new pqnode(adjendpoint, dis[adjendpoint]));
            }
        }
    }
    disrever[n-1] = 0;         //1 to n djikstra
    pq2.push(new pqnode(n-1, dis[n-1]));
    for(long long i = 0; i < n; ++i){
        long long shortestedgestartpoint = -1;
        while(!pq2.empty() && visitedrever[shortestedgestartpoint = pq2.top()->endpoint]){
            pq2.pop();
        }

        if(shortestedgestartpoint == -1)  break;
        visitedrever[shortestedgestartpoint] = true;

        for(auto j = adjrever[shortestedgestartpoint].begin(); j != adjrever[shortestedgestartpoint].end(); ++j){
            long long adjendpoint = j->first, adjweight = j->second;
            if(!visitedrever[adjendpoint] && disrever[shortestedgestartpoint] + adjweight < disrever[adjendpoint]){
                disrever[adjendpoint] = disrever[shortestedgestartpoint] + adjweight;
                pq2.push(new pqnode(adjendpoint, disrever[adjendpoint]));
            }
        }
    }
    for(long long i = 0; i < edges.size(); ++i){
        long long onetoa = dis[edges[i]->begin];
        long long bton = disrever[edges[i]->end];
        long long oneton = dis[n-1];
        long long diff = onetoa + bton + edges[i]->weight - oneton;
        if(diff > edges[i]->weight){
            cout << "-1\n";
        }
        else{
            cout << diff<< "\n";
        }
    }

    return 0;
}