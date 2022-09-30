#include <iostream>
#include <vector>
using namespace std;
int main(){
    long long num;
    cin >> num;
    while(num--){
        long long row, column, start_x, start_y, end_x, end_y;
        vector<vector<char>>graph(305, vector<char>(305, 0));
        cin >> row >> column;
        for(long long i = 0; i < row; ++i){
            for(long long j = 0; j < column; ++j){
                cin >> graph[i][j];
                if(graph[i][j] == 'S'){
                    start_x = i;
                    start_y = j;
                }
                if(graph[i][j] == 'E'){
                    end_x = i;
                    end_y = j;
                }
            }
        }
        vector<vector<vector<long long>>>dp(305, vector<vector<long long>>(305, vector<long long>(305, 0)));
        
    }
    return 0;
}