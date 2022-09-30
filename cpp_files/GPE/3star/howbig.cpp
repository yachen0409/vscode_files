#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
//! https://blog.csdn.net/tengfei461807914/article/details/53143336
long long num_circle;
double ans;
vector<double>circle_radius;   //紀錄各個circle的radius
vector<double>record_x;        //紀錄每種排法的x座標

double get_horizontal_dis(long long circle1, long long circle2){  //get horizontal center of circle distance between circle1 and circle2
    double z = circle_radius[circle1] + circle_radius[circle2];
    double x = abs(circle_radius[circle1] - circle_radius[circle2]);
    return sqrt(z*z - x*x);   //畢氏定理
}
void solve(){
    // long long count = 1;
    ans = MAXFLOAT; //記得要initialize
    do{
        double temp = -1;   //記得要initialize
        record_x[1] = circle_radius[1];   //第一個x座標必定是第一個circle的radius
        for(long long i = 2; i < circle_radius.size(); ++i){   //從第二個開始
            double temp_x = circle_radius[i];
            for(long long j = 1; j < i; ++j){
                //要馬無視前一個circle直接放，要馬是(前一個circle的record_x + 與前一circle的圓心水平距離)
                //窮舉前面所有circle是因為可能會有多個circle都擠在角落不佔空間的可能
                //取max才是正確的擺法(畫圖理解)
                temp_x = max(temp_x, record_x[j] + get_horizontal_dis(i, j)); 
            }
            record_x[i] = temp_x; //丟回record_x紀錄
        }
        // cout << "no'" << count <<" permutation:\n";
        // cout << "circle_radius: ";
        // for(long long i = 1; i < circle_radius.size(); ++i){
        //     cout << circle_radius[i] << " ";
        // }
        // cout << endl;
        // cout << "record_X: ";
        // for(long long i = 1; i < record_x.size(); ++i){
        //     cout << record_x[i] << " ";
        // }
        // cout << endl << endl;
        // count++;
        for(long long i = 1; i < circle_radius.size(); ++i){
            //得到此排列下最短要多長才能容納所有circle
            //!不能直接取最後一個record_x+最後一個circle_radius
            temp = max(temp, record_x[i] + circle_radius[i]);  
        }
        ans = min(ans, temp);   //取各個排列中最小的
    }while(next_permutation(circle_radius.begin()+1, circle_radius.end()));   //!窮舉所有circle的排列
}

int main(){
    long long n;
    cin >> n;
    while(n--){
        cin >> num_circle;
        circle_radius.resize(num_circle+1); //從index 1才開始放第1個circle
        record_x.resize(num_circle+1, -1);  //從index 1才開始放第1個record
        for(long long i = 1; i < circle_radius.size(); ++i){
            cin >> circle_radius[i];
        }
        sort(circle_radius.begin()+1, circle_radius.end());
        solve();
        cout << fixed << setprecision(3) << ans << endl;

    }
    return 0;
}