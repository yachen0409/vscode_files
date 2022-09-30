#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(){
    long long num;
    
    while(cin >> num){
        if(num==0)break;
        map<string, long long> courses;
        long long max = 0, ans = 0;
        for(long long j = 0; j < num; ++j){
            vector<string> temp;
            string id;
        
            for(long long i = 0; i < 5; ++i){
                string course;
                cin >> course;
                temp.push_back(course);
            }
            sort(temp.begin(), temp.end());
            for(long long i = 0; i < 5; ++i){
                id += temp[i];
            }
            ++courses[id];
        }
        
        
        for(auto it=courses.begin(); it!=courses.end(); ++it){
            if (it->second > max){
                max = it->second;
            }
        }
        for(auto it=courses.begin(); it!=courses.end(); ++it){
            if (it->second == max){
                ans++;
            }
        }
        cout << ans*max << "\n";
    }
    return 0;
}