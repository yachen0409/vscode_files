#include <iostream>
#include <vector>
// #include <map>
#include <algorithm>
using namespace std;
bool comp(pair<char, long long> lhs, pair<char, long long> rhs){
    if(lhs.second > rhs.second){
        return true;
    }
    else if(lhs.second == rhs.second){
        return lhs.first < rhs.first;
    
    }else{
        return false;
    }
}
void dfs(long long x, long long y, long long row, long long column, vector<vector<char>> &ori_map, vector<vector<bool>> &visit){
    visit[x][y] = true;
    if(x+1 < row && !visit[x+1][y] && ori_map[x+1][y] == ori_map[x][y])
        dfs(x+1, y, row, column, ori_map, visit);
    if(y+1 < column && !visit[x][y+1] && ori_map[x][y+1] == ori_map[x][y])
        dfs(x, y+1, row, column, ori_map, visit);
    if(x-1 >= 0 && !visit[x-1][y] && ori_map[x-1][y] == ori_map[x][y])
        dfs(x-1, y, row, column, ori_map, visit);
    if(y-1 >= 0 && !visit[x][y-1] && ori_map[x][y-1] == ori_map[x][y])
        dfs(x, y-1, row, column, ori_map, visit);
}
int main(){
    long long num;
    cin >> num;
    for(long long i = 0; i < num; ++i){
        long long row, column;
        vector<vector<char>> ori_map;
        vector<vector<bool>> visit;
        vector<pair<char, long long>> ans;
        cin >> row >> column;
        ori_map.resize(row, vector<char>(column, 0));
        visit.resize(row, vector<bool>(column, false));
        for(long long j = 0; j < row; ++j){
            for(long long k = 0; k < column; ++k){
                cin >> ori_map[j][k];
            }
        }
        for(long long j = 0; j < row; ++j){
            for(long long k = 0; k < column; ++k){
                if(!visit[j][k]){
                    bool exist = false;
                    for(long long l = 0; l < ans.size(); ++l){
                        if (ans[l].first == ori_map[j][k]){
                            ans[l].second += 1;
                            exist = true;
                            break;
                        }
                    }
                    if(!exist) ans.push_back(make_pair(ori_map[j][k], 1));
                    dfs(j ,k, row, column, ori_map, visit);
                }
            }
        }
        cout << "World #" << i+1 << "\n";
        sort(ans.begin(), ans.end(), comp);
        for(long long j = 0; j < ans.size(); ++j){
            cout << ans[j].first << ": " << ans[j].second << "\n";
        }
        // long long max = 0;
        // for(auto it = ans.begin(); it != ans.end(); ++it){
        //     if(it->second > max) max = it->second;
        // }

        // for(long long j = 0; j < row; ++j){
        //     for(long long k = 0; k < coldfs(j ,k, row, column, ori_map, visit);umn; ++k){
        //         cout << map[j][k];
        //     }
        // }
    }
}