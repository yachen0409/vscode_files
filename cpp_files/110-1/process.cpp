//方法錯誤
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;
int main(){
    long long q, N, C, time = 0;
    vector<long long>tasklist, processor;
    map<long long, long long> freq;
    cin >> N >> C >> q;
    tasklist.resize(q);
    processor.resize(C, 0);
    for(long long i = 0; i < q; ++i){
        cin >> tasklist[i];
        freq[tasklist[i]] += 1;
    }
    
    for(long long j = 0; j < q; ++j){
        long long task = tasklist[j];
        // cout <<"task = "<< task << endl;
        auto itfind0 = find(processor.begin(), processor.end(), 0);
        auto itfindtask = find(processor.begin(), processor.end(), task);
        // for(auto temp = freq.begin(); temp != freq.end(); temp++){
        //    cout << temp->first <<" " ;
        // }
        // cout << endl;
        // cout <<"itfindtask=" << *itfind0 <<endl;
        // cout <<"itfindtask=" << *itfindtask <<endl;
        if(itfind0 != processor.end()){ //init_process exist
            // cout << "init_process exist + ";
            if(itfindtask == processor.end()){ //no task in processor now
                // cout<<"no task in processor now"<<endl;
                *itfind0 = task;
                time++;
            }
            else{
                // cout<<"task in processor now"<<endl;
            } 
            
            //else: there is task in processor although there are still init_process
            //all: update freq 
            // cout <<"task"<<task<< "-- "<<endl;
            freq[task]--;
        }
        else{
            // cout << "init_process DOESN'T exist + ";
            if(itfindtask == processor.end()){ //no task in processor now
                // cout<<"no task in processor now"<<endl;
                // cout <<"processors: ";
                // for(auto a = processor.begin(); a != processor.end(); ++a){
                    // cout << *a << " ";
                // }
                long long min = freq[processor[0]], minkey = processor[0]; 
                                //find min.freq process
                for(long long k = 1; k < C; ++k){
                    long long temp = freq[processor[k]];
                    // cout << "666666666666666666666"<<endl;
                    // cout << processor[k]<<" " <<minkey<<endl;
                    // cout << temp <<" "<< min <<endl;
                    if(temp < min){
                        min = temp;
                        minkey = processor[k];
                    }
                }
                // cout << "minfreq process no."<< minkey <<" "<< min<<endl;
                auto change = find(processor.begin(), processor.end(), minkey);
                *change = task;
                time++;
            }
            // else {
                // cout<<"task in processor now"<<endl;
            // }
            // cout <<"task"<<task<< "-- "<<endl;
            freq[task]--;   
        }
        // cout << "i'm here~"<<endl;
    }
    cout << time;
    // cout << "i'm out~"<<endl;

    return 0;
}