#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <queue>
using namespace std;
class Node{
    public:
     double totalpoint = 0.0;
     double originpeoplenum = 0.0;
     double teammatenum = 0.0;
     double originpoint = 0.0;
     double newpoint = 0.0;
     double pointincrease = 0.0;
    Node(double a, double b, double c){
        totalpoint = a;
        originpeoplenum = b;
        teammatenum = c;
        if(originpeoplenum+teammatenum == 0){
            originpoint = 0;
        }
        else{
            originpoint = totalpoint / (originpeoplenum + teammatenum);
        }
        newpoint = totalpoint / (originpeoplenum + teammatenum + 1);
        pointincrease = newpoint * (teammatenum + 1) - originpoint * teammatenum;
        
    }
};
class comp{
    public:
    bool operator ()(Node *a, Node *b){
        return a->pointincrease < b->pointincrease;
    }
};

priority_queue<Node*, vector<Node*>, comp> furniturepoint; //(totalpt, numonit);

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cout << fixed << setprecision(6);
    double sum=0.0;
    long long N, k;
    cin >> N >> k;
    for(long long a = 0; a < N; ++a){
        double totalpt, numonit;
        cin >> totalpt >> numonit;
        furniturepoint.push(new Node(totalpt, numonit, 0));
    }
    for(long long i = 0; i < k; ++i){
        // cout << endl;
        auto itnode = furniturepoint.top();
        double newtotalpoint = itnode->totalpoint;
        double neworiginanum = itnode->originpeoplenum;
        double newteammatenum = itnode->teammatenum + 1;

        furniturepoint.pop();
        furniturepoint.push(new Node(newtotalpoint, neworiginanum, newteammatenum));
    }
    for(auto it = furniturepoint.top(); !furniturepoint.empty(); ){
        if( (it->originpeoplenum + it->teammatenum)>0){
            sum += (it->totalpoint / (it->originpeoplenum + it->teammatenum)) * it->teammatenum;
        }
        furniturepoint.pop();
        it = furniturepoint.top();
    }
    cout << sum;
    return 0;
}