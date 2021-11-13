#include <iostream>
#include <vector>
using namespace std;

struct good{
    int type;
    int day;
};

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int num_of_instruction;
    cin >> num_of_instruction;
    vector<good> good_list;
    for(int i = 0; i < num_of_instruction; ++i){
        int instruction, good_num, expire_day;
        cin >> instruction;
        if (instruction == 1){
            cin >> good_num >> expire_day;
            good_list.push_back({good_num, expire_day});
        }
        else if (instruction == 2){
            int smallest_index = -1;
            bool find = false;
            cin >> good_num;
            for(int i = 0; i < good_list.size(); ++i){
                if (good_list[i].type == good_num){
                    if(!find){
                        smallest_index = i;
                        find = true;
                    }
                    else{
                        if(good_list[i].day < good_list[smallest_index].day){
                            smallest_index = i;
                        }
                    }
                }
            }
            if(!find){
                cout << "-1\n";
            }
            else{
                cout << good_list[smallest_index].day << "\n";
                good_list.erase(good_list.begin()+smallest_index);
            }
        }
    }
    return 0;
}