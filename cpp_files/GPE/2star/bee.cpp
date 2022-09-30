#include <iostream>
#include <vector>
using namespace std;

typedef struct point{
    int x, y;
}Point;

int main() {
    int move_x[6] = { 0, -1, -1, 0, 1, 1};
    int move_y[6] = { 1, 1, 0, -1, -1, 0};
    vector<Point> p(100001); 
    p[1].x = 0; p[1].y = 0;
    int i = 2, step = 1;
    while(i < p.size()) {
        for(int l = 0; l < 6; ++l) {
            if(l == 1){
                for(int j = 0; j < step-1 && i < p.size(); ++j, ++i){
                    p[i].x = p[i-1].x + move_x[l];
                    p[i].y = p[i-1].y + move_y[l];
                }
            }else{
                for(int j = 0; j < step && i < p.size(); ++j, ++i){
                    p[i].x = p[i-1].x + move_x[l];
                    p[i].y = p[i-1].y + move_y[l];
                }  
            }
        }
        ++step;
    }
    int n;
    while(cin >> n) {
        cout << p[n].x << " " << p[n].y << '\n';
    }
    return 0;
}