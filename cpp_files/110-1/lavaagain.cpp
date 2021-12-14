#include <iostream>
#include <vector>
using namespace std;

vector <vector<long long>> point;
int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long N, T;
    cin >> N >> T;
    point.resize(T);
    for(long long i = 0; i < T; ++i){
        point[i].resize(N, 0);
        for(long long j = 0; j < N; ++j){
            cin >> point[i][j];
        }
    }
    for(long long i = T-2; i >= 0; --i){
        for(long long j = 0; j < N; ++j){
            if(N==1){
                point[i][j] += point[i+1][j];
            }
            else if(j-1 >= 0 && j+1 < N){   //有左右
                point[i][j]+=max(point[i+1][j-1], max(point[i+1][j], point[i+1][j+1]));
            }
            else if(j-1>=0 && j+1>=N){
                point[i][j]+=max(point[i+1][j-1], point[i+1][j]);
            }
            else{
                point[i][j]+=max(point[i+1][j], point[i+1][j+1]);
            }
        }
    }
    for(long long i = 0; i < N; ++i){
        cout << point[0][i]<< " ";
    }
    return 0;
}