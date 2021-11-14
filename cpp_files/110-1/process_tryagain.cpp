//方法對但有bug
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long q, N, C, time = 0;
    vector<long long>tasklist, processor;
    set<pair<long long, long long>> position;
    cin >> N >> C >> q;
    tasklist.resize(q);
    processor.resize(C, 0);
    for(long long i = 0; i < q; ++i){
        cin >> tasklist[i];
    }
    for(long long j = 0; j < q; ++j){
        long long task = tasklist[j];
        long long farestprocessornum;
        // cout <<"task = "<< task << endl;
        auto itfind0 = find(processor.begin(), processor.end(), 0);
        auto itfindtask = find(processor.begin(), processor.end(), task);
        // cout <<"itfind0=" << *itfind0 <<endl;
        // cout <<"itfindtask=" << *itfindtask <<endl;
        if(itfind0 != processor.end()){ //init_process exist
            if(itfindtask == processor.end()){ //no task in processor now
                // cout<<"no task in processor now"<<endl;
                *itfind0 = task;
                time++;
            }
        }
        else{
            if(itfindtask == processor.end()){
                // cout << "in !"<<endl;
                position.clear();
                for(long long k = 0; k < C; ++k){
                    vector<long long>:: iterator ittempfind = find(tasklist.begin()+j+1, tasklist.end(), processor[k]);
                    if(ittempfind == tasklist.end()){
                        farestprocessornum = k;
                        position.clear();
                        break;
                    }
                    else{
                        position.insert({ittempfind-tasklist.begin(), k});
                    }
                }
                // cout <<"position: "<<endl;
                // for(auto a = position.begin(); a != position.end(); ++a){
                    // cout << a->first << " "<<a->second <<" ";
                // }
                if(!position.empty()){
                    // cout<<"imhere"<<endl;
                    // cout<<position.rbegin()->first << " "<< position.rbegin()->second<<endl;
                    farestprocessornum = position.rbegin()->second;
                    processor[farestprocessornum] = task;
                    time++;
                }
                else{
                    // cout << "im in"<<endl;
                    processor[farestprocessornum] = task;
                    time++;
                }
            }
        }
    }
    cout << time;
    return 0;
}
// cout <<"processors: ";
                // for(auto a = processor.begin(); a != processor.end(); ++a){
                    // cout << *a << " ";
                // }
                // cout << endl;
                // cout <<"position: ";
                // for(auto a = position.begin(); a != position.end(); ++a){
                //     cout << a->first << " "<<a->second <<" ";
                // }
                // cout << endl;
                // cout<<position.rbegin()->first << " "<< position.rbegin()->second<<endl;