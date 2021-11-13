#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
class student{
    public:
    string name, mark;
    vector<int> point;
    student(string na, int a, int b, int c, int d){
        name = na;
        point.push_back(a);
        point.push_back(b);
        point.push_back(c);
        point.push_back(d);
    }
};

bool cmp(const student& lhs, const student& rhs){
    int sta_0, sta_1, sta_2, sta_3;
    for(int i = 0; i < 4; ++i){
        if(lhs.mark[i] == 'G'){
            if(i == 0){
                sta_0 = 0;
            }
            else if(i == 1){
                sta_1 = 0;
            }
            else if(i == 2){
                sta_2 = 0;
            }
            else if(i == 3){
                sta_3 = 0;
            }
        }
        else if(lhs.mark[i] == 'H'){
            if(i == 0){
                sta_0 = 1;
            }
            else if(i == 1){
                sta_1 = 1;
            }
            else if(i == 2){
                sta_2 = 1;
            }
            else if(i == 3){
                sta_3 = 1;
            }
        }
        else if(lhs.mark[i] == 'R'){
            if(i == 0){
                sta_0 = 2;
            }
            else if(i == 1){
                sta_1 = 2;
            }
            else if(i == 2){
                sta_2 = 2;
            }
            else if(i == 3){
                sta_3 = 2;
            }
        }
        else if(lhs.mark[i] == 'S'){
            if(i == 0){
                sta_0 = 3;
            }
            else if(i == 1){
                sta_1 = 3;
            }
            else if(i == 2){
                sta_2 = 3;
            }
            else if(i == 3){
                sta_3 = 3;
            }
        }
    }
    if (lhs.point[sta_0] != rhs.point[sta_0]){
        return lhs.point[sta_0] > rhs.point[sta_0];
    }    
    else if (lhs.point[sta_1] != rhs.point[sta_1]){
        return lhs.point[sta_1] > rhs.point[sta_1];
    }
    else if (lhs.point[sta_2] != rhs.point[sta_2]){
        return lhs.point[sta_2] > rhs.point[sta_2];
    }
    else if (lhs.point[sta_3] != rhs.point[sta_3]){
        return lhs.point[sta_3] > rhs.point[sta_3];
    }
    else if (lhs.name != rhs.name){
        return lhs.name < rhs.name;
    }
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int n;
    vector <vector<student>> college;
    vector <string> mark_stndard;
    college.resize(4);

    cin >> n;
    for(int i = 0; i < 4; ++i){
        string temp_mark;
        cin >> temp_mark;
        mark_stndard.push_back(temp_mark);     
    }
    for(int i = 0; i < n; ++i){
        string temp_name;
        int a, b, c, d;
        cin >> temp_name >> a >> b >> c >> d;
        student temp_class(temp_name, a, b, c, d);
        if(max_element(temp_class.point.begin(), temp_class.point.end()) - temp_class.point.begin() == 0){
            temp_class.mark = mark_stndard[0];
            college[0].push_back(temp_class);
        }
        else if(max_element(temp_class.point.begin(), temp_class.point.end()) - temp_class.point.begin() == 1){
            temp_class.mark = mark_stndard[1];
            college[1].push_back(temp_class);
        }
        else if(max_element(temp_class.point.begin(), temp_class.point.end()) - temp_class.point.begin() == 2){
            temp_class.mark = mark_stndard[2];
            college[2].push_back(temp_class);
        }
        else if(max_element(temp_class.point.begin(), temp_class.point.end()) - temp_class.point.begin() == 3){
            temp_class.mark = mark_stndard[3];
            college[3].push_back(temp_class);
        }
    }
    for(int i = 0; i < 4; ++i){
       sort(college[i].begin(), college[i].end(), cmp);
    }
    for(int i = 0; i < 4; ++i){
        if(i == 0){
            cout << "GRYFFINDOR: ";
        }
        else if(i == 1){
            cout << "HUFFLEPUFF: ";
        }
        else if(i == 2){
            cout << "RAVENCLAW: ";
        }
        else if(i == 3){
            cout << "SLYTHERIN: ";
        }
        if(college[i].size() == 0){
            cout << "NO NEW STUDENTS\n";
            continue;
        }
        cout << "\n";
        for(int j = 0; j < college[i].size(); ++j){
            cout << college[i][j].name << "\n";
        }
    }
    return 0;
}