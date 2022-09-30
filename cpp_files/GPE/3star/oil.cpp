#include <iostream>
#include <vector>
using namespace std;
vector<vector<char>>map;
vector<vector<bool>>visited;
long long row, column;
void check(long long i, long long j){
    if(map[i][j] == '@' && !visited[i][j]){
        // cout << i <<" "<< j << endl;
        visited[i][j] = true;
        if(i-1 >= 0) check(i-1, j ); //注意邊界問題！
        if(i+1 < row) check(i+1, j );
        if(j-1 >= 0) check(i, j-1 );
        if(j+1 < column) check(i, j+1 );
        if(i+1 < row && j-1 >= 0)check(i+1, j-1 );
        if(i+1 < row && j+1 < column)check(i+1, j+1 );
        if(i-1 >= 0 && j-1 >= 0)check(i-1, j-1 );
        if(i-1 >= 0 && j+1 < column)check(i-1, j+1 );
    }
}
int main(){
    while(cin >> row >> column){
        if(row == column && row == 0) break;
        map.clear(); //沒有會錯！
        visited.clear();
        map.resize(row, vector<char>(column, '0'));
        visited.resize(row, vector<bool>(column, false));
        long long count = 0;
        for(long long i = 0; i < row; ++i){
            for(long long j = 0; j < column; ++j){
                cin >> map[i][j];
            }
        }
        for(long long i = 0; i < row; ++i){
            for(long long j = 0; j < column; ++j){
                if(map[i][j] == '@' && !visited[i][j]){
                    ++count;
                    // cout << "find " << i << " " << j <<endl;
                    check(i, j);
                }
            }
        }
        cout << count << "\n";
        // for(long long i = 0; i < row; ++i){
        //     for(long long j = 0; j < column; ++j){
        //         cout << map[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    return 0;
}