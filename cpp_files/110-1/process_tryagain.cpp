#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <map>
using namespace std;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    long long q, N, C, time = 0;
    vector<long long>tasklist, processor;
    vector <vector<long long>> farposition;
    map <long long, long long> tasktoprocessor;
    vector<bool> taskincore;
    vector<long long> everyprocesstimes;
    priority_queue <pair<long long, long long>> fartable;  //(farest index in tasklist, processer num)
    cin >> N >> C >> q;
    taskincore.resize(N+1, false);
    tasklist.resize(q);
    everyprocesstimes.resize(N+1, 0);
    farposition.resize(N+1);
    for(auto a = farposition.begin(); a != farposition.end(); ++a){
        a->push_back(0);
    }
    processor.resize(C, 0);
    bool outofcore = false;
    long long zeroindex = 0;
    for(long long i = 0; i < q; ++i){ //
        cin >> tasklist[i];
        farposition[tasklist[i]].push_back(i);
    }
    for(long long i = 1; i <= N; ++i ){
        farposition[i].push_back(q+1);
    }
    for(long long j = 0; j < q; ++j){
        long long task = tasklist[j];
        long long farestprocessornum;
        if(zeroindex == C && !outofcore){
            outofcore = true;
            for(auto a = processor.begin(); a != processor.end(); ++a){
                fartable.push({farposition[*a][everyprocesstimes[*a]+1],   tasktoprocessor[*a]});
            }
        }
        if(zeroindex < C){ //init_process exist
            if(!taskincore[task]){ //no task in processor now
                processor[zeroindex] = task;
                tasktoprocessor[task] = zeroindex;
                zeroindex++;
                time++;
            }    
            taskincore[task] = true;
            everyprocesstimes[task]++;
        }
        else{
            if(!taskincore[task]){ //no task in processor now
                taskincore[task] = true;
                farestprocessornum = fartable.top().second;
                fartable.pop();
                tasktoprocessor[task] = farestprocessornum;
                taskincore[processor[farestprocessornum]] = false;
                processor[farestprocessornum] = task;
                time++;
                everyprocesstimes[task]++;
                fartable.push({farposition[task][everyprocesstimes[task]+1], farestprocessornum});
            }
            else{
                everyprocesstimes[task]++;
                
                fartable.push({farposition[task][everyprocesstimes[task]+1],  tasktoprocessor[task]});
            }
        }
    }
    cout << time;
    return 0;
}