#include <iostream>
#include <vector>
using namespace std;
struct Node{
    int value;
    struct Node *child1, *child2 = NULL;
};
long long calculate(Node *a){
    if(a->child1==NULL&&a->child2==NULL){
        return a->value;
    }
    return a->value*(calculate(a->child1)+calculate(a->child2)) % 1000000007;
}
vector<Node> tree;
int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
    long long num_of_node = 0;
    cin >> num_of_node;
    tree.resize(num_of_node);
    for(int i = 0; i < num_of_node; ++i){
        long long temp_value;
        cin >> temp_value;
        tree[i].value = temp_value;
    }
    for(int i = 1; i < num_of_node; ++i){
        long long temp_parent;
        cin >> temp_parent;
        if(tree[temp_parent-1].child1 == NULL){
            tree[temp_parent-1].child1 = &tree[i];
        }
        else{
            tree[temp_parent-1].child2 = &tree[i];
        }
    }
    long long ans;
    ans = calculate(&tree[0]);
    cout<<ans;
    return 0;
}