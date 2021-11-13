#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std ;

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    int types,number_instructions;
    int command,type_merchandise,expire,search_index ;
    cin>>number_instructions;
    map<int , priority_queue<int,vector<int>,greater<int> > > merchandise ;
    for(int i=0 ; i<number_instructions ; i++){
        cin>>command;
        if(command==1){
            cin>>type_merchandise>>expire;
            merchandise[type_merchandise].push(expire) ;
        }
        else{
            cin>>type_merchandise;
            if(merchandise.find(type_merchandise) == merchandise.end() || merchandise[type_merchandise].empty()){
                cout<<"-1"<<'\n';
            }
            else{
                cout<<merchandise[type_merchandise].top()<<'\n';
                merchandise[type_merchandise].pop();
            }

        }
    }
    return 0;
}