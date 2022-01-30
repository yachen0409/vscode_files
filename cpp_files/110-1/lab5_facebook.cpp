#include <iostream>
#include <stack>
#include <set>
#include <vector>
using namespace std;
long long N, M, Q;
stack<string>result;
vector<long long>fbrelation;
set <pair<long long, long long>> init;
long long find(long long x){
    return x == fbrelation[x] ? x : (fbrelation[x] = find(fbrelation[x]));
}
void merge(long long x, long long y){
    fbrelation[find(x)] = find(y);
}
bool relation(long long x, long long y){
    return find(x) == find(y);
}
class node{
    public:
    int node1, node2;
    string op;
    node(string a, int b, int c){
        op = a;
        node1 = b;
        node2 = c;
    }
};
stack<node*>instruction;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin >> N >> M >> Q;
    fbrelation.resize(N);
    for(long long i = 0; i < N; ++i){
        fbrelation[i] = i;
    }
    for(long long i = 0; i < M; ++i){
        long long temp1, temp2;
        cin >> temp1 >> temp2;
        init.insert(make_pair(temp1, temp2));
    }
    for(long long i = 0; i < Q; ++i){                  
        long long  node1, node2;
        string op;
        cin >> op >> node1 >> node2;
        node *temp = new node(op, node1, node2);
        instruction.push(temp);
        if(op == "U"){
            auto findit = init.find(make_pair(node1, node2));
            if(findit == init.end()) findit = init.find(make_pair(node2, node1));
            init.erase(findit);
        } 
    }
    for(auto it = init.begin(); it != init.end(); ++it){
        merge(it->second, it->first);
    }
    while(!instruction.empty()){
        node* curinstruction = instruction.top();
        if (curinstruction->op == "U"){
            merge(curinstruction->node2, curinstruction->node1);
        }
        else if(curinstruction->op == "A"){
            bool canreach = relation(curinstruction->node1, curinstruction->node2);
            if(canreach) result.push("YES");
            else result.push("NO");
        }
        instruction.pop();
    }
    while(!result.empty()){
        cout << result.top()<<"\n";
        result.pop();
    }
    return 0;
}