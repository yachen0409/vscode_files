#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  	vector<int> v;
    vector<int> :: iterator it;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int num;
    cin >> num;
    for (int i = 0; i < num; ++i){
        char move;
        int input_num;
        cin >> move;
        switch (move)
        {
        case 'a': 
          
            cin >> input_num;
            v.push_back(input_num);
            break;
        case 'e':
            cin >> input_num;
            it = find(v.begin(), v.end(), input_num);
            v.erase(it);
            break;
        case 'r':
            reverse(v.begin(), v.end());
            break;
        case 'd':
            v.pop_back();
            break;

        case 's':
            cout << v.size() << " ";
            break;

        case 'p':
            for(int x = 0; x < v.size(); ++x){
                cout << v[x] << " ";
            }
            break;

        default:
            break;
        }
    }
    return 0;
}