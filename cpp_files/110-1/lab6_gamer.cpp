#include <iostream>
#include <vector>
#define INF 10000000000005
using namespace std;
long long m, n;
vector<vector<long long>>adjmatrix;
vector<long long>disjoint;
int main(){
    cin >> n >> m;
    adjmatrix.resize(n, vector<long long>(n));
    for(long long i = 0; i < n; ++i){
        for(long long j = 0; j < n; ++j){
            if(i == j)  adjmatrix[i][j] = 0;
            else    adjmatrix[i][j] = INF;
        }
    }

    for(long long i = 0; i < m; ++i){
        long long a, b, w;
        cin >> a >> b >> w;
        adjmatrix[a][b] = min(w, adjmatrix[a][b]);
    }
    cout << endl;
    for (int i = 0; i < n; i++){             
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                if (adjmatrix[j][k] > adjmatrix[j][i] + adjmatrix[i][k]){
                    adjmatrix[j][k] = adjmatrix[j][i] + adjmatrix[i][k];
                }
            }
        }
    }
    long long times;
    cin >> times;
    for(long long i = 0; i < times; ++i){
        long long temp1, temp2;
        cin >> temp1 >> temp2;
        if(adjmatrix[temp1][temp2] != INF)
            cout << adjmatrix[temp1][temp2] << "\n";
        else
            cout << "-1\n";
    }

}